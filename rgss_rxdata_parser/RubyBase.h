#pragma once

#include <vector>
#include <string>

#include "eRubyTokens.h"

struct RubyBase
{
	RubyBase(const eRubyTokens type);
	virtual ~RubyBase(void) = default;

	eRubyTokens Type;

	static std::vector<RubyBase*> sObjectReferences;
};