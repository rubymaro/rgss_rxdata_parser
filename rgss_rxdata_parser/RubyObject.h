#pragma once

#include "RubyBase.h"

struct RubyObject : public RubyBase
{
	RubyObject(char* const paClassName, const size_t classNameLength);

	char* PAClassName;
	size_t ClassNameLength;
};

