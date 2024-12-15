#pragma once

#include "RubyBase.h"

struct RubyString : public RubyBase
{
	RubyString(char* const paPtr, const size_t size);
	
	size_t Size;
};

