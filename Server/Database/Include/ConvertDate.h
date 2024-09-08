#pragma once

#include "Precompile.h"
#include "date.h"


namespace Server::Database
{

    /// @brief 
    /// @param data 
    /// @return 
    Poco::DateTime Convert(const date::year_month_day& data);

    /// @brief 
    /// @param data 
    /// @return 
    date::year_month_day Convert(const Poco::DateTime& data);

}