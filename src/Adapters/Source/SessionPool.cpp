#include "SessionPool.h"

#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Exception.h"

namespace Adapters
{

    SessionPool::SessionPool(): _pocoSessionPool(Poco::Data::SessionPool("SQLite", "Allocation.db"))
    {
        Poco::Data::SQLite::Connector::registerConnector();
    }

    SessionPool::~SessionPool()
    {
        Poco::Data::SQLite::Connector::unregisterConnector();
    }

    SessionPool& SessionPool::Instance()
    {
        static SessionPool sessionPool;
        return sessionPool;
    }

    Adapters::Session SessionPool::Get()
    {
        return Adapters::Session(_pocoSessionPool.get());
    }

    void InitTables(Adapters::Session& session)
    {
        // Создание таблицы order_lines
        session() << "CREATE TABLE IF NOT EXISTS order_lines ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "sku TEXT, "
            "qty INTEGER NOT NULL, "
            "orderid TEXT);",
            Poco::Data::Keywords::now;

        // Создание таблицы products
        session() << "CREATE TABLE IF NOT EXISTS products ("
            "sku TEXT PRIMARY KEY, "
            "version_number INTEGER NOT NULL DEFAULT 0);",
            Poco::Data::Keywords::now;

        // Создание таблицы batches
        session() << "CREATE TABLE IF NOT EXISTS batches ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "reference TEXT, "
            "sku TEXT, "
            "_purchased_quantity INTEGER NOT NULL, "
            "eta DATE, "
            "FOREIGN KEY (sku) REFERENCES products(sku));",
            Poco::Data::Keywords::now;

        // Создание таблицы allocations
        session() << "CREATE TABLE IF NOT EXISTS allocations ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "orderline_id INTEGER, "
            "batch_id INTEGER, "
            "FOREIGN KEY (orderline_id) REFERENCES order_lines(id), "
            "FOREIGN KEY (batch_id) REFERENCES batches(id));",
            Poco::Data::Keywords::now;

        // Создание представления allocations_view
        session() << "CREATE VIEW IF NOT EXISTS allocations_view AS "
            "SELECT ol.orderid, p.sku, b.reference AS batchref "
            "FROM allocations a "
            "JOIN order_lines ol ON a.orderline_id = ol.id "
            "JOIN batches b ON a.batch_id = b.id "
            "JOIN products p ON b.sku = p.sku;",
            Poco::Data::Keywords::now;
    }

    void DeleteTables(Adapters::Session& session)
    {
        session() << "DROP VIEW IF EXISTS allocations_view", Poco::Data::Keywords::now;
        session() << "DROP TABLE IF EXISTS allocations", Poco::Data::Keywords::now;
        session() << "DROP TABLE IF EXISTS batches", Poco::Data::Keywords::now;
        session() << "DROP TABLE IF EXISTS products", Poco::Data::Keywords::now;
        session() << "DROP TABLE IF EXISTS order_lines", Poco::Data::Keywords::now;
    }
}
