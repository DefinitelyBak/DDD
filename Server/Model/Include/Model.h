#pragma once

#include "Decl.h"
#include "Precompile.h"

#include "Batch.h"


namespace Server::Model
{
    
    /// @brief 
    /// @tparam Iterator 
    /// @param  
    /// @param begin 
    /// @param end 
    /// @return 
    template<typename Iterator>
    std::shared_ptr<Batch> Allocate(OrderLine line, Iterator begin, Iterator end)
    {
        std::vector<std::shared_ptr<Batch>> localCopy;
        std::copy(begin, end, std::back_inserter(localCopy));

        auto comp = [](std::shared_ptr<Batch> a, std::shared_ptr<Batch> b){return a->GetDeliveryDate() < b->GetDeliveryDate();};
        std::sort(localCopy.begin(), localCopy.end(), comp);

        for(auto& batch : localCopy)
            if(batch->CanAllocate(line))
            {
                batch->Allocate(line);
                return batch;
            }

        return std::shared_ptr<Batch>();
    };

}