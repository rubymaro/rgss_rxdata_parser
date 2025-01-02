#pragma once

#include "RubyBase.h"

struct RubyFixnum : public RubyBase
{
	RubyFixnum(const int32_t val);
	virtual ~RubyFixnum(void) = default;

	int32_t Value;
};

