#include <cstdio>
#include <cassert>
#include <strsafe.h>
#include <vector>

#include "eRubyTokens.h"
#include "RubyBase.h"
#include "RubyNil.h"
#include "RubyTrue.h"
#include "RubyFalse.h"
#include "RubyFixnum.h"
#include "RubyString.h"
#include "RubyArray.h"
#include "RubyHash.h"
#include "RubyBignum.h"
#include "RubyFloat.h"
#include "RubyClass.h"
#include "RubySymbol.h"
#include "RubyStruct.h"
#include "RubyObject.h"

bool ReadBytes(const wchar_t* const pWcsfileName, unsigned char** ppOutData, unsigned int* pDataSize);
bool StartParse(unsigned char* const paBuf, const unsigned int bufSize, std::vector<RubyBase*>& currentObjectPtrs);
bool ParseRecursive(unsigned char** ppToken, const unsigned char* const pEnd, std::vector<RubyBase*>& currentObjectPtrs);
bool ProcessFixnum(unsigned char** ppToken, int* outVal);
bool ProcessStringUTF8(unsigned char** ppToken, char** ppaString, size_t* pOutLength);
bool ProcessSymbol(unsigned char** ppToken, char** ppaSymbol, size_t* pOutLength);
const wchar_t* RubyTokenToString(const eRubyTokens token);

int wmain(const int argc, const wchar_t* argv[])
{
	unsigned char* paBuf;
	unsigned int bufSize;
	std::vector<RubyBase*> rootObjectPtrs;

	rootObjectPtrs.reserve(10000);

	/*
	if (ReadBytes(L"marshals/marshal/nil.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/true.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/false.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/0x12345678.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/06_Fixnum_16777216.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/06_Fixnum_16777217.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-1.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-123.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-124.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-256.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/07_Fixnum_-257.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-65534.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-65535.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-65536.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-65537.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-16777215.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-16777216.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-16777217.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-1073741824.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/08_Fixnum_-1073741825.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/String_abcd.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/String_0123가나다라ABCD.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/String_empty.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/String_long063.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/array_empty.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/array_nil_122.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/array_nil_123.rxdata", &paBuf, &bufSize))
	{
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/array_2d.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/hash_new.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/hash_simple.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/hash_simple2.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}
	
	if (ReadBytes(L"marshals/marshal/hash_simple3.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/hash_new_0.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/hash_new_32.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/hash_new_default_key_val.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/bignum_2_exp_30.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/bignum_2_exp_31.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}
	if (ReadBytes(L"marshals/marshal/bignum_2_exp_32.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}
	if (ReadBytes(L"marshals/marshal/bignum_2_exp_33.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}
	if (ReadBytes(L"marshals/marshal/bignum_2_exp_34.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}
	if (ReadBytes(L"marshals/marshal/bignum_2_exp_99.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}
	if (ReadBytes(L"marshals/marshal/bignum_2_exp_100.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}
	if (ReadBytes(L"marshals/marshal/bignum_2_exp_200.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/float_0.999999999999.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/float_1.0.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/float_3.141592.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/float_inf.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/float_-inf.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/float_nan.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/struct_customer.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/struct_abc_chocolate.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	if (ReadBytes(L"marshals/marshal/struct_customer_instance_dave.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}
	*/

	if (ReadBytes(L"marshals/marshal/class_abc_chocolate_instance.rxdata", &paBuf, &bufSize))
	{
		rootObjectPtrs.clear();
		StartParse(paBuf, bufSize, rootObjectPtrs);
		delete[] paBuf;
		paBuf = nullptr;
	}

	for (const RubyBase* pObject : rootObjectPtrs)
	{
		wprintf(L"%s (%c) -> %p\n", RubyTokenToString(pObject->Type), pObject->Type, pObject->PAPtr);
	}

	return 0;
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

bool StartParse(unsigned char* const paBuf, const unsigned int bufSize, std::vector<RubyBase*>& currentObjectPtrs)
{
	assert(paBuf != nullptr);
	assert(bufSize > 0);

	unsigned char* pToken = paBuf;
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

	return ParseRecursive(&pToken, pEnd, currentObjectPtrs);
}

bool ProcessFixnum(unsigned char** ppToken, int* outVal)
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

bool ProcessStringUTF8(unsigned char** ppToken, char** ppaString, size_t* pOutLength)
{
	assert(ppToken != nullptr);
	assert(ppaString != nullptr);
	assert(pOutLength != nullptr);

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

bool ProcessSymbol(unsigned char** ppToken, char** ppaSymbol, size_t* pOutLength)
{
	assert(ppToken != nullptr);
	assert(ppaSymbol != nullptr);
	assert(pOutLength != nullptr);

	const int symbolLengthHeader = (*ppToken)[0];
	size_t symbolLength = 0;

	switch (symbolLengthHeader)
	{
	case 0x00: // zero length
		(*ppToken)++;
		break;

	case 0x01:
		symbolLength = (*ppToken)[1];
		(*ppToken) += 2;
		break;

	case 0x02:
		symbolLength = (*ppToken)[1] | (*ppToken)[2] << 8;
		(*ppToken) += 3;
		break;

	case 0x03:
		symbolLength = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16;
		(*ppToken) += 4;
		break;

	case 0x04:
		symbolLength = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16 | (*ppToken)[4] << 24;
		(*ppToken) += 5;
		break;

	default:
		if (symbolLengthHeader >= 0x05 && symbolLengthHeader <= 0xff)
		{
			symbolLength = symbolLengthHeader - 0x05;
			(*ppToken) += 1;
			break;
		}
		else
		{
			return false;
		}
	}

	*ppaSymbol = new char[symbolLength];
	memcpy(*ppaSymbol, reinterpret_cast<const char*>(*ppToken), symbolLength);
	*pOutLength = symbolLength;

	(*ppToken) += symbolLength;

	return true;
}

bool ParseRecursive(unsigned char** ppToken, const unsigned char* const pEnd, std::vector<RubyBase*>& currentObjectPtrs)
{
	int val;
	int repCount;
	char* paBuffer;
	size_t bufferLength;
	bool bSignBignum;
	std::vector<RubyBase*>* paChildObjectPtrs;
	int hashDefault = 0;

	assert(*ppToken <= pEnd);
	if (*ppToken == pEnd)
	{
		return true;
	}

	switch (static_cast<eRubyTokens>(**ppToken))
	{
	case eRubyTokens::TYPE_NIL:
		++(*ppToken);
		currentObjectPtrs.push_back(new RubyNil());
		break;

	case eRubyTokens::TYPE_TRUE:
		++(*ppToken);
		currentObjectPtrs.push_back(new RubyTrue());
		break;

	case eRubyTokens::TYPE_FALSE:
		++(*ppToken);
		currentObjectPtrs.push_back(new RubyFalse());
		break;

	case eRubyTokens::TYPE_FIXNUM:
		++(*ppToken); 
		ProcessFixnum(ppToken, &val);
		currentObjectPtrs.push_back(new RubyFixnum(val));
		break;

	case eRubyTokens::TYPE_STRING:
		++(*ppToken);
		ProcessStringUTF8(ppToken, &paBuffer, &bufferLength);
		currentObjectPtrs.push_back(new RubyString(paBuffer, bufferLength));
		break;

	case eRubyTokens::TYPE_ARRAY:
		++(*ppToken);
		ProcessFixnum(ppToken, &val);
		paChildObjectPtrs = new std::vector<RubyBase*>();
		paChildObjectPtrs->reserve(val);
		currentObjectPtrs.push_back(new RubyArray(paChildObjectPtrs, val));
		for (repCount = 0; repCount < val; ++repCount)
		{
			ParseRecursive(ppToken, pEnd, *paChildObjectPtrs);
		}
		break;

	case eRubyTokens::TYPE_HASH_DEF:
		hashDefault = 1;
		__fallthrough;
	case eRubyTokens::TYPE_HASH:
		++(*ppToken);
		ProcessFixnum(ppToken, &val);
		val = val * 2 + hashDefault; // <key, value> + default value
		paChildObjectPtrs = new std::vector<RubyBase*>();
		paChildObjectPtrs->reserve(val);
		currentObjectPtrs.push_back(new RubyHash(paChildObjectPtrs, val));
		for (repCount = 0; repCount < val; ++val)
		{
			ParseRecursive(ppToken, pEnd, *paChildObjectPtrs);
		}
		break;

	case eRubyTokens::TYPE_BIGNUM:
		++(*ppToken);

		assert((**ppToken) == static_cast<char>(eRubyTokens::TYPE_BIGNUM_PLUS_SIGN)
			|| (**ppToken) == static_cast<char>(eRubyTokens::TYPE_BIGNUM_MINUS_SIGN));
		bSignBignum = ((**ppToken) == static_cast<char>(eRubyTokens::TYPE_BIGNUM_MINUS_SIGN));
		++(*ppToken);

		ProcessFixnum(ppToken, &val);
		val *= 2;
			
		paBuffer = new char[val];
		memcpy(paBuffer, *ppToken, val);
		currentObjectPtrs.push_back(new RubyBignum(bSignBignum, val, paBuffer));

		(*ppToken) += val;
		break;

	case eRubyTokens::TYPE_FLOAT:
		++(*ppToken);

		ProcessFixnum(ppToken, &val);

		paBuffer = new char[val];
		memcpy(paBuffer, *ppToken, val);
		currentObjectPtrs.push_back(new RubyFloat(paBuffer, val));

		(*ppToken) += val;
		break;

	case eRubyTokens::TYPE_CLASS: // Struct, Class Declaration
		++(*ppToken);
			
		ProcessFixnum(ppToken, &val);

		paBuffer = new char[val];
		memcpy(paBuffer, *ppToken, val);
		currentObjectPtrs.push_back(new RubyClass(paBuffer, val));
		(*ppToken) += val;

		break;

	case eRubyTokens::TYPE_SYMBOL:
		++(*ppToken);
		ProcessSymbol(ppToken, &paBuffer, &bufferLength);
		currentObjectPtrs.push_back(new RubySymbol(paBuffer, bufferLength));
		break;

	case eRubyTokens::TYPE_STRUCT:
		++(*ppToken);

		assert(**ppToken == ':');
		++(*ppToken);
		ProcessSymbol(ppToken, &paBuffer, &bufferLength);

		ProcessFixnum(ppToken, &val);
		val *= 2;

		paChildObjectPtrs = new std::vector<RubyBase*>();
		paChildObjectPtrs->reserve(val);
		currentObjectPtrs.push_back(new RubyStruct(paBuffer, bufferLength, paChildObjectPtrs, val));

		for (repCount = 0; repCount < val; ++repCount)
		{
			ParseRecursive(ppToken, pEnd, *paChildObjectPtrs);
		}
		break;

	case eRubyTokens::TYPE_OBJECT:
		++(*ppToken);

		assert(**ppToken == ':');
		++(*ppToken);
		ProcessSymbol(ppToken, &paBuffer, &bufferLength);

		currentObjectPtrs.push_back(new RubyObject(paBuffer, bufferLength));

		break;

	default:
		wprintf(L"not registered token: %s\n", RubyTokenToString(static_cast<eRubyTokens>(**ppToken)));
		return false;
	}

	return true;
}

const wchar_t* RubyTokenToString(const eRubyTokens token)
{
	switch (token)
	{
	case eRubyTokens::TYPE_NIL:
		return L"TYPE_NIL";
	case eRubyTokens::TYPE_TRUE:
		return L"TYPE_TRUE";
	case eRubyTokens::TYPE_FALSE: 
		return L"TYPE_FALSE";
	case eRubyTokens::TYPE_FIXNUM:
		return L"TYPE_FIXNUM";
	case eRubyTokens::TYPE_EXTENDED: 
		return L"TYPE_EXTENDED";
	case eRubyTokens::TYPE_UCLASS:
		return L"TYPE_UCLASS";
	case eRubyTokens::TYPE_OBJECT:
		return L"TYPE_OBJECT";
	case eRubyTokens::TYPE_DATA:
		return L"TYPE_DATA";
	case eRubyTokens::TYPE_USERDEF:
		return L"TYPE_USERDEF";
	case eRubyTokens::TYPE_USRMARSHAL:
		return L"TYPE_USRMARSHAL";
	case eRubyTokens::TYPE_FLOAT:
		return L"TYPE_FLOAT";
	case eRubyTokens::TYPE_BIGNUM:
		return L"TYPE_BIGNUM";
	case eRubyTokens::TYPE_STRING:
		return L"TYPE_STRING";
	case eRubyTokens::TYPE_REGEXP:
		return L"TYPE_REGEXP";
	case eRubyTokens::TYPE_ARRAY:
		return L"TYPE_ARRAY";
	case eRubyTokens::TYPE_HASH:
		return L"TYPE_HASH";
	case eRubyTokens::TYPE_HASH_DEF:
		return L"TYPE_HASH_DEF";
	case eRubyTokens::TYPE_STRUCT:
		return L"TYPE_STRUCT";
	case eRubyTokens::TYPE_MODULE_OLD:
		return L"TYPE_MODULE_OLD";
	case eRubyTokens::TYPE_CLASS:
		return L"TYPE_CLASS";
	case eRubyTokens::TYPE_MODULE:
		return L"TYPE_MODULE";
	case eRubyTokens::TYPE_SYMBOL:
		return L"TYPE_SYMBOL";
	case eRubyTokens::TYPE_SYMLINK:
		return L"TYPE_SYMLINK";
	case eRubyTokens::TYPE_IVAR:
		return L"TYPE_IVAR";
	case eRubyTokens::TYPE_LINK:
		return L"TYPE_LINK";
	default:
		return L"UNKNOWN_TOKEN";
	}
}
