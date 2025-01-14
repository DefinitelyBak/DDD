#include <gtest/gtest.h>

#include <chrono>
#include "Batch.h"
#include "Model.h"


TEST(Domain, test_prefers_current_stock_batches_to_shipments)
{
	const std::chrono::time_point now{ std::chrono::system_clock::now() };
	const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(now) };

	Batch in_stock_batch = Batch("in-stock-batch", "RETRO-CLOCK", 100);
	Batch shipment_batch = Batch("shipment-batch", "RETRO-CLOCK", 100, std::chrono::year_month_day{ std::chrono::sys_days(ymd) + std::chrono::days{ 1 } });
	std::vector<Batch> batches = { in_stock_batch , shipment_batch };

	OrderLine line = OrderLine("oref", "RETRO-CLOCK", 10);

	Allocate(line, batches.begin(), batches.end());

	EXPECT_EQ(batches[0].GetAvailableQuantity(), 90);
	EXPECT_EQ(batches[1].GetAvailableQuantity(), 100);
}

TEST(Domain, test_prefers_earlier_batches)
{
	const std::chrono::time_point now{ std::chrono::system_clock::now() };
	const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(now) };
	std::chrono::sys_days sys_days_date = std::chrono::sys_days(ymd);

	Batch earliest = Batch("speedy-batch", "MINIMALIST-SPOON", 100, ymd);
	Batch medium = Batch("normal-batch", "MINIMALIST-SPOON", 100, std::chrono::year_month_day{ sys_days_date + std::chrono::days{ 1 } });
	Batch latest = Batch("slow-batch", "MINIMALIST-SPOON", 100, std::chrono::year_month_day{ sys_days_date + std::chrono::days{ 2 } });
	OrderLine line = OrderLine("order1", "MINIMALIST-SPOON", 10);
	std::vector<Batch> batches = { earliest , medium,  latest };

	Allocate(line, batches.begin(), batches.end());

	EXPECT_EQ(batches[0].GetAvailableQuantity(), 90);
	EXPECT_EQ(batches[1].GetAvailableQuantity(), 100);
	EXPECT_EQ(batches[2].GetAvailableQuantity(), 100);
}

TEST(Domain, test_returns_allocated_batch_ref)
{
	const std::chrono::time_point now{ std::chrono::system_clock::now() };
	const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(now) };

	Batch in_stock_batch = Batch("in-stock-batch-ref", "HIGHBROW-POSTER", 100);
	Batch shipment_batch = Batch("shipment-batch-ref", "HIGHBROW-POSTER", 100, std::chrono::year_month_day{ std::chrono::sys_days(ymd) + std::chrono::days{ 1 } });
	OrderLine line = OrderLine("oref", "HIGHBROW-POSTER", 10);
	std::list<Batch> batches = { in_stock_batch , shipment_batch };

	auto allocation = Allocate(line, batches.begin(), batches.end());
	EXPECT_EQ(allocation, in_stock_batch.GetReference());
}

TEST(Domain, test_raises_out_of_stock_exception_if_cannot_allocate)
{
	const std::chrono::time_point now{ std::chrono::system_clock::now() };
	const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(now) };

	Batch batch = Batch("batch1", "SMALL - FORK", 10, ymd);
	std::list<Batch> batches = { batch };
	Allocate(OrderLine("order1", "SMALL - FORK", 10), batches.begin(), batches.end());
	EXPECT_THROW(Allocate(OrderLine("order2", "SMALL - FORK", 1), batches.begin(), batches.end()), OutOfStock);
}