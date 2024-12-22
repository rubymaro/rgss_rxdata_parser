#include "RubyUserDefined.h"

RubyUserDefined::RubyUserDefined(char* const paClassName, const size_t classNameLength, char* const paPtr, const size_t bufferLength)
	: RubyBase(eRubyTokens::TYPE_USERDEF, paPtr)
	, PAClassName(paClassName)
	, ClassNameLength(classNameLength)
	, BufferLength(bufferLength)
{
}
