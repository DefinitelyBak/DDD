#include "Model/Auxiliary.h"


namespace Server::Tests
{

    /// @brief 
    /// @param sku 
    /// @param batchQty 
    /// @param lineQty 
    /// @return 
    std::pair<Model::Batch, Model::OrderLine> MakeBatchAndLine(
        std::string sku, int batchQty, int lineQty)
    {
        return std::pair<Model::Batch, Model::OrderLine>(
            Model::Batch("Batch-001", sku, batchQty),
            Model::OrderLine("order-123", sku, lineQty));
    }

}