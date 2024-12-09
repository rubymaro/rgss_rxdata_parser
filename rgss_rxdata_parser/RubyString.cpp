#include "RubyString.h"

RubyString::RubyString(const eRubyTokens token, const char* paPtr, const size_t size)
	: RubyObject(token, (void*)paPtr)
	, Size(size)
{
}