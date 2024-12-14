#include "RubyString.h"

RubyString::RubyString(const char* paPtr, const size_t size)
	: RubyObject(eRubyTokens::TYPE_STRING, (void*)paPtr)
	, Size(size)
{
}