#include "RubyHash.h"

RubyHash::RubyHash(std::vector<RubyBase*>* const paPtrs, const size_t pairCount)
	: RubyBase(eRubyTokens::TYPE_HASH, paPtrs)
	, PairCount(pairCount)
{
}
