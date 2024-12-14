#pragma once

#include "RubyObject.h"

struct RubyClass : public RubyObject
{
	RubyClass(char* const paClassName, const size_t classNameLength);

	size_t ClassNameLength;
};

