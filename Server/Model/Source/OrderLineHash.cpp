#include "OrderLineHash.h"


namespace Server::Model
{
    std::size_t OrderLineHash::operator()(const Model::OrderLine& line) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(line.GetSku());
        std::size_t h2 = std::hash<std::string>{}(line.GetOrderId());
        std::size_t h3 = std::hash<int>{}(line.GetQuantity());
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
}