#pragma once

#include <vector>

#include "eRubyTokens.h"

struct RubyBase
{
	RubyBase(const eRubyTokens type, void* paPtr);

	eRubyTokens Type;
	void* PAPtr;

	static std::vector<RubyBase*> sObjectReferences;
};