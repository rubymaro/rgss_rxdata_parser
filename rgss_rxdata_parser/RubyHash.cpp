#include "RubyHash.h"

RubyHash::RubyHash(const size_t pairCount)
	: RubyBase(eRubyTokens::TYPE_HASH)
	, PairCount(pairCount)
{
	sObjectReferences.push_back(this);
}
