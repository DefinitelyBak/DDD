#include "OrderLine.h"


namespace Server::Model
{

    OrderLine::OrderLine(): _orderid(""), _sku(""), _qty(0), _batchId(-1)  
    {}

    OrderLine::OrderLine(std::string orderId, std::string sku, int qty, int batchId): 
        _orderid(orderId), _sku(sku), _qty(qty), _batchId(batchId)
    {};

    std::string OrderLine::GetOrderId() const
    {
        return _orderid;
    };

    std::string OrderLine::GetSku() const
    {
        return _sku;
    };

    int OrderLine::GetQuantity() const
    {
        return _qty;
    };

    int OrderLine::GetParrentBatchId() const
    {
        return _batchId;
    };

    bool operator==(const OrderLine &lhs, const OrderLine &rhs)
    {
        return lhs.GetOrderId() == rhs.GetOrderId() &&
               lhs.GetQuantity() == rhs.GetQuantity() &&
               lhs.GetSku() == rhs.GetSku();
    }

}
