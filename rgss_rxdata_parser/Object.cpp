#include "Object.h"

Object::Object(const eRubyTokens type, void* paPtr)
	: mType(type)
	, mpaPtr(paPtr)
{
}
