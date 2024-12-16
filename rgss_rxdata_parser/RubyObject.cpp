#include "RubyObject.h"

RubyObject::RubyObject(char* const paClassName, const size_t classNameLength)
	: RubyBase(eRubyTokens::TYPE_OBJECT, nullptr)
	, PAClassName(paClassName)
	, ClassNameLength(classNameLength)
{
}
