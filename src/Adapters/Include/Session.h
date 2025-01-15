#pragma once

#include "Poco/Data/Transaction.h"
#include "Poco/Data/Session.h"


namespace Adapters
{
	/// <summary>Сессия с поддержкой транзакций</summary>
	class Session
	{
	public:
		Session(Poco::Data::Session session, Poco::Logger* pLogger = 0);

		~Session();

		void Commit();

		void RollBack();

		Poco::Data::Session& operator()(void);

	private:
		Poco::Data::Transaction _transaction;
		Poco::Data::Session _session;
		bool _committed{false};
	};
}