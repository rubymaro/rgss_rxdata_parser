#include <cstdio>
#include <cassert>

enum
{
	MARSHAL_MAJOR = 4,
	MARSHAL_MINOR = 8,

	TYPE_NIL = '0',
	TYPE_TRUE = 'T',
	TYPE_FALSE = 'F',
	TYPE_FIXNUM = 'i',

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

bool Parse(const char* const paBuf, unsigned int bufSize)
{
	assert(paBuf != nullptr);
	const char* pToken = paBuf;
	
	pToken = paBuf;
	if (*pToken != MARSHAL_MAJOR)
	{
		return false;
	}
	++pToken;

	if (*pToken != MARSHAL_MINOR)
	{
		return false;
	}
	++pToken;

	

	return true;
}

int wmain(const int argc, const wchar_t* argv[])
{
	FILE* pFile = nullptr;
	errno_t err;
	unsigned int bufSize;
	unsigned int  readByte;
	char* paBuf = nullptr;

	do
	{
		err = _wfopen_s(&pFile, L"nil.rxdata", L"rb");
		if (err != 0 || pFile == nullptr)
		{
			break;
		}

		fseek(pFile, 0, SEEK_END);
		bufSize = (unsigned int)ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		if (bufSize < 2)
		{
			break;
		}

		paBuf = new char[bufSize];
		readByte = (unsigned int)fread_s(paBuf, bufSize, sizeof(char), bufSize, pFile);
		fclose(pFile);
		assert(readByte == bufSize);

		Parse(paBuf, bufSize);

		delete[] paBuf;

		return 0;

	} while (0);	

	return 1;
}