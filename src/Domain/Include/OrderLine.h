#pragma once

#include <string>


class OrderLine
{
public:
    OrderLine() = default;

    OrderLine(std::string orderId, std::string sku, int qty);

    std::string GetOrderId() const;

    std::string GetSku() const;

    int GetQuantity() const;

private:
    std::string _orderId;
    std::string _sku;
    int _quantity;
};

bool operator==(const OrderLine& lsh, const OrderLine& rsh);