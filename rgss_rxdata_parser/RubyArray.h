#pragma once

#include <vector>

#include "RubyObject.h"

struct RubyArray : public RubyObject
{
	RubyArray(std::vector<RubyObject*>* const paPtrs, const size_t length);

	size_t Length;
};

