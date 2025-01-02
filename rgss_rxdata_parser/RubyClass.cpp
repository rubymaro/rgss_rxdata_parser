#include "RubyClass.h"

RubyClass::RubyClass(const char* const pClassName, const size_t classNameLength)
	: RubyBase(eRubyTokens::TYPE_CLASS)
	, Name(pClassName, classNameLength)
{
	sObjectReferences.push_back(this);
}
