#pragma once

#include "RubyBase.h"

struct RubyStruct : public RubyBase
{
	RubyStruct(const char* const pStructName, const size_t structNameLength, const size_t capacity);
	virtual ~RubyStruct(void) = default;

	std::string Name;
	std::vector<RubyBase*> StructMemberPtrs;
};

