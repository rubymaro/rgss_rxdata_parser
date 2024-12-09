#pragma once

#include "eRubyTokens.h"

struct RubyObject
{
	RubyObject(const eRubyTokens type, void* paPtr);

	eRubyTokens Type;
	void* PAPtr;
};