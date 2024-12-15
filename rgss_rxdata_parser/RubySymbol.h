#pragma once

#include "RubyBase.h"

struct RubySymbol : public RubyBase
{
	RubySymbol(char* const paPtr, const size_t size);

	size_t Size;
};

