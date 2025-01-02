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
		--pRubyBase->RefCount;
		if (pRubyBase->RefCount == 0)
		{
			delete pRubyBase;
		}
	}
	ArrayElementPtrs.clear();
}
