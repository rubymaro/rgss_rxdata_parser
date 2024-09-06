#include <cstdio>

enum
{
	RUBY_MARSHAL_MAJOR = 4,
	RUBY_MARSHAL_MINOR = 8,
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
		err = _wfopen_s(&pFile, L"Actors.rxdata", L"rb");
		if (err != 0 || pFile == nullptr)
		{
			break;
		}

		fseek(pFile, 0, SEEK_END);
		size = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		paBuf = new char[size];

		readByte = fread_s(paBuf, size, sizeof(char), size, pFile);
		fclose(pFile);

		pCur = paBuf;
		if (*pCur != RUBY_MARSHAL_MAJOR)
		{
			break;
		}
		++pCur;

		if (*pCur != RUBY_MARSHAL_MINOR)
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