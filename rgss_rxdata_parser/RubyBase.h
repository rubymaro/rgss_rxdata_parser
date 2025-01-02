#pragma once

#include <vector>
#include <string>

#include "eRubyTokens.h"

struct RubyBase
{
	RubyBase(const eRubyTokens type);
	virtual ~RubyBase(void) = default;

	eRubyTokens Type;
	uint32_t RefCount;

	static std::vector<RubyBase*> sObjectReferences;
};