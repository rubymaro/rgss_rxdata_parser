#pragma once

#include "RubyBase.h"

struct RubyStruct : public RubyBase
{
	RubyStruct(const char* paStructName, size_t structNameLength, std::vector<RubyBase*>* const paPtrs, const size_t length);

	std::string Name;
	size_t ChildLength;
};

