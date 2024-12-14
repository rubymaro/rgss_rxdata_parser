#include <cstring>

#include "RubyFloat.h"

const char RubyFloat::STATE_NAN[]        = { 'n' ,'a', 'n' };
const char RubyFloat::STATE_INF[]        = { 'i', 'n', 'f' };
const char RubyFloat::STATE_SIGNED_INF[] = { '-', 'i', 'n', 'f' };

RubyFloat::RubyFloat(char* const paBytes, const size_t byteCount)
	: RubyObject(eRubyTokens::TYPE_FLOAT, paBytes)
	, ByteCount(byteCount)
{
	if (byteCount == sizeof(STATE_NAN) && memcmp(paBytes, STATE_NAN, sizeof(STATE_NAN)) == 0)
	{
		State = eStates::Nan;
	}
	else if (byteCount == sizeof(STATE_INF) && memcmp(paBytes, STATE_INF, sizeof(STATE_INF)) == 0)
	{
		State = eStates::Infinity;
	}
	else if (byteCount == sizeof(STATE_SIGNED_INF) && memcmp(paBytes, STATE_SIGNED_INF, sizeof(STATE_SIGNED_INF)) == 0)
	{
		State = eStates::SignedInfinity;
	}
	else
	{
		State = eStates::Normal;
	}
}
