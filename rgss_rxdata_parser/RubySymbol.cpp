#include "RubySymbol.h"

RubySymbol::RubySymbol(char* const paPtr, const size_t size)
	: RubyBase(eRubyTokens::TYPE_SYMBOL, paPtr)
	, Size(size)
{
}
