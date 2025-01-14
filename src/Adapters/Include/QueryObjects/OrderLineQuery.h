#pragma once

#include "Poco/Data/Session.h"

#include "OrderLine.h"


using namespace Poco::Data;
using namespace Poco::Data::Keywords;

class OrderLineQuery
{
public:
	OrderLineQuery(Poco::Data::Session& session);

	std::list<OrderLine> GetAll();

	template<typename Iterator>
	void Add(Iterator begin, Iterator end)
	{
		std::list<OrderLineSql> orderLinesSql;;

		for (; begin != end; ++begin)
			orderLinesSql.emplace_back(begin->GetSku(), begin->GetQuantity(), begin->GetOrderId());

		try
		{
			_session << "INSERT INTO order_lines (sku, qty, orderid) VALUES (?, ?, ?)", use(orderLinesSql), now;
		}
		catch (const Poco::Exception& ex)
		{
			throw ex;
		}
	}

	void Add(OrderLine line);

	template<typename Iterator>
	Statement AddLater(Iterator begin, Iterator end)
	{
		std::list<OrderLineSql> orderLinesSql;

		for (; begin != end; ++begin)
			orderLinesSql.emplace_back(begin->GetSku(), begin->GetQuantity(), begin->GetOrderId());

		return (_session << "INSERT INTO order_lines (sku, qty, orderid) VALUES (?, ?, ?)", bind(orderLinesSql));
	}

	Statement AddLater(OrderLine line);

private:
	using OrderLineSql = Poco::Tuple<std::string, int, std::string>;
	Poco::Data::Session& _session;
};