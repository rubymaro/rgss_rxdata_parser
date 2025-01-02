#pragma once

#include <vector>

#include "RubyBase.h"

struct RubySymbol : public RubyBase
{
	RubySymbol(const char* const pSymbolName, const size_t symbolNameLength);

	std::string Name;

	static std::vector<RubySymbol*> sSymbolLinks;
};

