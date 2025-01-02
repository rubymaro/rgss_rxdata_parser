#include "RubyArray.h"

RubyArray::RubyArray(const size_t capacity)
	: RubyBase(eRubyTokens::TYPE_ARRAY)
{
	ArrayElementPtrs.reserve(capacity);
	sObjectReferences.push_back(this);
}

RubyArray::~RubyArray(void)
{
	for (RubyBase* pRubyBase : ArrayElementPtrs)
	{
		delete pRubyBase;
	}
	ArrayElementPtrs.clear();
}
