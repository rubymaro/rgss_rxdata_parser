#pragma once

enum
{
	MARSHAL_MAJOR = 4,
	MARSHAL_MINOR = 8,

	TYPE_NIL = '0',    // void*:nullptr
	TYPE_TRUE = 'T',   // bool:true
	TYPE_FALSE = 'F',  // bool:false
	TYPE_FIXNUM = 'i', // int32_t

	TYPE_EXTENDED = 'e',
	TYPE_UCLASS = 'C',
	TYPE_OBJECT = 'o',
	TYPE_DATA = 'd',
	TYPE_USERDEF = 'u',
	TYPE_USRMARSHAL = 'U',
	TYPE_FLOAT = 'f',
	TYPE_BIGNUM = 'l',
	TYPE_STRING = '"',
	TYPE_REGEXP = '/',
	TYPE_ARRAY = '[',
	TYPE_HASH = '{',
	TYPE_HASH_DEF = '}',
	TYPE_STRUCT = 'S',
	TYPE_MODULE_OLD = 'M',
	TYPE_CLASS = 'c',
	TYPE_MODULE = 'm',

	TYPE_SYMBOL = ':',
	TYPE_SYMLINK = ';',

	TYPE_IVAR = 'I',
	TYPE_LINK = '@',
};