#pragma once

#include "RubyBase.h"

struct RubyBignum : public RubyBase
{
	RubyBignum(bool bSign, char* bytes, const size_t byteLength);

	bool Sign;
	char* PABytes;
	size_t ByteLength;
};

