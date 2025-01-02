#include "RubySymbol.h"

std::vector<RubySymbol*> RubySymbol::sSymbolLinks;

RubySymbol::RubySymbol(char* const paSymbolName, const size_t symbolNameLength)
	: RubyBase(eRubyTokens::TYPE_SYMBOL, nullptr)
	, Name(paSymbolName, symbolNameLength)
{
}
