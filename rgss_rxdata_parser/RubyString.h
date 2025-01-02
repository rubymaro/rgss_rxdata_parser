#pragma once

#include "RubyBase.h"

struct RubyString : public RubyBase
{
	RubyString(const char* const pSrcString, const size_t length);
	
	std::string Value;
};

