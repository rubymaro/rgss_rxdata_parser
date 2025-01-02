#pragma once

#include <vector>

#include "RubyBase.h"

struct RubyArray : public RubyBase
{
	RubyArray(const size_t capacity);
	virtual ~RubyArray(void) = default;

	std::vector<RubyBase*> ArrayElementPtrs;
};

