#pragma once

#include "RubyObject.h"

struct RubyString : public RubyObject
{
	RubyString(const char* paPtr, const size_t size);
	
	size_t Size;
};

