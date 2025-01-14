#pragma once

#include <string>
#include <chrono>
#include <unordered_set>

#include "OrderLine.h"
#include "Utility.h"


class Batch
{
public:
	Batch() = default;

	Batch(std::string ref, std::string sku, unsigned int qty, std::chrono::year_month_day eta = std::chrono::year_month_day());

	std::string GetReference() const;

	std::string GetSku() const;

	std::chrono::year_month_day GetEta() const;

	unsigned int GetAvailableQuantity() const;

	void Allocate(OrderLine line);

	void Deallocate(OrderLine line);

	bool CanAllocate(OrderLine line);

private:
	std::string _reference;
	std::string _sku;
	std::chrono::year_month_day _eta;
	unsigned int _purchasedQuantity;
	std::unordered_set<OrderLine> _allocations;
};

bool operator==(const Batch& lsh, const Batch& rsh);