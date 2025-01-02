#include "RubyClass.h"

RubyClass::RubyClass(char* const paClassName, const size_t classNameLength)
	: RubyBase(eRubyTokens::TYPE_CLASS, nullptr)
	, Name(paClassName, classNameLength)
{
	sObjectReferences.push_back(this);
}
