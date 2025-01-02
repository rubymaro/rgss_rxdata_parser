#include "RubyUserDefined.h"

RubyUserDefined::RubyUserDefined(const char* const pClassName, const size_t classNameLength, char* const paPtr, const size_t bufferLength)
	: RubyBase(eRubyTokens::TYPE_USERDEF)
	, ClassName(pClassName, classNameLength)
	, PABuffer(paPtr)
	, BufferLength(bufferLength)
{
}
