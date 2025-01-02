#pragma once

#include "RubyBase.h"

struct RubyUserDefined : public RubyBase
{
	RubyUserDefined(const char* const pClassName, const size_t classNameLength, const char* const pSrcBuffer, const size_t bufferLength);
	~RubyUserDefined(void);

	std::string ClassName;
	char* PABuffer;
	size_t BufferLength;
};

