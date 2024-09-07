#include <cstdio>

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

int wmain(const int argc, const wchar_t* argv[])
{
	FILE* pFile = nullptr;
	errno_t err;
	long size;
	char* paBuf = nullptr;
	size_t readByte;
	char* pCur;

	do
	{
		err = _wfopen_s(&pFile, L"nil.rxdata", L"rb");
		if (err != 0 || pFile == nullptr)
		{
			break;
		}

		fseek(pFile, 0, SEEK_END);
		size = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		if (size < 2)
		{
			break;
		}

		paBuf = new char[size];

		readByte = fread_s(paBuf, size, sizeof(char), size, pFile);
		fclose(pFile);

		pCur = paBuf;
		if (*pCur != MARSHAL_MAJOR)
		{
			break;
		}
		++pCur;

		if (*pCur != MARSHAL_MINOR)
		{
			break;
		}
		++pCur;

		return 0;


	} while (0);

	if (paBuf != nullptr)
	{
		delete[] paBuf;
	}

	return 1;
}