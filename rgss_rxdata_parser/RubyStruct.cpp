#include "RubyStruct.h"

RubyStruct::RubyStruct(const char* paStructName, size_t structNameLength)
	: RubyBase(eRubyTokens::TYPE_STRUCT)
	, Name(paStructName, structNameLength)
{
	sObjectReferences.push_back(this);
}
