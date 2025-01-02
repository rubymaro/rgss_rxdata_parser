#pragma once

#include "RubyBase.h"

struct RubyNil : public RubyBase
{
	RubyNil(void);
	virtual ~RubyNil(void) = default;
};

