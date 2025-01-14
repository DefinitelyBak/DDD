#include <gtest/gtest.h>

#include <utility>
#include "Batch.h"


std::pair<Batch, OrderLine> MakeBatchAndLine(std::string sku, unsigned int batchQty, unsigned int lineQty)
{
	const std::chrono::time_point now{ std::chrono::system_clock::now() };
	const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(now) };

	return std::make_pair<Batch, OrderLine>(
		Batch("batch-001", sku, batchQty, ymd),
		OrderLine("order-123", sku, lineQty)
	);
}
TEST(Domain, test_allocating_to_a_batch_reduces_the_available_quantity)
{
	Batch batch("batch-001", "SMALL-TABLE", 20);
	OrderLine line("order-ref", "SMALL-TABLE", 2);

	batch.Allocate(line);

	EXPECT_EQ(batch.GetAvailableQuantity(), 18);
}

TEST(Domain, test_can_allocate_if_available_greater_than_required)
{
	auto [large_batch, small_line] = MakeBatchAndLine("ELEGANT-LAMP", 20, 2);
	EXPECT_TRUE(large_batch.CanAllocate(small_line));
}

TEST(Domain, test_cannot_allocate_if_available_smaller_than_required)
{
	auto [small_batch, large_line] = MakeBatchAndLine("ELEGANT-LAMP", 2, 20);
	EXPECT_FALSE(small_batch.CanAllocate(large_line));
}

TEST(Domain, test_can_allocate_if_available_equal_to_required)
{
	auto [batch, line] = MakeBatchAndLine("ELEGANT-LAMP", 2, 2);
	EXPECT_TRUE(batch.CanAllocate(line));
}

TEST(Domain, test_cannot_allocate_if_skus_do_not_match)
{
	Batch batch = Batch("batch-001", "UNCOMFORTABLE-CHAIR", 100);
	OrderLine different_sku_line = OrderLine("order-123", "EXPENSIVE-TOASTER", 10);
	EXPECT_FALSE(batch.CanAllocate(different_sku_line));
}

TEST(Domain, test_can_only_deallocate_allocated_lines)
{
	auto [batch, unallocated_line] = MakeBatchAndLine("DECORATIVE-TRINKET", 20, 2);
	batch.Deallocate(unallocated_line);
	EXPECT_EQ(batch.GetAvailableQuantity(), 20);
}

TEST(Domain, test_allocation_is_idempotent)
{
	auto [batch, line] = MakeBatchAndLine("ANGULAR-DESK", 20, 2);
	batch.Allocate(line);
	batch.Allocate(line);
	EXPECT_EQ(batch.GetAvailableQuantity(), 18);
}
