#pragma once

#include <vector>

#include "RubyBase.h"

struct RubyArray : public RubyBase
{
	RubyArray(std::vector<RubyBase*>* const paPtrs, const size_t length);

	size_t Length;
};

