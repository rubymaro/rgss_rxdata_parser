#include "RubyString.h"

RubyString::RubyString(const char* paPtr, const size_t size)
	: RubyBase(eRubyTokens::TYPE_STRING)
	, Value(paPtr, size)
{
	sObjectReferences.push_back(this);
}