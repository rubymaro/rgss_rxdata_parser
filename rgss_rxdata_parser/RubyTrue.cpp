#include "RubyTrue.h"

RubyTrue::RubyTrue()
	: RubyBase(eRubyTokens::TYPE_TRUE, new bool(true))
{
}
