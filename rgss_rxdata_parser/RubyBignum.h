#pragma once

#include "RubyBase.h"

struct RubyBignum : public RubyBase
{
	RubyBignum(bool bSign, const size_t byteLength, char* bytes);

	bool Sign;
	size_t ByteLength;
};

