#include <cstdio>

int wmain(const int argc, const wchar_t* argv[])
{
	FILE* pFile = nullptr;
	errno_t err;
	long size;
	char* paBuf;
	size_t readByte;

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

		delete[] paBuf;

		

		fclose(pFile);

		return 0;


	} while (0);



	return 1;
}