#pragma once

#include <vector>

#include "RubyBase.h"

struct RubyHash : public RubyBase
{
	RubyHash(std::vector<RubyBase*>* const paPtrs, const size_t pairCount);

	size_t PairCount;
};

