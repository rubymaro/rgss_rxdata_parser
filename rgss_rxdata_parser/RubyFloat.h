#pragma once

#include "RubyBase.h"

struct RubyFloat : public RubyBase
{
	static const char STATE_NAN[];
	static const char STATE_INF[];
	static const char STATE_SIGNED_INF[];

	enum class eStates
	{
		Normal = 0,
		Nan = 1,
		Infinity = 2,
		SignedInfinity = 3
	};

	RubyFloat(char* const paBytes, const size_t byteCount);

	size_t ByteCount;
	eStates State;
	double Value;
};

