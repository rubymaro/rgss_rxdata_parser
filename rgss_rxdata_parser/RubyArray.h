#pragma once

#include <vector>

#include "RubyBase.h"

struct RubyArray : public RubyBase
{
	RubyArray(const size_t capacity);

	std::vector<RubyBase*> ArrayElementPtrs;
};

