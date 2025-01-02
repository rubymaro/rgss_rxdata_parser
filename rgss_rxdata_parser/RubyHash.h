#pragma once

#include <vector>

#include "RubyBase.h"

struct RubyHash : public RubyBase
{
	RubyHash(const size_t pairCount);

	std::vector<RubyBase*> HashElementPtrs;
	size_t PairCount;
};

