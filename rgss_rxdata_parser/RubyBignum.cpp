#include "RubyBignum.h"

RubyBignum::RubyBignum(bool bSign, char* bytes, const size_t byteLength)
	: RubyBase(eRubyTokens::TYPE_BIGNUM)
	, Sign(bSign)
	, PABytes(bytes)
	, ByteLength(byteLength)
{
	sObjectReferences.push_back(this);
}
