#include "RubyBignum.h"

RubyBignum::RubyBignum(const bool bSign, const char* const pSrcBytes, const size_t byteLength)
	: RubyBase(eRubyTokens::TYPE_BIGNUM)
	, Sign(bSign)
	, ByteLength(byteLength)
{
	PABytes = new char[byteLength];
	memcpy(PABytes, pSrcBytes, byteLength);

	sObjectReferences.push_back(this);
}

RubyBignum::~RubyBignum(void)
{
	delete[] PABytes;
}
