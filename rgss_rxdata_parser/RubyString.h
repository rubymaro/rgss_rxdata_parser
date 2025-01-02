#pragma once

#include "RubyBase.h"

struct RubyString : public RubyBase
{
	RubyString(const char* const pString, const size_t length);
	
	std::string Value;
};

