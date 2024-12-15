#pragma once

#include <vector>

#include "RubyBase.h"

struct RubyStruct : public RubyBase
{
	RubyStruct(char* const paStructName, size_t structNameLength, std::vector<RubyBase*>* const paPtrs, const size_t length);

	size_t ChildLength;
	char* PAStructName;
	size_t StructNameLength;
};

