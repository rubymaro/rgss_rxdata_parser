#pragma once

#include "RubyBase.h"

struct RubyBignum : public RubyBase
{
	RubyBignum(const bool bSign, char* const bytes, const size_t byteLength);
	~RubyBignum(void);

	bool Sign;
	char* PABytes;
	size_t ByteLength;
};

