#include <gtest/gtest.h>

#include "Precompile.h"

#include "Model/Auxiliary.h"
#include "Model.h"


namespace Server::Tests
{

  using namespace Model;
  using namespace date;

  TEST(Model, AllocatingToBatchReducesAvailableQuantity)
  {
    Batch batch = Batch("batch-001", "SMALL-TABLE", 20);
    OrderLine line = OrderLine("order-ref", "SMALL-TABLE", 2);
    batch.Allocate(line);

    int value = batch.GetAvailableQuantity();

    EXPECT_EQ( value, 18);
  };

  TEST(Model, CanAllocateIfAvailableGreaterThanRequired)
  {
    auto pair = MakeBatchAndLine("ELEGANT-LAMP", 20, 2);
    EXPECT_TRUE(pair.first.CanAllocate(pair.second));
  };

  TEST(Model, CannotAllocateIfAvailableSmallerThanRequired)
  {
    auto pair = MakeBatchAndLine("ELEGANT-LAMP", 2, 20);
    EXPECT_FALSE(pair.first.CanAllocate(pair.second));
  };

  TEST(Model, CanAllocateIfAvailableEqualToRequired)
  {
    auto pair = MakeBatchAndLine("ELEGANT-LAMP", 2, 2);
    EXPECT_TRUE(pair.first.CanAllocate(pair.second));
  };

  TEST(Model, CannotAllocateIfSkusDoNotMatch)
  {
    Batch batch = Batch("batch-001", "UNCOMFORTABLE-CHAIR", 100);
    OrderLine line = OrderLine("order-123", "EXPENSIVE-TOASTER", 10);
    EXPECT_FALSE(batch.CanAllocate(line));
  };

  TEST(Model, AllocationIsIdempotent)
  {
    auto pair = MakeBatchAndLine("ANGULAR-DESK", 20, 2);
    pair.first.Allocate(pair.second);
    pair.first.Allocate(pair.second);
    EXPECT_EQ(pair.first.GetAvailableQuantity(), 18);
  };

  TEST(Model, PrefersCurrentStockBatchesToShipments)
  {
    const year_month_day ymd{std::chrono::floor<days>(std::chrono::system_clock::now())};
    const year_month_day tomorrow(year(ymd.year()), month(ymd.month()), ++day(ymd.day()));

    std::list<std::shared_ptr<Batch>> batches;
    batches.emplace_back(std::make_shared<Batch>("in-stock-batch", "RETRO-CLOCK", 100, ymd));
    batches.emplace_back(std::make_shared<Batch>("shipment-batch", "RETRO-CLOCK", 100, tomorrow));
    OrderLine line = OrderLine("oref", "RETRO-CLOCK", 10);

    Allocate(line, batches.begin(), batches.end());

    EXPECT_EQ(batches.front()->GetAvailableQuantity(), 90);
    EXPECT_EQ(batches.back()->GetAvailableQuantity(), 100);
  };

  TEST(Model, PrefersEarlierBatches)
  {
    const year_month_day today{std::chrono::floor<days>(std::chrono::system_clock::now())};
    const year_month_day tomorrow(year(today.year()), month(today.month()), ++day(today.day()));
    const year_month_day later(year(tomorrow.year()), month(tomorrow.month()), ++day(tomorrow.day()));

    std::vector<std::shared_ptr<Batch>> batches;
    batches.emplace_back(std::make_shared<Batch>("speedy-batch", "MINIMALIST-SPOON", 100, today));
    batches.emplace_back(std::make_shared<Batch>("normal-batch", "MINIMALIST-SPOON", 100, tomorrow));
    batches.emplace_back(std::make_shared<Batch>("slow-batch", "MINIMALIST-SPOON", 100, later));

    OrderLine line = OrderLine("order1", "MINIMALIST-SPOON", 10);

    Allocate(line, batches.begin(), batches.end());

    for(auto& batch : batches)
    {
      if(batch->GetDeliveryDate() == today)
        EXPECT_EQ(batch->GetAvailableQuantity(), 90);
      else
        EXPECT_EQ(batch->GetAvailableQuantity(), 100);
    }
  };

   TEST(Model, ReturnsAllocatedBatchRef)
  {
    const year_month_day today{std::chrono::floor<days>(std::chrono::system_clock::now())};
    const year_month_day tomorrow(year(today.year()), month(today.month()), ++day(today.day()));

    std::deque<std::shared_ptr<Batch>> batches;
    std::shared_ptr<Batch> inStockBatch = std::make_shared<Batch>("in-stock-batch-ref", "HIGHBROW-POSTER", 100);
    std::shared_ptr<Batch> shipmentBatch = std::make_shared<Batch>("shipment-batch-ref", "HIGHBROW-POSTER", 100, tomorrow);

    batches.push_back(inStockBatch);
    batches.push_back(shipmentBatch);

    OrderLine line = OrderLine("oref", "HIGHBROW-POSTER", 10);

    auto allocation = Allocate(line, batches.begin(), batches.end());
    EXPECT_EQ(allocation->GetReference(), inStockBatch->GetReference());
  };

  TEST(Model, RaisesOutOfStockExceptionIfCannotAllocate)
  {
    std::vector<std::shared_ptr<Batch>> batches;
    batches.emplace_back(std::make_shared<Batch>("batch1", "SMALL-FORK", 10));
    Allocate(OrderLine("order1", "SMALL-FORK", 10), batches.begin(), batches.end());

    EXPECT_THROW({
        try
        {
            Allocate(OrderLine("order2", "SMALL-FORK", 1), batches.begin(), batches.end());
        }
        catch(const OutOfStock& e)
        {
            EXPECT_STREQ( "Артикула SMALL-FORK нет в наличии", e.what() );
            throw;
        }
    }, OutOfStock );
  };

}