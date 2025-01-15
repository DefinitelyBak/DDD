#pragma once

#include "Poco/Data/Session.h"

#include "OrderLine.h"
#include "Session.h"


namespace Adapters::QueryObjects
{

	class OrderLineQuery
	{
	public:
		OrderLineQuery(Adapters::Session& session);

		std::list<OrderLine> GetAll();

		template<typename Iterator>
		void Add(Iterator begin, Iterator end)
		{
			std::list<OrderLineSql> orderLinesSql;;

			for (; begin != end; ++begin)
				orderLinesSql.emplace_back(begin->GetSku(), begin->GetQuantity(), begin->GetOrderId());

			try
			{
				_session() << "INSERT INTO order_lines (sku, qty, orderid) VALUES (?, ?, ?)", Poco::Data::Keywords::use(orderLinesSql), Poco::Data::Keywords::now;
			}
			catch (const Poco::Exception& ex)
			{
				throw ex;
			}
		}

		void Add(OrderLine line);

	private:
		using OrderLineSql = Poco::Tuple<std::string, int, std::string>;
		Adapters::Session& _session;
	};
}