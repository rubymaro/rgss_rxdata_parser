#include "RubyStruct.h"

RubyStruct::RubyStruct(char* const paStructName, size_t structNameLength, std::vector<RubyBase*>* const paPtrs, const size_t length)
	: RubyBase(eRubyTokens::TYPE_STRUCT, paPtrs)
	, ChildLength(length)
	, PAStructName(paStructName)
	, StructNameLength(structNameLength)
{
	sObjectReferences.push_back(this);
}
