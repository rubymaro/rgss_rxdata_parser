#include "RubyString.h"

RubyString::RubyString(const char* const pString, const size_t length)
	: RubyBase(eRubyTokens::TYPE_STRING)
	, Value(pString, length)
{
	sObjectReferences.push_back(this);
}