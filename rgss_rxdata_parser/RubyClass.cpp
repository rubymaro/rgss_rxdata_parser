#include "RubyClass.h"

RubyClass::RubyClass(char* const paClassName, const size_t classNameLength)
	: RubyObject(eRubyTokens::TYPE_CLASS, paClassName)
	, ClassNameLength(classNameLength)
{
}
