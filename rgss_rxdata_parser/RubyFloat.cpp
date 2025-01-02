#include <cstring>
#include <string>

#include "RubyFloat.h"

const char RubyFloat::STATE_NAN[]        = { 'n' ,'a', 'n' };
const char RubyFloat::STATE_INF[]        = { 'i', 'n', 'f' };
const char RubyFloat::STATE_SIGNED_INF[] = { '-', 'i', 'n', 'f' };

RubyFloat::RubyFloat(const char* const pSrcBytes, const size_t byteCount)
	: RubyBase(eRubyTokens::TYPE_FLOAT)
{
	if (byteCount == sizeof(STATE_NAN) && memcmp(pSrcBytes, STATE_NAN, sizeof(STATE_NAN)) == 0)
	{
		State = eStates::Nan;
		Value = -NAN;
	}
	else if (byteCount == sizeof(STATE_INF) && memcmp(pSrcBytes, STATE_INF, sizeof(STATE_INF)) == 0)
	{
		State = eStates::Infinity;
		Value = INFINITY;
	}
	else if (byteCount == sizeof(STATE_SIGNED_INF) && memcmp(pSrcBytes, STATE_SIGNED_INF, sizeof(STATE_SIGNED_INF)) == 0)
	{
		State = eStates::SignedInfinity;
		Value = -INFINITY;
	}
	else
	{
		State = eStates::Normal;
		Value = std::stod(std::string(pSrcBytes, byteCount));
	}

	sObjectReferences.push_back(this);
}
