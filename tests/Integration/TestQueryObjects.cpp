#include <gtest/gtest.h>

#include "OrderLine.h"
#include "QueryObjects/OrderLineQuery.h"
#include "SessionPool.h"

#include "Session.h"


using namespace Poco::Data;
using namespace Poco::Data::Keywords;

void InsertOrderLinesInTable(Adapters::Session& session, std::list<OrderLine> values)
{
	using OrderLineSql = Poco::Tuple<std::string, int, std::string>;
	std::vector<OrderLineSql> OrderLinesSql;

	for (const auto& line : values)
		OrderLinesSql.push_back(OrderLineSql(line.GetSku(), line.GetQuantity(), line.GetOrderId()));

	std::string insertQuery = "INSERT INTO order_lines (sku, qty, orderid) VALUES (?, ?, ?)";
	session() << insertQuery, use(OrderLinesSql), now;
}

TEST(Adapters, TestOrderLineQueryCanLoadLines)
{
    Adapters::Session session(Adapters::SessionPool::Instance().Get());
	Adapters::InitTables(session);

	std::list<OrderLine> orderLines = { OrderLine("order1", "RED-CHAIR", 12),
										OrderLine("order1", "RED-TABLE", 13),
										OrderLine("order2", "BLUE-LIPSTICK", 14) };
	InsertOrderLinesInTable(session, orderLines);

	Adapters::QueryObjects::OrderLineQuery sqlLine(session);
	auto received = sqlLine.GetAll();
	bool successfully{ true };

	for (const auto& line : orderLines)
	{
		if (std::find(received.begin(), received.end(), line) == received.end())
		{
			successfully = false;
			break;
		}
	}

	Adapters::DeleteTables(session);
	session.Commit();
    EXPECT_TRUE(successfully);
}

TEST(Adapters, TestOrderLineQueryCanSaveLine)
{
	Adapters::Session session(Adapters::SessionPool::Instance().Get());
	Adapters::InitTables(session);

	OrderLine newLine("order1", "DECORATIVE-WIDGET", 12);
	Adapters::QueryObjects::OrderLineQuery sqlLine(session);

	sqlLine.Add(newLine);

	auto orderLines = sqlLine.GetAll();
	bool successfully{ true };
		
	if (std::find(orderLines.begin(), orderLines.end(), newLine) == orderLines.end())
		successfully = false;

	Adapters::DeleteTables(session);
	session.Commit();
	EXPECT_TRUE(successfully);
}

TEST(Adapters, TestOrderLineQueryCanSaveLines)
{
	Adapters::Session session(Adapters::SessionPool::Instance().Get());
	Adapters::InitTables(session);

	std::list<OrderLine> orderLines = { OrderLine("order1", "RED-CHAIR", 12),
										OrderLine("order1", "RED-TABLE", 13),
										OrderLine("order2", "BLUE-LIPSTICK", 14) };
	
	Adapters::QueryObjects::OrderLineQuery sqlLine(session);
	sqlLine.Add(orderLines.begin(), orderLines.end());

	auto received = sqlLine.GetAll();
	bool successfully{ true };

	for (const auto& line : orderLines)
	{
		if (std::find(received.begin(), received.end(), line) == received.end())
		{
			successfully = false;
			break;
		}
	}

	Adapters::DeleteTables(session);
	session.Commit();
	EXPECT_TRUE(successfully);
}
