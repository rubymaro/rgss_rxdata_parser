#pragma once

#include "RubyBase.h"

struct RubyObject : public RubyBase
{
	RubyObject(const char* paClassName, const size_t classNameLength, const bool bAddToRef);

	std::string ClassName;
	std::vector<RubyBase*> ObjectElementPtrs;
};

