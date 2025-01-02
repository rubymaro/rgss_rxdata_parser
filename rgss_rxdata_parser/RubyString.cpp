#include "RubyString.h"

RubyString::RubyString(const char* const pSrcString, const size_t length)
	: RubyBase(eRubyTokens::TYPE_STRING)
	, Value(pSrcString, length)
{
	sObjectReferences.push_back(this);
}