#pragma once

#include "RubyBase.h"

struct RubyFixnum : public RubyBase
{
	RubyFixnum(const int32_t val);
	int32_t Value;
};

