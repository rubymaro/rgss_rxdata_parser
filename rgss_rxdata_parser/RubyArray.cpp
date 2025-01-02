#include "RubyArray.h"

RubyArray::RubyArray(const size_t length)
	: RubyBase(eRubyTokens::TYPE_ARRAY)
	, Length(length)
{
	sObjectReferences.push_back(this);
}