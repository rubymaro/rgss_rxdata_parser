#include "RubyFixnum.h"

RubyFixnum::RubyFixnum(const int val)
	: RubyBase(eRubyTokens::TYPE_FIXNUM, new int(val))
{
}
