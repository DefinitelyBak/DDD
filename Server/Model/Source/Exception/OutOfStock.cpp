#include "Exception/OutOfStock.h"


namespace Server::Model
{

    OutOfStock::OutOfStock(const std::string& what_arg) : out_of_range (what_arg){};

    OutOfStock::OutOfStock(const char* what_arg) : out_of_range(what_arg){};

    OutOfStock::OutOfStock(const OutOfStock& other) noexcept : out_of_range(other){};

    const char* OutOfStock::what() const noexcept
    {
        return out_of_range::what();
    }

}

