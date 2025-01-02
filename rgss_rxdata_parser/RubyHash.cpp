#include "RubyHash.h"

RubyHash::RubyHash(const size_t capacity)
	: RubyBase(eRubyTokens::TYPE_HASH)
{
	HashElementPtrs.reserve(capacity);
	sObjectReferences.push_back(this);
}

RubyHash::~RubyHash(void)
{
	for (RubyBase* pRubyBase : HashElementPtrs)
	{
		delete pRubyBase;
	}
}
