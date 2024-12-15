#pragma once

#include "RubyBase.h"

struct RubyClass : public RubyBase
{
	RubyClass(char* const paClassName, const size_t classNameLength);

	size_t ClassNameLength;
};

