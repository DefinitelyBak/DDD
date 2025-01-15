#include "Session.h"


namespace Adapters
{
	Session::Session(Poco::Data::Session session, Poco::Logger* pLogger):
		_session(session), _transaction(session, pLogger)
	{}

	Session::~Session()
	{
		if (!_committed)
			_transaction.rollback();
	}

	void Session::Commit()
	{
		_transaction.commit();
		_committed = true;
	}

	void Session::RollBack()
	{
		_transaction.rollback();
		_committed = false;
	}

	Poco::Data::Session& Session::operator()(void)
	{
		return _session;
	}
}
