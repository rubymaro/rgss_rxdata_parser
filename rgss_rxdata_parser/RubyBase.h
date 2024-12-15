#pragma once

#include "eRubyTokens.h"

struct RubyBase
{
	RubyBase(const eRubyTokens type, void* paPtr);

	eRubyTokens Type;
	void* PAPtr;
};