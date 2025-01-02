#include "RubyUserDefined.h"

RubyUserDefined::RubyUserDefined(const char* paClassName, const size_t classNameLength, char* const paPtr, const size_t bufferLength)
	: RubyBase(eRubyTokens::TYPE_USERDEF, paPtr)
	, ClassName(paClassName, classNameLength)
	, BufferLength(bufferLength)
{
}
