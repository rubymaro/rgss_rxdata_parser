#pragma once

#include <vector>

#include "RubyObject.h"

struct RubyHash : public RubyObject
{
	RubyHash(std::vector<RubyObject*>* const paPtrs, const size_t pairCount);

	size_t PairCount;
};

