#pragma once

#include "RubyObject.h"

struct RubyBignum : public RubyObject
{
	RubyBignum(bool bSign, const size_t byteLength, char* bytes);

	bool Sign;
	size_t ByteLength;
};

