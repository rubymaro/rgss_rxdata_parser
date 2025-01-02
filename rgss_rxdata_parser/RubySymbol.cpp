#include "RubySymbol.h"

std::vector<RubySymbol*> RubySymbol::sSymbolLinks;

RubySymbol::RubySymbol(const char* const pSymbolName, const size_t symbolNameLength)
	: RubyBase(eRubyTokens::TYPE_SYMBOL)
	, Name(pSymbolName, symbolNameLength)
{
}

RubySymbol::RubySymbol(const RubySymbol& other)
	: RubySymbol(other.Name.c_str(), other.Name.size())
{
}
