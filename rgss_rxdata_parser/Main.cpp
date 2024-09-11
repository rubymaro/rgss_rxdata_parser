#include <cstdio>
#include <cassert>

#include "eRubyTokens.h"

void OpenFile(const wchar_t* const pWcsfileName);
bool Parse(const unsigned char* const paBuf, const unsigned int bufSize);

void OpenFile(const wchar_t* const pWcsfileName)
{
	FILE* pFile = nullptr;
	errno_t err;
	unsigned int bufSize;
	unsigned int  readByte;
	unsigned char* paBuf = nullptr;

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
		fclose(pFile);

		assert(readByte > 0);
		assert(readByte == bufSize);

		Parse(paBuf, bufSize);

		delete[] paBuf;

	} while (0);
}

bool ProcessFixnum(const unsigned char** ppToken, int* outVal)
{
	++(*ppToken);

	int followingByte = **ppToken;

	switch (followingByte)
	{
	case 0x00: // 0
		*outVal = 0;
		(*ppToken) += 1;
		return true;
	case 0x01: // unsigned [0x7B, 0xFF]
		*outVal = (*ppToken)[1];
		(*ppToken) += 2;
		return true;
	case 0x02: // unsigned [0x0100, 0xFFFF]
		*outVal = (*ppToken)[1] | (*ppToken)[2] << 8;
		(*ppToken) += 3;
		break;
	case 0x03: // unsigned [0x010000, 0xFFFFFF]
		*outVal = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16;
		(*ppToken) += 4;
		break;
	case 0x04: // unsigned [0x01000000, 0x3FFFFFFF]
		*outVal = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16 | (*ppToken)[4] << 24;
		(*ppToken) += 5;
		break;
	case 0xFF: // signed [0x00, 0x84] => [-256, -124]
		*outVal = -(((~((*ppToken)[1])) & 0x000000ff) + 1);
		(*ppToken) += 2;
		break;
	case 0xFE:
		*outVal = -(((~((*ppToken)[1] | (*ppToken)[2] << 8)) & 0x0000ffff) + 1);
		(*ppToken) += 3;
		break;
	case 0xFD:
		break;
	case 0xFC:
		break;
	default:
	{
		if (followingByte >= 0x06 && followingByte <= 0x7F)
		{
			*outVal = (char)(followingByte - 0x05); // unsigned [0x01, 0x7A]
			(*ppToken) += 1;
			return true;
		}
		else if (followingByte >= 0x80 && followingByte <= 0xFA) 
		{
			*outVal = (char)(followingByte + 0x05); // signed [0x85, 0xFF] = [-123, -1]
			(*ppToken) += 1;
			return true;
		}
		break;
	}
	}

	return false;
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

	while (pToken < pEnd)
	{
		switch (*pToken)
		{
		case TYPE_NIL:
			++pToken;
			break;
		case TYPE_TRUE:
			++pToken;
			break;
		case TYPE_FALSE:
			++pToken;
			break;
		case TYPE_FIXNUM:
			ProcessFixnum(&pToken, &val);
			break;
		default:
			break;
		}
	}

	return true;
}

int wmain(const int argc, const wchar_t* argv[])
{
	//OpenFile(L"06_Fixnum_16777216.rxdata");
	//OpenFile(L"06_Fixnum_16777217.rxdata");
	//OpenFile(L"07_Fixnum_-1.rxdata");
	//OpenFile(L"07_Fixnum_-123.rxdata");
	//OpenFile(L"07_Fixnum_-124.rxdata");
	//OpenFile(L"07_Fixnum_-256.rxdata");
	OpenFile(L"07_Fixnum_-257.rxdata");
	OpenFile(L"08_Fixnum_-65534.rxdata");
	OpenFile(L"08_Fixnum_-65535.rxdata");
	OpenFile(L"08_Fixnum_-65536.rxdata");
	OpenFile(L"08_Fixnum_-65537.rxdata");

	return 0;
}