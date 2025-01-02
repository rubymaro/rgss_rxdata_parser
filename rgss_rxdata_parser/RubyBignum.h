#pragma once

#include "RubyBase.h"

struct RubyBignum : public RubyBase
{
	RubyBignum(const bool bSign, const char* const pSrcBytes, const size_t byteLength);
	virtual ~RubyBignum(void) override;

	bool Sign;
	char* PABytes;
	size_t ByteLength;
};

