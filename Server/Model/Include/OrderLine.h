#pragma once

#include "Decl.h"
#include "Precompile.h"


namespace Server::Model
{

    /// @brief 
    class DLL_EXPORT OrderLine
    {
    public:
        /// @brief 
        OrderLine();

        /// @brief 
        /// @param orderid 
        /// @param sku 
        /// @param qty 
        explicit OrderLine(std::string orderId, std::string sku, int qty, int batchId = -1);

        /// @brief 
        /// @return 
        std::string GetOrderId() const;

        /// @brief 
        /// @return 
        std::string GetSku() const;

        /// @brief 
        /// @return 
        int GetQuantity() const;

        /// @brief 
        /// @return 
        int GetParrentBatchId() const;

    private:
        std::string _orderid;
        std::string _sku;
        int _qty;
        int _batchId;
    };

    /// @brief 
    /// @param lhs 
    /// @param rhs 
    /// @return 
    bool operator==(const OrderLine& lhs, const OrderLine& rhs);

}