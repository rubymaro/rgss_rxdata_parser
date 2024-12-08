#pragma once

#include "eRubyTokens.h"

class Object
{
public:
	Object(const eRubyTokens type, void* paPtr);
	eRubyTokens mType;
	void* mpaPtr;

protected:

};