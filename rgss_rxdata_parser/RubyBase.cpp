#include "RubyBase.h"

std::vector<RubyBase*> RubyBase::sObjectReferences(1);

RubyBase::RubyBase(const eRubyTokens type)
	: Type(type)
{
}
