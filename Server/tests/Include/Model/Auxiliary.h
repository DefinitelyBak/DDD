#pragma once

#include "Precompile.h"
#include "Batch.h"


namespace Server::Tests
{

    std::pair<Model::Batch, Model::OrderLine> MakeBatchAndLine(
        std::string sku, int batchQty, int lineQty);

}