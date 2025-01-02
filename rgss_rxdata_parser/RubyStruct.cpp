#include "RubyStruct.h"

RubyStruct::RubyStruct(const char* paStructName, const size_t structNameLength, std::vector<RubyBase*>* const paPtrs, const size_t length)
	: RubyBase(eRubyTokens::TYPE_STRUCT, paPtrs)
	, Name(paStructName, structNameLength)
	, ChildLength(length)
{
	sObjectReferences.push_back(this);
}
