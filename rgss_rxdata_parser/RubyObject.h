#pragma once

#include "RubyBase.h"

struct RubyObject : public RubyBase
{
	RubyObject(const char* paClassName, const size_t classNameLength, std::vector<RubyBase*>* const paPtrs, const size_t length, const bool bAddToRef);

	std::string ClassName;
	size_t ChildLength;
};

