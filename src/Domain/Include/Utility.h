#pragma once

#include <utility>

#include "OrderLine.h"

template<>
struct std::hash<OrderLine>
{
    std::size_t operator()(const OrderLine& line) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(line.GetOrderId());
        std::size_t h2 = std::hash<std::string>{}(line.GetSku());
        std::size_t h3 = std::hash<unsigned int>{}(line.GetQuantity());
        return h1 ^ (h2 << 1) ^ (h3 << 2); // or use boost::hash_combine
    }
};