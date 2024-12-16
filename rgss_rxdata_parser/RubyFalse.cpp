#include "RubyFalse.h"

RubyFalse::RubyFalse(void)
	: RubyBase(eRubyTokens::TYPE_FALSE, new bool(false))
{
}
