#pragma once

#include "RubyBase.h"

struct RubyUserDefined : public RubyBase
{
	RubyUserDefined(char* const paClassName, const size_t classNameLength, char* const paPtr, const size_t bufferLength);

	char* PAClassName;
	size_t ClassNameLength;
	size_t BufferLength;
};

