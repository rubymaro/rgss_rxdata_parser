#pragma once

#include "RubyBase.h"

struct RubyStruct : public RubyBase
{
	RubyStruct(const char* paStructName, size_t structNameLength);

	std::string Name;
	std::vector<RubyBase*> StructMemberPtrs;
};

