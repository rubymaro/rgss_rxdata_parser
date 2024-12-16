#include "RubyFixnum.h"

RubyFixnum::RubyFixnum(int* const paPtr)
	: RubyBase(eRubyTokens::TYPE_FIXNUM, paPtr)
{
}
