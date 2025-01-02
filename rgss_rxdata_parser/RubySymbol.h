#pragma once

#include <vector>

#include "RubyBase.h"

struct RubySymbol : public RubyBase
{
	RubySymbol(const char* const pSymbolName, const size_t symbolNameLength);
	RubySymbol(const RubySymbol& other);
	virtual ~RubySymbol(void) = default;

	std::string Name;

	static std::vector<RubySymbol*> sSymbolLinks;
};

