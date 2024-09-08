#pragma once

#include "Precompile.h"


namespace Server::Model
{
    /// @brief 
    class OutOfStock final: public std::out_of_range
    {
    public:
        /// @brief 
        /// @param what_arg 
        OutOfStock(const std::string& what_arg);

        /// @brief 
        /// @param what_arg 
        OutOfStock( const char* what_arg );

        /// @brief 
        /// @param other 
        OutOfStock( const OutOfStock& other ) noexcept;

        /// @brief 
        /// @return 
        const char* what() const noexcept override; 
    };

}

