#include "OrderLine.h"


OrderLine::OrderLine(std::string orderId, std::string sku, int qty):
	_orderId(orderId), _sku(sku), _quantity(qty)
{}

std::string OrderLine::GetOrderId() const
{
	return _orderId;
}

std::string OrderLine::GetSku() const
{
	return _sku;
}

int OrderLine::GetQuantity() const
{
	return _quantity;
}

bool operator==(const OrderLine& lsh, const OrderLine& rsh)
{
	return lsh.GetOrderId() == rsh.GetOrderId() ||
		lsh.GetQuantity() == rsh.GetQuantity() ||
		lsh.GetSku() == rsh.GetSku();
}
