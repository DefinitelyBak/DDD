#include "Batch.h"

#include<numeric>

Batch::Batch(std::string ref, std::string sku, unsigned int qty, std::chrono::year_month_day eta):
	_reference(ref), _sku(sku), _eta(eta), _purchasedQuantity(qty)
{}

std::string Batch::GetReference() const
{
	return _reference;
}

std::string Batch::GetSku() const
{
	return _sku;
}

std::chrono::year_month_day Batch::GetEta() const
{
	return _eta;
}

unsigned int Batch::GetAvailableQuantity() const
{
	return _purchasedQuantity - std::accumulate(_allocations.begin(), _allocations.end(), 0,
		[](unsigned int value, OrderLine line)
		{
			return value + line.GetQuantity();
		}
	);
}

void Batch::Allocate(OrderLine line)
{
	if (CanAllocate(line))
		_allocations.insert(line);
}

void Batch::Deallocate(OrderLine line)
{
	if (auto iter = _allocations.find(line); iter != _allocations.end())
		_allocations.erase(iter);
}

bool Batch::CanAllocate(OrderLine line)
{
	return _sku == line.GetSku() and GetAvailableQuantity() >= line.GetQuantity();
}

bool operator==(const Batch& lsh, const Batch& rsh)
{
	return lsh.GetReference() == rsh.GetReference();
}
