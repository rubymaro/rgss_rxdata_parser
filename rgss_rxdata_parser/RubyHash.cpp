#include "RubyHash.h"

RubyHash::RubyHash(std::vector<RubyObject*>* const paPtrs, const size_t pairCount)
	: RubyObject(eRubyTokens::TYPE_HASH, paPtrs)
	, PairCount(pairCount)
{
}
