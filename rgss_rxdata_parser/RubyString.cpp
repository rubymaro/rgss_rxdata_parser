#include "RubyString.h"

RubyString::RubyString(char* const paPtr, const size_t size)
	: RubyObject(eRubyTokens::TYPE_STRING, paPtr)
	, Size(size)
{
}