#pragma once

#include "RubyBase.h"

struct RubyUserDefined : public RubyBase
{
	RubyUserDefined(const char* const pClassName, const size_t classNameLength, char* const paPtr, const size_t bufferLength);

	std::string ClassName;

	char* PABuffer;
	size_t BufferLength;
};

