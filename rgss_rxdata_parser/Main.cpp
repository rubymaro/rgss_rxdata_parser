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
	case '\x00': // 0
		*outVal = 0;
		(*ppToken) += 1;
		return true;
	case '\x01': // [0x7B, 0xFF]
		*outVal = (*ppToken)[1];
		(*ppToken) += 2;
		return true;
	case '\x02': // [0x0100, 0xFFFF]
		*outVal = (*ppToken)[1] | (*ppToken)[2] << 8;
		(*ppToken) += 3;
		break;
	case '\x03': // [0x010000, 0xFFFFFF]
		*outVal = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16;
		(*ppToken) += 4;
		break;
	case '\x04': // [0x01000000, 0x3FFFFFFF]
		*outVal = (*ppToken)[1] | (*ppToken)[2] << 8 | (*ppToken)[3] << 16 | (*ppToken)[4] << 24;
		(*ppToken) += 5;
		break;
	case '\xff':
		break;
	case '\xfe':
		break;
	case '\xfd':
		break;
	case '\xfc':
		break;
	default:
	{
		if (followingByte > 0x05 && followingByte <= 0x7F)
		{
			return followingByte - 0x05; // [0x01, 0x7A]
		}
		else
		{

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
	OpenFile(L"06_Fixnum_16777216.rxdata");
	OpenFile(L"06_Fixnum_16777217.rxdata");

	return 0;
}