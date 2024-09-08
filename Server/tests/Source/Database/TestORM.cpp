#include <gtest/gtest.h>

#include "Precompile.h"

#include "OrderLine.h"
#include "Batch.h"
#include "ORM/OrderLineMapping.h"
#include "ORM/BatchMapping.h"


namespace Server::Database
{

    using namespace Model;

    using namespace Poco::Data::Keywords;
    using Poco::DateTime;
    using Poco::DateTimeFormatter;
    using Poco::Data::Session;
    using Poco::Data::Statement;

    TEST(ORM, OrderlineMapperCanLoadLines)
    {
        Poco::Data::SQLite::Connector::registerConnector();
        Session session("SQLite", "test_database.db");

        session << "DROP TABLE IF EXISTS order_lines", now;
        session << "CREATE TABLE order_lines (orderid VARCHAR, sku VARCHAR, quantity INTEGER, batchId INTEGER)", now;
        
        std::vector<OrderLine> expected;
        expected.emplace_back("order1", "RED-CHAIR", 12);
        expected.emplace_back("order1", "RED-TABLE", 13);
        expected.emplace_back("order1", "BLUE-LIPSTICK", 14);

        Statement insert(session);
	    insert << "INSERT INTO order_lines VALUES(?, ?, ?, ?)", use(expected);
        
        insert.execute();

        std::vector<OrderLine> result;
        session << "SELECT * FROM order_lines", into(result), now;

        EXPECT_EQ(expected[0], result[0]);
        EXPECT_EQ(expected[1], result[1]);
        EXPECT_EQ(expected[2], result[2]);
    };

    TEST(ORM, OrderlineMapperCanSaveLines)
    {
        Poco::Data::SQLite::Connector::registerConnector();
        Session session("SQLite", "test_database.db");

        session << "DROP TABLE IF EXISTS order_lines", now;
        session << "CREATE TABLE order_lines (orderid VARCHAR, sku VARCHAR, quantity INTEGER, batchId INTEGER)", now;

        OrderLine newLine = OrderLine("order1", "DECORATIVE-WIDGET", 12);

        Statement insert(session);
	    insert << "INSERT INTO order_lines VALUES(?, ?, ?, ?)", use(newLine);
        insert.execute();
        
        OrderLine resultLine;
        session << "SELECT * FROM order_lines", into(resultLine), now;

        EXPECT_EQ(resultLine.GetOrderId(), "order1");
        EXPECT_EQ(resultLine.GetSku(), "DECORATIVE-WIDGET");
        EXPECT_EQ(resultLine.GetQuantity(), 12);
    };

    TEST(ORM, BatchMapperCanLoadBatch)
    {
        Poco::Data::SQLite::Connector::registerConnector();
        Session session("SQLite", "test_database.db");

        session << "DROP TABLE IF EXISTS batches", now;
        session << "CREATE TABLE batches (reference VARCHAR, sku VARCHAR, availableQuantity INTEGER, allocateQuantity INTEGER, date DATE)", now;
        
        std::vector<Batch> expected;
        expected.emplace_back("batch-001", "SMALL-TABLE", 20);
        expected.emplace_back("batch-002", "BIG-TABLE", 10);
        expected.emplace_back("batch-003", "TABLE", 5);

        Statement insert(session);
	    insert << "INSERT INTO batches VALUES(?, ?, ?, ?, ?)", use(expected);
        
        insert.execute();

        std::vector<Batch> result;
        session << "SELECT * FROM batches", into(result), now;

        EXPECT_EQ(expected[0], result[0]);
        EXPECT_EQ(expected[1], result[1]);
        EXPECT_EQ(expected[2], result[2]);
    };

    TEST(ORM, BatchMapperCanSaveBatch)
    {
        Poco::Data::SQLite::Connector::registerConnector();
        Session session("SQLite", "test_database.db");

        session << "DROP TABLE IF EXISTS batches", now;
        session << "CREATE TABLE batches (reference VARCHAR, sku VARCHAR, availableQuantity INTEGER, allocateQuantity INTEGER, date DATE)", now;

        date::year_month_day date(date::year(2015), date::month(6), date::day(13));
        Batch batch = Batch("batch-001", "SMALL-TABLE", 20, 12, date);

        Statement insert(session);
	    insert << "INSERT INTO batches VALUES(?, ?, ?, ?, ?)", use(batch);
        
        insert.execute();
        
        Batch result;
        session << "SELECT * FROM batches", into(result), now;

        EXPECT_EQ(result.GetReference(), "batch-001");
        EXPECT_EQ(result.GetSku(), "SMALL-TABLE");
        EXPECT_EQ(result.GetAvailableQuantity(), 20);
        EXPECT_EQ(result.GetAllocateQuantity(), 12);
        EXPECT_EQ(result.GetDeliveryDate(), date);
    };
}