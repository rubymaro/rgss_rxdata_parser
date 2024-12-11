#include "RubyArray.h"

RubyArray::RubyArray(const eRubyTokens type, const void* paPtr, const size_t length)
	: RubyObject(type, (void*)paPtr)
	, Length(length)
{
}