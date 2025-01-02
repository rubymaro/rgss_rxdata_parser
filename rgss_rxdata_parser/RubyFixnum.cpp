#include "RubyFixnum.h"

RubyFixnum::RubyFixnum(const int32_t val)
	: RubyBase(eRubyTokens::TYPE_FIXNUM, new int32_t(val))
{
}
