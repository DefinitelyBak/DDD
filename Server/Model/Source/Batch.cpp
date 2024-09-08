#include "Batch.h"


namespace Server::Model
{
    Batch::Batch():
        _ref(""), _sku(""), _availableQuantity(0), _allocateQuantity(0), _data(date::year_month_day{})
    {};

    Batch::Batch(std::string ref, std::string sku, int qty, date::year_month_day data, const std::vector<OrderLine>& orderLines):
        _ref(ref), _sku(sku), _availableQuantity(qty), _data(data), _allocateQuantity(0)
    {
        for(const auto& line : orderLines)
        {
            _allocations.insert(line);
            _allocateQuantity += line.GetQuantity();
        }
    };

    Batch::Batch(std::string ref, std::string sku, int availableQuantity, int allocateQuantity, date::year_month_day data):
        _ref(ref), _sku(sku), _availableQuantity(availableQuantity), _allocateQuantity(allocateQuantity), _data(data) 
    {}

    void Batch::Allocate(const OrderLine &line)
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

    void Batch::SetOrders(const std::vector<OrderLine>& orderLines)
    {
        _allocations = SetOrderLines(orderLines.begin(), orderLines.end());
    };

    bool operator==(const Batch &lhs, const Batch &rhs)
    {
        return lhs.GetReference() == rhs.GetReference();
    };
    
}