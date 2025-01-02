#pragma once

#include "RubyBase.h"

struct RubyClass : public RubyBase
{
	RubyClass(const char* const pClassName, const size_t classNameLength);

	std::string Name;
};

