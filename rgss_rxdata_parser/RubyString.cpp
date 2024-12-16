#include "RubyString.h"

RubyString::RubyString(char* const paPtr, const size_t size)
	: RubyBase(eRubyTokens::TYPE_STRING, paPtr)
	, Size(size)
{
	sObjectReferences.push_back(this);
}