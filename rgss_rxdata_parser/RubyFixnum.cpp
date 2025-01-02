#include "RubyFixnum.h"

RubyFixnum::RubyFixnum(const int32_t val)
	: RubyBase(eRubyTokens::TYPE_FIXNUM)
	, Value(val)
{
}
