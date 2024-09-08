#pragma once

#include "Precompile.h"

#include "OrderLine.h"

using namespace Poco::Data::Keywords;
using Poco::DateTime;
using Poco::DateTimeFormatter;
using Poco::Data::Session;
using Poco::Data::Statement;

namespace Poco::Data
{

    using namespace Server::Model;

    template <>
    class TypeHandler<OrderLine>
    {
    public:
        static std::size_t size()
        {
            return 4;
        }

        static void bind(std::size_t pos, const OrderLine& line, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
        {
            TypeHandler<std::string>::bind(pos++, line.GetOrderId(), pBinder, dir);
            TypeHandler<std::string>::bind(pos++, line.GetSku(), pBinder, dir);
            TypeHandler<int>::bind(pos++, line.GetQuantity(), pBinder, dir);
            TypeHandler<int>::bind(pos++, line.GetParrentBatchId(), pBinder, dir);
        }

        static void extract(std::size_t pos, OrderLine& line, const OrderLine& deflt, AbstractExtractor::Ptr pExtr)
        {
            std::string orderId;
            std::string sku;
            int quantity;
            int parrentBatchId;
            TypeHandler<std::string>::extract(pos++, orderId, deflt.GetOrderId(), pExtr);
            TypeHandler<std::string>::extract(pos++, sku, deflt.GetSku(), pExtr);
            TypeHandler<int>::extract(pos++, quantity, deflt.GetQuantity(), pExtr);
            TypeHandler<int>::extract(pos++, parrentBatchId, deflt.GetParrentBatchId(), pExtr);
            line = OrderLine(orderId, sku, quantity, parrentBatchId);
        }

        static void prepare(std::size_t pos, const OrderLine& line, AbstractPreparator::Ptr pPrep)
        {
            TypeHandler<std::string>::prepare(pos++, line.GetOrderId(), pPrep);
            TypeHandler<std::string>::prepare(pos++, line.GetSku(), pPrep);
            TypeHandler<int>::prepare(pos++, line.GetQuantity(), pPrep);
            TypeHandler<int>::prepare(pos++, line.GetParrentBatchId(), pPrep);
        }
    };

}