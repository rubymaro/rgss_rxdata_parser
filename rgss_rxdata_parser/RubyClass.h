#pragma once

#include "RubyBase.h"

struct RubyClass : public RubyBase
{
	RubyClass(const char* const pClassName, const size_t classNameLength);
	virtual ~RubyClass(void) = default;

	std::string Name;
};

