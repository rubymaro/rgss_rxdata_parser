#include "RubyBignum.h"

RubyBignum::RubyBignum(bool bSign, const size_t byteLength, char* bytes)
	: RubyObject(eRubyTokens::TYPE_BIGNUM, bytes)
	, Sign(bSign)
	, ByteLength(byteLength)
{
}
