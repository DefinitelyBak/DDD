#pragma once

#include "Decl.h"
#include "Precompile.h"

#include "OrderLine.h"
#include "OrderLineHash.h"


namespace Server::Model
{

    class DLL_EXPORT Batch
    {
    public:
        /// @brief 
        Batch();

        /// @brief 
        /// @param ref 
        /// @param sku 
        /// @param qty 
        /// @param data 
        Batch(std::string ref, std::string sku, int qty, date::year_month_day data = date::year_month_day(), const std::vector<OrderLine>& orderLines = std::vector<OrderLine>());

        /// @brief 
        /// @param ref 
        /// @param sku 
        /// @param availableQuantity 
        /// @param allocateQuantity 
        /// @param data 
        Batch(std::string ref, std::string sku, int availableQuantity, int allocateQuantity, date::year_month_day data = date::year_month_day());

        /// @brief 
        /// @param Line 
        void Allocate(const OrderLine& line);

        /// @brief 
        /// @param line 
        void Deallocate(OrderLine line);

        /// @brief 
        /// @return 
        int GetAllocateQuantity() const;

        /// @brief 
        /// @return 
        int GetAvailableQuantity() const;

        /// @brief 
        /// @return 
        std::string GetReference() const;

        /// @brief 
        /// @return 
        std::string GetSku() const;

        /// @brief 
        /// @return 
        date::year_month_day GetDeliveryDate() const;

        /// @brief 
        /// @param line 
        /// @return 
        bool CanAllocate(OrderLine line) const;

        /// @brief 
        /// @param orderLines 
        void SetOrders(const std::vector<OrderLine>& orderLines);

    private:
        /// @brief 
        using SetOrderLines = std::unordered_set<OrderLine, OrderLineHash>;

        std::string _ref;
        std::string _sku;
        int _availableQuantity;
        int _allocateQuantity;
        date::year_month_day _data;
        SetOrderLines _allocations;
    };

    /// @brief 
    /// @param lhs 
    /// @param rhs 
    /// @return 
    bool operator==(const Batch& lhs, const Batch& rhs);

}