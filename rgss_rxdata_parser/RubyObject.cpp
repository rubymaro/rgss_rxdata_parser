#include "RubyObject.h"
#include "RubyClass.h"

RubyObject::RubyObject(const char* paClassName, const size_t classNameLength, const bool bAddToRef)
	: RubyBase(eRubyTokens::TYPE_OBJECT)
	, ClassName(paClassName, classNameLength)
{
	if (bAddToRef)
	{
		sObjectReferences.push_back(this);
	}
}