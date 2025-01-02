#include "RubyBignum.h"

RubyBignum::RubyBignum(const bool bSign, char* const bytes, const size_t byteLength)
	: RubyBase(eRubyTokens::TYPE_BIGNUM)
	, Sign(bSign)
	, PABytes(bytes)
	, ByteLength(byteLength)
{
	PABytes = new char[byteLength];
	memcpy(PABytes, bytes, byteLength);

	sObjectReferences.push_back(this);
}

RubyBignum::~RubyBignum(void)
{
	delete[] PABytes;
}
