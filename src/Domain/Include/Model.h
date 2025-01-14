#pragma once

#include <functional>
#include <algorithm>
#include "Batch.h"
#include "Exception.h"

template<typename Iterator>
std::string Allocate(OrderLine line, Iterator begin, Iterator end)
{
	std::list<Batch> copy(begin, end);
	copy.sort([](const Batch& lsh, const Batch& rsh)
		{
			return lsh.GetEta() < rsh.GetEta();
		});

	std::string reference;

	for (auto& batch : copy)
	{
		if (batch.CanAllocate(line))
		{
			reference = batch.GetReference();
			break;
		}
	}

	auto iter = std::find_if(begin, end, [reference](const Batch& batch)
		{
			return batch.GetReference() == reference;
		});

	if (iter != end)
	{
		iter->Allocate(line);
		return iter->GetReference();
	}

	throw OutOfStock("Артикула " + line.GetSku() + " нет в наличии");
}