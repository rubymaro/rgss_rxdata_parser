#include <cstdio>
#include <cassert>
#include <strsafe.h>
#include <vector>

#include "eRubyTokens.h"
#include "RubyObject.h"
#include "RubyString.h"

std::vector<RubyObject*> gObjectPtrs;

bool ReadBytes(const wchar_t* const pWcsfileName, unsigned char** ppOutData, unsigned int* pDataSize);
bool Parse(const unsigned char* const paBuf, const unsigned int bufSize);

const wchar_t* RubyTokenToString(const eRubyTokens token)
{
	switch (token)
	{
	case eRubyTokens::TYPE_NIL: return L"TYPE_NIL";
	case eRubyTokens::TYPE_TRUE: return L"TYPE_TRUE";
	case eRubyTokens::TYPE_FALSE: return L"TYPE_FALSE";
	case eRubyTokens::TYPE_FIXNUM: return L"TYPE_FIXNUM";
	case eRubyTokens::TYPE_EXTENDED: return L"TYPE_EXTENDED";
	case eRubyTokens::TYPE_UCLASS: return L"TYPE_UCLASS";
	case eRubyTokens::TYPE_OBJECT: return L"TYPE_OBJECT";
	case eRubyTokens::TYPE_DATA: return L"TYPE_DATA";
	case eRubyTokens::TYPE_USERDEF: return L"TYPE_USERDEF";
	case eRubyTokens::TYPE_USRMARSHAL: return L"TYPE_USRMARSHAL";
	case eRubyTokens::TYPE_FLOAT: return L"TYPE_FLOAT";
	case eRubyTokens::TYPE_BIGNUM: return L"TYPE_BIGNUM";
	case eRubyTokens::TYPE_STRING: return L"TYPE_STRING";
	case eRubyTokens::TYPE_REGEXP: return L"TYPE_REGEXP";
	case eRubyTokens::TYPE_ARRAY: return L"TYPE_ARRAY";
	case eRubyTokens::TYPE_HASH: return L"TYPE_HASH";
	case eRubyTokens::TYPE_HASH_DEF: return L"TYPE_HASH_DEF";
	case eRubyTokens::TYPE_STRUCT: return L"TYPE_STRUCT";
	case eRubyTokens::TYPE_MODULE_OLD: return L"TYPE_MODULE_OLD";
	case eRubyTokens::TYPE_CLASS: return L"TYPE_CLASS";
	case eRubyTokens::TYPE_MODULE: return L"TYPE_MODULE";
	case eRubyTokens::TYPE_SYMBOL: return L"TYPE_SYMBOL";
	case eRubyTokens::TYPE_SYMLINK: return L"TYPE_SYMLINK";
	case eRubyTokens::TYPE_IVAR: return L"TYPE_IVAR";
	case eRubyTokens::TYPE_LINK: return L"TYPE_LINK";
	default: return L"UNKNOWN_TOKEN";
	}
}


bool ReadBytes(const wchar_t* const pWcsfileName, unsigned char** ppOutData, unsigned int* pDataSize)
{
	FILE* pFile = nullptr;
	errno_t err;
	unsigned int bufSize;
	unsigned int readByte;
	unsigned char* paBuf = nullptr;
	bool bSuccess = false;

	do
	{
		err = _wfopen_s(&pFile, pWcsfileName, L"rb");
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

		paBuf = new unsigned char[bufSize];
		readByte = (unsigned int)fread_s(paBuf, bufSize, sizeof(unsigned char), bufSize, pFile);

		bSuccess = true;

		*ppOutData = paBuf;
		*pDataSize = readByte;

	} while (0);

	if (pFile != nullptr)
	{
		fclose(pFile);
	}

	return bSuccess;
}

bool ProcessFixnum(const unsigned char** ppToken, int* outVal)
{
	const int fixnumHeader = (*ppToken)[0];
	int retFixnum = -1;

	switch (fixnumHeader)
	{
	case 0x00: // 0
		retFixnum = fixnumHeader;
		(*ppToken) += 1;
		break;

	case 0x01: // unsigned [0x7B, 0xFF]
		retFixnum = (*ppToken)[1];
		(*ppToken) += 2;
		break;

	case 0x02: // unsigned [0x0100, 0xFFFF]
		retFixnum = (*ppToken)[1] | (*ppToken)[2] << 8;
		(*ppToken) += 3;
		break;

	case 0x03: // unsigned [0x010000, 0xFFFFFF]
		retFixnum = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16;
		(*ppToken) += 4;
		break;

	case 0x04: // unsigned [0x01000000, 0x3FFFFFFF]
		__fallthrough;
	case 0xFC: // signed [0xC0000000, 0xFEFFFFFF] => [-1073741824, -16777217]
		retFixnum = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16 | (*ppToken)[4] << 24;
		(*ppToken) += 5;
		break;

	case 0xFF: // signed [0x00, 0x84] => [-256, -124]
		retFixnum = ~(*ppToken)[1];
		retFixnum &= 0x000000ff;
		retFixnum = -(retFixnum + 1);
		(*ppToken) += 2;
		break;

	case 0xFE: // signed [0x0000, 0xFEFF] => [-65536, -257]
		retFixnum = (*ppToken)[1] | (*ppToken)[2] << 8;
		retFixnum = ~retFixnum;
		retFixnum &= 0x0000ffff;
		retFixnum = -(retFixnum + 1);
		(*ppToken) += 3;
		break;

	case 0xFD: // signed [0x000000, 0xFEFFFF] => [-16777216, -65537]
		retFixnum = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16;
		retFixnum = ~retFixnum;
		retFixnum &= 0x00ffffff;
		retFixnum = -(retFixnum + 1);
		(*ppToken) += 4;
		break;

	default:
		if (fixnumHeader >= 0x06 && fixnumHeader <= 0x7F)
		{
			retFixnum = static_cast<char>(fixnumHeader - 0x05); // unsigned [0x01, 0x7A]
			(*ppToken) += 1;
		}
		else if (fixnumHeader >= 0x80 && fixnumHeader <= 0xFA) 
		{
			retFixnum = static_cast<char>(fixnumHeader + 0x05); // signed [0x85, 0xFF] => [-123, -1]
			(*ppToken) += 1;
		}
		else
		{
			return false;
		}
		break;
	}

	*outVal = retFixnum;

	return true;
}

bool ProcessStringUTF8(const unsigned char** ppToken, char** ppaString, size_t* pOutLength)
{
	assert(ppToken != nullptr);
	assert(ppaString != nullptr);
	assert(pOutLength != nullptr);

	// skip the string header
	++(*ppToken);

	const int stringLengthHeader = (*ppToken)[0];
	size_t utf8ByteLength = 0;

	switch (stringLengthHeader)
	{
	case 0x00: // zero length
		(*ppToken)++;
		break;

	case 0x01:
		utf8ByteLength = (*ppToken)[1];
		(*ppToken) += 2;
		break;

	case 0x02:
		utf8ByteLength = (*ppToken)[1] | (*ppToken)[2] << 8;
		(*ppToken) += 3;
		break;

	case 0x03:
		utf8ByteLength = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16;
		(*ppToken) += 4;
		break;

	case 0x04:
		utf8ByteLength = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16 | (*ppToken)[4] << 24;
		(*ppToken) += 5;
		break;

	default:
		if (stringLengthHeader >= 0x05 && stringLengthHeader <= 0xff)
		{
			utf8ByteLength = stringLengthHeader - 0x05;
			(*ppToken) += 1;
			break;
		}
		else
		{
			return false;
		}
	}

	*ppaString = new char[utf8ByteLength];
	memcpy(*ppaString, reinterpret_cast<const char*>(*ppToken), utf8ByteLength);
	*pOutLength = utf8ByteLength;

	(*ppToken) += utf8ByteLength;

	return true;
}

bool Parse(const unsigned char* const paBuf, const unsigned int bufSize)
{
	assert(paBuf != nullptr);
	assert(bufSize > 0);

	const unsigned char* pToken = paBuf;
	const unsigned char* const pEnd = paBuf + bufSize;

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

	int val;
	char* paString = nullptr;
	size_t stringLength = 0;

	while (pToken < pEnd)
	{
		switch ((eRubyTokens)(*pToken))
		{
		case eRubyTokens::TYPE_NIL:
			++pToken;
			gObjectPtrs.push_back(new RubyObject(eRubyTokens::TYPE_NIL, nullptr));
			break;

		case eRubyTokens::TYPE_TRUE:
			++pToken;
			gObjectPtrs.push_back(new RubyObject(eRubyTokens::TYPE_TRUE, new bool(true)));
			break;

		case eRubyTokens::TYPE_FALSE:
			++pToken;
			gObjectPtrs.push_back(new RubyObject(eRubyTokens::TYPE_FALSE, new bool(false)));
			break;

		case eRubyTokens::TYPE_FIXNUM:
			++pToken;
			ProcessFixnum(&pToken, &val);
			gObjectPtrs.push_back(new RubyObject(eRubyTokens::TYPE_FIXNUM, new int(val)));
			break;

		case eRubyTokens::TYPE_STRING:
			ProcessStringUTF8(&pToken, &paString, &stringLength);
			gObjectPtrs.push_back(new RubyString(eRubyTokens::TYPE_STRING, paString, stringLength));
			break;

		case eRubyTokens::TYPE_ARRAY:
			++pToken;
			ProcessFixnum(&pToken, &val);
			printf("array length = %d\n", val);
			break;

		default:
			return false;
		}
	}

	return true;
}

int wmain(const int argc, const wchar_t* argv[])
{
	unsigned char* paBuf;
	unsigned int bufSize;

	gObjectPtrs.reserve(10000);

	if (ReadBytes(L"marshals/marshal/nil.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/true.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/false.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/0x12345678.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/06_Fixnum_16777216.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/06_Fixnum_16777217.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-1.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-123.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-124.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-256.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-257.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-65534.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-65535.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-65536.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-65537.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-16777215.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-16777216.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}
	
	if (ReadBytes(L"marshals/marshal/08_Fixnum_-16777217.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-1073741824.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-1073741825.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/String_abcd.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}
	
	if (ReadBytes(L"marshals/marshal/String_0123가나다라ABCD.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/String_empty.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/String_long063.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/array_empty.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/array_nil1.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/array_nil_122.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/array_nil_123.rxdata", &paBuf, &bufSize))
	{
		Parse(paBuf, bufSize);
		delete[] paBuf;
		paBuf = nullptr;
	}



	for (const RubyObject* pObject : gObjectPtrs)
	{
		wprintf(L"%s(%c) -> %p\n", RubyTokenToString(pObject->Type), pObject->Type, pObject->PAPtr);
	}

	return 0;
}