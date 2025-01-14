#include "QueryObjects/OrderLineQuery.h"

#include "Poco/Data/RecordSet.h"
#include <Poco/Data/Statement.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/Exception.h>

OrderLineQuery::OrderLineQuery(Poco::Data::Session& session) : _session(session) {}

std::list<OrderLine> OrderLineQuery::GetAll()
{
    std::list<OrderLine> result;

    try
    {
        Statement select = (_session << "SELECT sku, qty, orderid FROM order_lines", now);
        RecordSet rs(select);

        for(auto iter = rs.begin(); iter != rs.end(); ++iter)
        {
            result.emplace_back((*iter)["orderid"].toString(),
                                (*iter)["sku"].toString(),
                                (*iter)["qty"].convert<int>());
        }

        return result;
    }
    catch (const Poco::Exception& ex)
    {
        throw ex;
    }

    return result;
}

void OrderLineQuery::Add(OrderLine line)
{
    OrderLineSql sqlLine(line.GetSku(), line.GetQuantity(), line.GetOrderId());
    try
    {
        _session << "INSERT INTO order_lines(sku, qty, orderid) VALUES(? , ? , ? )",
            use(sqlLine), now;
    }
    catch (const Poco::Exception& ex)
    {
        throw ex;
    }
}

Poco::Data::Statement OrderLineQuery::AddLater(OrderLine line)
{
    OrderLineSql sqlLine(line.GetSku(), line.GetQuantity(), line.GetOrderId());
    try
    { 
        return _session << "INSERT INTO order_lines (sku, qty, orderid) VALUES (?, ?, ?)", bind(sqlLine);
    }
    catch (const Poco::Exception& ex)
    {
        throw ex;
    }
}


