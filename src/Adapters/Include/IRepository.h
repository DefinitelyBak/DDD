#pragma once

#include "Batch.h"

class IRepository
{
public:
	virtual ~IRepository() = default;

	virtual void Add(Batch batch) = 0;

	virtual Batch Get() = 0;
};