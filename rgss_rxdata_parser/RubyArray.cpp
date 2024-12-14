#include "RubyArray.h"

RubyArray::RubyArray(std::vector<RubyObject*>* const paPtrs, const size_t length)
	: RubyObject(eRubyTokens::TYPE_ARRAY, paPtrs)
	, Length(length)
{
}