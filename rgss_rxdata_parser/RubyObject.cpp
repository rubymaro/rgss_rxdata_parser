#include "RubyObject.h"
#include "RubyClass.h"

RubyObject::RubyObject(const char* const pClassName, const size_t classNameLength, const size_t capacity)
	: RubyBase(eRubyTokens::TYPE_OBJECT)
	, ClassName(pClassName, classNameLength)
{
	ObjectElementPtrs.reserve(capacity);
	sObjectReferences.push_back(this);
}

RubyObject::~RubyObject(void)
{
	for (RubyBase* pRubyBase : ObjectElementPtrs)
	{
		--pRubyBase->RefCount;
		if (pRubyBase->RefCount == 0)
		{
			delete pRubyBase;
		}
	}
	ObjectElementPtrs.clear();
}
