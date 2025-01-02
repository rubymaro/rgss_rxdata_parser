#pragma once

#include <vector>

#include "RubyBase.h"

struct RubyHash : public RubyBase
{
	RubyHash(const size_t capacity);
	virtual ~RubyHash(void) = default;

	std::vector<RubyBase*> HashElementPtrs;
};

