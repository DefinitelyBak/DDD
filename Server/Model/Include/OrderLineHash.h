#pragma once

#include "Precompile.h"

#include "OrderLine.h"


namespace Server::Model
{

    /// @brief Функтор для расчёта хэша
    struct OrderLineHash
    {
        /// @brief Расчёт кэша
        /// @param s Пара для которой раситывается кэш
        /// @return Кэш сумма
        std::size_t operator()(const Model::OrderLine & line) const noexcept;
    };

}