#include <gtest/gtest.h>

#include "OrderLine.h"
#include "QueryObjects/OrderLineQuery.h"

#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/SessionPool.h"

using namespace Poco::Data;
using namespace Poco::Data::Keywords;


static SessionPool pool("SQLite", "TestDatabase.db");

void CreateNewTableOrderLine(Poco::Data::Session& session)
{
    session << "DROP TABLE IF EXISTS order_lines", now;
    std::string createTableQuery = R"(
            CREATE TABLE IF NOT EXISTS order_lines (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                sku TEXT,
                qty INTEGER NOT NULL,
                orderid TEXT
            )
        )";
    session << createTableQuery, now;
}

void InsertOrderLinesInTable(Poco::Data::Session& session, std::list<OrderLine> values)
{
	using OrderLineSql = Poco::Tuple<std::string, int, std::string>;
	std::vector<OrderLineSql> OrderLinesSql;

	for (const auto& line : values)
		OrderLinesSql.push_back(OrderLineSql(line.GetSku(), line.GetQuantity(), line.GetOrderId()));

	std::string insertQuery = "INSERT INTO order_lines (sku, qty, orderid) VALUES (?, ?, ?)";
	session << insertQuery, use(OrderLinesSql), now;
}

TEST(Adapters, test_orderline_mapper_can_load_lines)
{
	SQLite::Connector::registerConnector();
    Session session(pool.get());

	std::list<OrderLine> orderLines = { OrderLine("order1", "RED-CHAIR", 12),
										OrderLine("order1", "RED-TABLE", 13),
										OrderLine("order2", "BLUE-LIPSTICK", 14) };

    CreateNewTableOrderLine(session);
	InsertOrderLinesInTable(session, orderLines);
	OrderLineQuery sqlLine(session);

	bool successfully{ true };
	auto received = sqlLine.GetAll();

	for (const auto& line : orderLines)
	{
		if (std::find(received.begin(), received.end(), line) == received.end())
		{
			successfully = false;
			break;
		}
	}

    EXPECT_TRUE(successfully);
}

TEST(Adapters, test_orderline_mapper_can_save_line)
{
	SQLite::Connector::registerConnector();
	Session session(pool.get());
	CreateNewTableOrderLine(session);

	OrderLine newLine("order1", "DECORATIVE-WIDGET", 12);
	OrderLineQuery sqlLine(session);

	bool successfully{ true };

	sqlLine.Add(newLine);
	auto orderLines = sqlLine.GetAll();
		
	if (std::find(orderLines.begin(), orderLines.end(), newLine) == orderLines.end())
		successfully = false;

	EXPECT_TRUE(successfully);
}

TEST(Adapters, test_orderline_mapper_can_save_lines)
{
	SQLite::Connector::registerConnector();
	Session session(pool.get());

	std::list<OrderLine> orderLines = { OrderLine("order1", "RED-CHAIR", 12),
										OrderLine("order1", "RED-TABLE", 13),
										OrderLine("order2", "BLUE-LIPSTICK", 14) };

	CreateNewTableOrderLine(session);
	OrderLineQuery sqlLine(session);

	bool successfully{ true };
	sqlLine.Add(orderLines.begin(), orderLines.end());
	auto received = sqlLine.GetAll();

	for (const auto& line : orderLines)
	{
		if (std::find(received.begin(), received.end(), line) == received.end())
		{
			successfully = false;
			break;
		}
	}

	EXPECT_TRUE(successfully);
}

TEST(Adapters, test_orderline_mapper_can_save_line_later)
{
	SQLite::Connector::registerConnector();
	Session session(pool.get());
	CreateNewTableOrderLine(session);

	OrderLine newLine("order1", "DECORATIVE-WIDGET", 12);
	OrderLineQuery sqlLine(session);

	bool successfully{ true };

	auto statement = sqlLine.AddLater(newLine);
	statement.execute();
	auto orderLines = sqlLine.GetAll();

	if (std::find(orderLines.begin(), orderLines.end(), newLine) == orderLines.end())
		successfully = false;

	EXPECT_TRUE(successfully);
}

TEST(Adapters, test_orderline_mapper_can_save_lines_later)
{
	SQLite::Connector::registerConnector();
	Session session(pool.get());

	std::list<OrderLine> orderLines = { OrderLine("order1", "RED-CHAIR", 12),
										OrderLine("order1", "RED-TABLE", 13),
										OrderLine("order2", "BLUE-LIPSTICK", 14) };

	CreateNewTableOrderLine(session);
	OrderLineQuery sqlLine(session);

	bool successfully{ true };
	auto statement = sqlLine.AddLater(orderLines.begin(), orderLines.end());
	statement.execute();
	auto received = sqlLine.GetAll();

	for (const auto& line : orderLines)
	{
		if (std::find(received.begin(), received.end(), line) == received.end())
		{
			successfully = false;
			break;
		}
	}

	EXPECT_TRUE(successfully);
}