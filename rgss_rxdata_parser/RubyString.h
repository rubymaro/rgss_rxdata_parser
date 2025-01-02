#pragma once

#include "RubyBase.h"

struct RubyString : public RubyBase
{
	RubyString(const char* paPtr, const size_t size);
	
	std::string Value;
};

