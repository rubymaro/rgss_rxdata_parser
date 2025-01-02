#include "RubyStruct.h"

RubyStruct::RubyStruct(const char* const pStructName, const size_t structNameLength, const size_t capacity)
	: RubyBase(eRubyTokens::TYPE_STRUCT)
	, Name(pStructName, structNameLength)
{
	StructMemberPtrs.reserve(capacity);
	sObjectReferences.push_back(this);
}
