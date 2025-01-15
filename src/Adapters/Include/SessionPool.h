#pragma once

#include <Poco/Data/SessionPool.h>

#include "Session.h"


namespace Adapters
{
	void InitTables(Adapters::Session& session);
	void DeleteTables(Adapters::Session& session);

	class SessionPool
	{
	public:

		static SessionPool& Instance();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Adapters::Session Get();

	private:
		SessionPool();

		~SessionPool();

		Poco::Data::SessionPool _pocoSessionPool;
	};

}