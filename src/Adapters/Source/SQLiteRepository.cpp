#include "SQLiteRepository.h"

#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>
#include <Poco/DateTime.h>
#include <Poco/Timestamp.h>

std::chrono::system_clock::time_point GetDateFromDatabase(Poco::DateTime)
{
	return std::chrono::system_clock::time_point();
}

SQLiteRepository::SQLiteRepository(Poco::Data::Session& session)
{
}

void SQLiteRepository::Add(Batch batch)
{
}

Batch SQLiteRepository::Get()
{
	return Batch();
}
