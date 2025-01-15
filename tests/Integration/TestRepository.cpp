#include <gtest/gtest.h>


#include "OrderLine.h"
#include "Batch.h"
#include "IRepository.h"
#include "SQLiteRepository.h"
#include "QueryObjects/OrderLineQuery.h"

#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/SessionPool.h"
#include "Poco/Data/RecordSet.h"

using namespace Poco::Data;
using namespace Poco::Data::Keywords;


static SessionPool pool("SQLite", "TestDatabase.db");

TEST(Adapters, test_repository_can_save_a_batch)
{
	SQLite::Connector::registerConnector();
	Session session(pool.get());

	Batch batch("batch1", "RUSTY-SOAPDISH", 100);
	std::shared_ptr<IRepository> repo = std::make_shared<SQLiteRepository>(session);
	repo->Add(batch);
	session.commit();

	auto stament = (session << "SELECT reference, sku, _purchased_quantity, eta FROM batches", now);
	Poco::Data::RecordSet rs(stament);
	rs.moveFirst();

	EXPECT_EQ(rs["reference"].toString(), "batch1");
	EXPECT_EQ(rs["sku"].toString(), "RUSTY-SOAPDISH");
	EXPECT_EQ(rs["_purchased_quantity"].convert<int>(), 100);
	std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(GetDateFromDatabase(rs["eta"].convert<Poco::DateTime>()))};
	EXPECT_EQ(ymd, std::chrono::year_month_day());
}



/*
def insert_order_line(session):
session.execute( 
'INSERT INTO order_lines (orderid, sku, qty)'
' VALUES ("order1", "GENERIC-SOFA", 12)'
)
[[orderline_id]] = session.execute(
'SELECT id FROM order_lines WHERE orderid=:orderid AND
sku=:sku',
dict(orderid="order1", sku="GENERIC-SOFA")
)
return orderline_id
def insert_batch(session, batch_id): 
...
def test_repository_can_retrieve_a_batch_with_allocations(session):
orderline_id = insert_order_line(session)
batch1_id = insert_batch(session, "batch1")
insert_batch(session, "batch2")
insert_allocation(session, orderline_id, batch1_id) 
repo = repository.SqlAlchemyRepository(session)
retrieved = repo.get("batch1")
expected = model.Batch("batch1", "GENERIC-SOFA", 100, eta=None)
assert retrieved == expected # Batch.__eq__ сравнивает только
ссылку 
assert retrieved.sku == expected.sku 
assert retrieved._purchased_quantity == expected._purchased_quantity
assert retrieved._allocations == { 
model.OrderLine("order1", "GENERIC-SOFA", 12),
}
}
*/