#pragma once

#include "RubyBase.h"

struct RubyUserDefined : public RubyBase
{
	RubyUserDefined(const char* const pClassName, const size_t classNameLength, const char* const pSrcBuffer, const size_t bufferLength);
	virtual ~RubyUserDefined(void) override;

	std::string ClassName;
	char* PABuffer;
	size_t BufferLength;
};

