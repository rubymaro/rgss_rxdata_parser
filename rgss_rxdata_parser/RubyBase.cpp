#include "RubyBase.h"

std::vector<RubyBase*> RubyBase::sObjectReferences;

RubyBase::RubyBase(const eRubyTokens type, void* paPtr)
	: Type(type)
	, PAPtr(paPtr)
{
}
