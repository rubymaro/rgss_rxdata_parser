#include "RubyObject.h"
#include "RubyClass.h"

RubyObject::RubyObject(const char* paClassName, const size_t classNameLength, std::vector<RubyBase*>* const paPtrs, const size_t length, const bool bAddToRef)
	: RubyBase(eRubyTokens::TYPE_OBJECT, paPtrs)
	, ClassName(std::string(paClassName, classNameLength))
	, ChildLength(length)
{
	if (bAddToRef)
	{
		sObjectReferences.push_back(this);
	}
}