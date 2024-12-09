#include "RubyObject.h"

RubyObject::RubyObject(const eRubyTokens type, void* paPtr)
	: Type(type)
	, PAPtr(paPtr)
{
}
