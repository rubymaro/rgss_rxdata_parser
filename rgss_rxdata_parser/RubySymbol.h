#pragma once

#include <vector>

#include "RubyBase.h"

struct RubySymbol : public RubyBase
{
	RubySymbol(char* const paSymbolName, const size_t simbolNameLength);

	size_t SymbolNameLength;

	static std::vector<RubySymbol*> sSymbolLinks;
};

