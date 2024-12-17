#pragma once

#include "RubyBase.h"

struct RubyObject : public RubyBase
{
	RubyObject(char* const paClassName, const size_t classNameLength, std::vector<RubyBase*>* const paPtrs, const size_t length, const bool bAddToRef);

	size_t ChildLength;
	char* PAClassName;
	size_t ClassNameLength;
};

