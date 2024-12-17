#include "RubyObject.h"
#include "RubyClass.h"

RubyObject::RubyObject(char* const paClassName, const size_t classNameLength, std::vector<RubyBase*>* const paPtrs, const size_t length, const bool bAddToRef)
	: RubyBase(eRubyTokens::TYPE_OBJECT, paPtrs)
	, PAClassName(paClassName)
	, ClassNameLength(classNameLength)
	, ChildLength(length)
{
	if (bAddToRef)
	{
		sObjectReferences.push_back(this);
	}
}