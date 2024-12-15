#include "RubyBignum.h"

RubyBignum::RubyBignum(bool bSign, const size_t byteLength, char* bytes)
	: RubyBase(eRubyTokens::TYPE_BIGNUM, bytes)
	, Sign(bSign)
	, ByteLength(byteLength)
{
}
