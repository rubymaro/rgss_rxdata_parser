#pragma once

#include "RubyObject.h"

class RubyArray : public RubyObject
{
public:
	RubyArray(const eRubyTokens type, const void* paPtr, const size_t length);

	size_t Length;
};

