#include "RubyArray.h"

RubyArray::RubyArray(std::vector<RubyBase*>* const paPtrs, const size_t length)
	: RubyBase(eRubyTokens::TYPE_ARRAY, paPtrs)
	, Length(length)
{
	sObjectReferences.push_back(this);
}