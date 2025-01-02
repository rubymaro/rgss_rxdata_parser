#pragma once

#include "RubyBase.h"

struct RubyObject : public RubyBase
{
	RubyObject(const char* const pClassName, const size_t classNameLength, const size_t capacity);
	virtual ~RubyObject(void) = default;

	std::string ClassName;
	std::vector<RubyBase*> ObjectElementPtrs;
};

