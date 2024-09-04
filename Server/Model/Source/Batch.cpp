#include "Batch.h"


namespace Server::Model
{

    Batch::Batch(std::string ref, std::string sku, int qty, date::year_month_day data):
        _ref(ref), _sku(sku), _availableQuantity(qty), _data(data), _allocateQuantity(0)
    {};

    void Batch::Allocate(OrderLine line)
    {
        if(!CanAllocate(line))
            return;

        Deallocate(line);

        _allocations.insert(line);
        _availableQuantity -= line.GetQuantity();
        _allocateQuantity += line.GetQuantity();
    };

    void Batch::Deallocate(OrderLine line)
    {
        if(auto iter = _allocations.find(line); iter != _allocations.end())
        {
           _availableQuantity += iter->GetQuantity();
           _allocateQuantity -= iter->GetQuantity();
           _allocations.erase(iter);
        }
    };

    int Batch::GetAllocateQuantity() const
    {
        return _allocateQuantity;
    };

    int Batch::GetAvailableQuantity() const
    {
        return _availableQuantity;
    };

    std::string Batch::GetReference() const
    {
        return _ref;
    };

    std::string Batch::GetSku() const
    {
        return _sku;
    };

    date::year_month_day Batch::GetDeliveryDate() const
    {
        return _data;
    };

    bool Batch::CanAllocate(OrderLine line) const
    {
        return _sku == line.GetSku() &&
               _availableQuantity >= line.GetQuantity();
    };

    bool operator==(const Batch &lhs, const Batch &rhs)
    {
        return lhs.GetReference() == rhs.GetReference();
    };
    
}