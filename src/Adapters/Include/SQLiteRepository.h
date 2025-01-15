#pragma once

#include "IRepository.h"

#include <Poco/Data/Session.h>
#include <Poco/DateTime.h>

std::chrono::system_clock::time_point GetDateFromDatabase(Poco::DateTime);

class  SQLiteRepository final: public IRepository
{
public:
	SQLiteRepository(Poco::Data::Session& session);

	void Add(Batch batch) override;

	virtual Batch Get() override;

private:

};