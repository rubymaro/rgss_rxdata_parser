#pragma once

#include <vector>

#include "RubyBase.h"

struct RubyArray : public RubyBase
{
	RubyArray(const size_t length);

	std::vector<RubyBase*> ArrayElementPtrs;
	size_t Length;
};

