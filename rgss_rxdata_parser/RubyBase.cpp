#include "RubyBase.h"

std::vector<RubyBase*> RubyBase::sObjectReferences(1);

RubyBase::RubyBase(const eRubyTokens type, void* paPtr)
	: Type(type)
	, PAPtr(paPtr)
{
}
