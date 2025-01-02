#include "RubyUserDefined.h"

RubyUserDefined::RubyUserDefined(const char* const pClassName, const size_t classNameLength, const char* const pSrcBuffer, const size_t bufferLength)
	: RubyBase(eRubyTokens::TYPE_USERDEF)
	, ClassName(pClassName, classNameLength)
	, BufferLength(bufferLength)
{
	PABuffer = new char[bufferLength];
	memcpy(PABuffer, pSrcBuffer, bufferLength);
}

RubyUserDefined::~RubyUserDefined(void)
{
	delete[] PABuffer;
}
