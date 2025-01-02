#pragma once

#include <vector>

#include "RubyBase.h"

struct RubyHash : public RubyBase
{
	RubyHash(const size_t capacity);

	std::vector<RubyBase*> HashElementPtrs;
};

