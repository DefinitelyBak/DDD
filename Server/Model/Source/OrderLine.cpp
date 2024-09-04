#include "OrderLine.h"


namespace Server::Model
{

    OrderLine::OrderLine(std::string orderId, std::string sku, int qty): 
        _orderid(orderId), _sku(sku), _qty(qty)
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

    bool operator==(const OrderLine &lhs, const OrderLine &rhs)
    {
        return lhs.GetOrderId() == rhs.GetOrderId() &&
               lhs.GetQuantity() == rhs.GetQuantity() &&
               lhs.GetSku() == rhs.GetSku();
    }

}
