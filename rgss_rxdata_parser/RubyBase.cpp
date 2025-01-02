#include "RubyBase.h"

std::vector<RubyBase*> RubyBase::sObjectReferences;

RubyBase::RubyBase(const eRubyTokens type)
	: Type(type)
	, RefCount(1)
{
}
