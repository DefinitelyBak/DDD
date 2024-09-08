#pragma once

#include "Precompile.h"

#include "Batch.h"
#include "ConvertDate.h"

using namespace Poco::Data::Keywords;
using Poco::DateTime;
using Poco::DateTimeFormatter;
using Poco::Data::Session;
using Poco::Data::Statement;

//batch.GetReference(); // - 1
//batch.GetSku(); // - 2
//batch.GetAvailableQuantity(); // - 3;
//batch.GetAllocateQuantity(); // - 4;
//batch.GetDeliveryDate(); // - 5;


namespace Poco::Data
{

    using namespace Server::Model;

    template <>
    class TypeHandler<Batch>
    {
    public:
        static std::size_t size()
        {
            return 5;
        }

        static void bind(std::size_t pos, const Batch& batch, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
        {
            Poco::DateTime mapData = Server::Database::Convert(batch.GetDeliveryDate());

            TypeHandler<std::string>::bind(pos++, batch.GetReference(), pBinder, dir);
            TypeHandler<std::string>::bind(pos++, batch.GetSku(), pBinder, dir);
            TypeHandler<int>::bind(pos++, batch.GetAvailableQuantity(), pBinder, dir);
            TypeHandler<int>::bind(pos++, batch.GetAllocateQuantity(),  pBinder, dir);
            TypeHandler<DateTime>::bind(pos++, mapData, pBinder, dir);
        }

        static void extract(std::size_t pos, Batch& batch, const Batch& deflt, AbstractExtractor::Ptr pExtr)
        {
            std::string reference;
            std::string sku;
            int availableQuantity;
            int allocateQuantity;
            DateTime mapData(Server::Database::Convert(batch.GetDeliveryDate()));
            DateTime resData;

            TypeHandler<std::string>::extract(pos++, reference, deflt.GetReference(), pExtr);
            TypeHandler<std::string>::extract(pos++, sku, deflt.GetSku(), pExtr);
            TypeHandler<int>::extract(pos++, availableQuantity, deflt.GetAvailableQuantity(), pExtr);
            TypeHandler<int>::extract(pos++, allocateQuantity, deflt.GetAllocateQuantity(), pExtr);
            TypeHandler<DateTime>::extract(pos++, resData, mapData, pExtr);

            date::year_month_day batchData(Server::Database::Convert(resData));
            batch = Batch(reference, sku, availableQuantity, allocateQuantity, batchData);
        }

        static void prepare(std::size_t pos, const Batch& batch, AbstractPreparator::Ptr pPrep)
        {
            DateTime mapData(Server::Database::Convert(batch.GetDeliveryDate()));

            TypeHandler<std::string>::prepare(pos++, batch.GetReference(), pPrep);
            TypeHandler<std::string>::prepare(pos++, batch.GetSku(), pPrep);
            TypeHandler<int>::prepare(pos++, batch.GetAvailableQuantity(), pPrep);
            TypeHandler<int>::prepare(pos++, batch.GetAvailableQuantity(), pPrep);
            TypeHandler<DateTime>::prepare(pos++, mapData, pPrep);
        }
    };

}