#include <cstdio>
#include <cassert>
#include <clocale>
#include <strsafe.h>
#include <vector>
#include <Windows.h>

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
#include "RubyUserDefined.h"
#include "RubyTable.h"
#include "RubyColor.h"
#include "RubyTone.h"

bool ReadBytes(const wchar_t* const pWcsfileName, uint8_t** ppOutData, uint32_t* pDataSize);
int64_t StartParse(uint8_t** ppToken, const uint8_t* const pEnd, std::vector<RubyBase*>& currentObjectPtrs);
bool ParseRecursive(uint8_t** ppToken, const uint8_t* const pEnd, std::vector<RubyBase*>& currentObjectPtrs);
bool ProcessFixnum(uint8_t** ppToken, int32_t* pOutVal);
RubyString* ProcessStringUTF8(uint8_t** ppToken);
RubySymbol* ProcessSymbol(uint8_t** ppToken);
const wchar_t* RubyTokenToString(const eRubyTokens token);
void PrintRxdataRecursive(const RubyBase* const pRubyBase, const int32_t indent);

int32_t wmain(const int32_t argc, const wchar_t* argv[])
{
	uint8_t* paBuf;
	uint8_t* pToken;
	uint32_t bufSize;
	std::vector<RubyBase*> rootObjectPtrs;
	const wchar_t* ppFileNames[] = {
		//L"marshals/marshal/nil.rxdata",
		//L"marshals/marshal/true.rxdata",
		//L"marshals/marshal/false.rxdata",
		//L"marshals/marshal/0x12345678.rxdata",
		//L"marshals/marshal/String_abcd.rxdata",
		//L"marshals/marshal/String_0123가나다라ABCD.rxdata",
		//L"marshals/marshal/String_empty.rxdata",
		//L"marshals/marshal/String_long063.rxdata",
		//L"marshals/marshal/array_empty.rxdata",
		//L"marshals/marshal/array_2d.rxdata",
		//L"marshals/marshal/hash_new.rxdata",
		//L"marshals/marshal/hash_simple.rxdata",
		//L"marshals/marshal/hash_simple2.rxdata",
		//L"marshals/marshal/hash_simple3.rxdata",
		//L"marshals/marshal/hash_new_0.rxdata",
		//L"marshals/marshal/hash_new_32.rxdata",
		//L"marshals/marshal/hash_new_default_key_val.rxdata",
		//L"marshals/marshal/bignum_2_exp_30.rxdata",
		//L"marshals/marshal/bignum_2_exp_31.rxdata",
		//L"marshals/marshal/bignum_2_exp_32.rxdata",
		//L"marshals/marshal/bignum_2_exp_33.rxdata",
		//L"marshals/marshal/bignum_2_exp_34.rxdata",
		//L"marshals/marshal/bignum_2_exp_99.rxdata",
		//L"marshals/marshal/bignum_2_exp_100.rxdata",
		//L"marshals/marshal/bignum_2_exp_200.rxdata",
		//L"marshals/marshal/float_0.999999999999.rxdata",
		//L"marshals/marshal/float_1.0.rxdata",
		//L"marshals/marshal/float_3.141592.rxdata",
		//L"marshals/marshal/float_inf.rxdata",
		//L"marshals/marshal/float_-inf.rxdata",
		//L"marshals/marshal/float_nan.rxdata",
		//L"marshals/marshal/struct_customer.rxdata",
		//L"marshals/marshal/struct_abc_chocolate.rxdata",
		//L"marshals/marshal/struct_customer_instance_dave.rxdata",
		//L"marshals/marshal/class_abc_chocolate_instance.rxdata",
		//L"marshals/marshal/array_nested1.rxdata",
		//L"marshals/marshal/array_nested2.rxdata",
		//L"marshals/marshal/array_two_same_symbols.rxdata",
		//L"marshals/marshal/array_two_same_strings.rxdata",
		//L"marshals/marshal/testset_instance.rxdata",
		//L"marshals/marshal/game_system_instance.rxdata",
		//L"marshals/Data/Actors.rxdata", // ok
		//L"marshals/Data/Animations.rxdata", // ok
		//L"marshals/Data/Armors.rxdata", // ok
		//L"marshals/Data/Classes.rxdata", // ok
		//L"marshals/Data/CommonEvents.rxdata", // ok
		//L"marshals/Data/Enemies.rxdata", // ok
		//L"marshals/Data/Items.rxdata", // ok
		//L"marshals/Data/Map001.rxdata", // ok
		//L"marshals/Data/MapInfos.rxdata", // ok
		//L"marshals/Data/Scripts.rxdata",
		//L"marshals/Data/Skills.rxdata", // ok
		//L"marshals/Data/States.rxdata", // ok
		//L"marshals/Data/System.rxdata", // ok
		//L"marshals/Data/Tilesets.rxdata", // ok
		//L"marshals/Data/Troops.rxdata", // ok
		//L"marshals/Data/Weapons.rxdata", // ok
		L"marshals/Save1.rxdata", // ok
	};

	rootObjectPtrs.reserve(10000);
	_wsetlocale(LC_ALL, L"");

	for (const wchar_t* pFileName : ppFileNames)
	{
		wprintf(L"Start reading \"%s\"=============================\n", pFileName);
		if (ReadBytes(pFileName, &paBuf, &bufSize))
		{
			pToken = paBuf;
			while (true)
			{
				rootObjectPtrs.clear();
				RubyObject::sObjectReferences.clear();
				RubyObject::sObjectReferences.push_back(nullptr);
				RubySymbol::sSymbolLinks.clear();
				int64_t ret = StartParse(&pToken, paBuf + bufSize, rootObjectPtrs);

				for (const RubyBase* pRubyBase : rootObjectPtrs)
				{
					PrintRxdataRecursive(pRubyBase, 0);
				}
				wprintf(L"-----------------------------------------------------------------------\n");

				if (ret < 0)
				{
					assert(0);
					delete[] paBuf;
					paBuf = nullptr;
					break;
				}
				else if (ret == 0)
				{
					delete[] paBuf;
					paBuf = nullptr;
					break;
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			assert(0);
		}
		wprintf(L"=====================================================\n\n");
	}

	return 0;
}

bool ReadBytes(const wchar_t* const pWcsfileName, uint8_t** ppOutData, uint32_t* pDataSize)
{
	FILE* pFile = nullptr;
	errno_t err;
	uint32_t bufSize;
	uint32_t readByte;
	uint8_t* paBuf = nullptr;
	bool bSuccess = false;

	do
	{
		err = _wfopen_s(&pFile, pWcsfileName, L"rb");
		if (err != 0 || pFile == nullptr)
		{
			break;
		}

		fseek(pFile, 0, SEEK_END);
		bufSize = static_cast<uint32_t>(ftell(pFile));
		fseek(pFile, 0, SEEK_SET);

		if (bufSize < 2)
		{
			break;
		}

		paBuf = new uint8_t[bufSize];
		readByte = static_cast<uint32_t>(fread_s(paBuf, bufSize, sizeof(uint8_t), bufSize, pFile));

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

int64_t StartParse(uint8_t** ppToken, const uint8_t* const pEnd, std::vector<RubyBase*>& currentObjectPtrs)
{
	assert(ppToken != nullptr);
	assert(pEnd != nullptr);

	if (**ppToken != MARSHAL_MAJOR)
	{
		return -1;
	}
	++(*ppToken);

	if (**ppToken != MARSHAL_MINOR)
	{
		return -2;
	}
	++(*ppToken);

	ParseRecursive(ppToken, pEnd, currentObjectPtrs);

	return pEnd - *ppToken;
}

bool ProcessFixnum(uint8_t** ppToken, int32_t* pOutVal)
{
	const int32_t fixnumHeader = (*ppToken)[0];
	int32_t retFixnum = -1;

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

	*pOutVal = retFixnum;

	return true;
}

RubyString* ProcessStringUTF8(uint8_t** ppToken)
{
	assert(ppToken != nullptr);

	const int32_t stringLengthHeader = (*ppToken)[0];
	size_t utf8ByteLength = 0;
	RubyString* paRubyString;

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
			return nullptr;
		}
	}

	paRubyString = new RubyString(reinterpret_cast<char*>(*ppToken), utf8ByteLength);
	(*ppToken) += utf8ByteLength;

	return paRubyString;
}

RubySymbol* ProcessSymbol(uint8_t** ppToken)
{
	assert(ppToken != nullptr);

	const int32_t symbolLengthHeader = (*ppToken)[0];
	size_t symbolLength = 0;
	RubySymbol* paRubySymbol;

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
			return nullptr;
		}
	}

	paRubySymbol = new RubySymbol(reinterpret_cast<const char*>(*ppToken), symbolLength);
	(*ppToken) += symbolLength;

	return paRubySymbol;
}

bool ParseRecursive(uint8_t** ppToken, const uint8_t* const pEnd, std::vector<RubyBase*>& currentObjectPtrs)
{
	int32_t val;
	int32_t repCount;
	bool bSignBignum;
	int32_t hashDefault = 0;
	RubySymbol* paRubySymbol;
	RubyBase* pRubyBase;

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
		pRubyBase = ProcessStringUTF8(ppToken);
		assert(pRubyBase != nullptr);
		currentObjectPtrs.push_back(pRubyBase);
		break;

	case eRubyTokens::TYPE_ARRAY:
		++(*ppToken);
		ProcessFixnum(ppToken, &val);
		pRubyBase = new RubyArray(val);
		currentObjectPtrs.push_back(pRubyBase);
		for (repCount = 0; repCount < val; ++repCount)
		{
			ParseRecursive(ppToken, pEnd, static_cast<RubyArray*>(pRubyBase)->ArrayElementPtrs);
		}
		break;

	case eRubyTokens::TYPE_HASH_DEF:
		hashDefault = 1;
		__fallthrough;
	case eRubyTokens::TYPE_HASH:
		++(*ppToken);
		ProcessFixnum(ppToken, &val);
		val = val * 2 + hashDefault; // <key, value> + default value
		pRubyBase = new RubyHash(val);
		currentObjectPtrs.push_back(pRubyBase);
		for (repCount = 0; repCount < val; ++repCount)
		{
			ParseRecursive(ppToken, pEnd, static_cast<RubyHash*>(pRubyBase)->HashElementPtrs);
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

		currentObjectPtrs.push_back(new RubyBignum(bSignBignum, reinterpret_cast<char*>(*ppToken), val));
		(*ppToken) += val;
		break;

	case eRubyTokens::TYPE_FLOAT:
		++(*ppToken);
		ProcessFixnum(ppToken, &val);
		currentObjectPtrs.push_back(new RubyFloat(reinterpret_cast<char*>(*ppToken), val));
		(*ppToken) += val;
		break;

	case eRubyTokens::TYPE_CLASS: // Struct, Class Declaration
		++(*ppToken);
		ProcessFixnum(ppToken, &val);
		currentObjectPtrs.push_back(new RubyClass(reinterpret_cast<char*>(*ppToken), val));
		(*ppToken) += val;
		break;

	case eRubyTokens::TYPE_SYMBOL:
		++(*ppToken);
		paRubySymbol = ProcessSymbol(ppToken);
		assert(paRubySymbol != nullptr);
		currentObjectPtrs.push_back(paRubySymbol);
		RubySymbol::sSymbolLinks.push_back(paRubySymbol);
		break;

	case eRubyTokens::TYPE_SYMLINK:
		++(*ppToken);
		ProcessFixnum(ppToken, &val);
		currentObjectPtrs.push_back(RubySymbol::sSymbolLinks[val]);
		break;

	case eRubyTokens::TYPE_STRUCT:
		++(*ppToken);

		assert(**ppToken == ':');
		++(*ppToken);

		paRubySymbol = ProcessSymbol(ppToken);
		assert(paRubySymbol != nullptr);

		ProcessFixnum(ppToken, &val);
		val *= 2;

		pRubyBase = new RubyStruct(paRubySymbol->Name.c_str(), paRubySymbol->Name.size(), val);
		currentObjectPtrs.push_back(pRubyBase);

		for (repCount = 0; repCount < val; ++repCount)
		{
			ParseRecursive(ppToken, pEnd, static_cast<RubyStruct*>(pRubyBase)->StructMemberPtrs);
		}
		break;

	case eRubyTokens::TYPE_OBJECT:
		++(*ppToken);

		if (**ppToken == ':')
		{
			++(*ppToken);
			paRubySymbol = ProcessSymbol(ppToken);
			assert(paRubySymbol != nullptr);

			ProcessFixnum(ppToken, &val);
			val *= 2;

			pRubyBase = new RubyObject(paRubySymbol->Name.c_str(), paRubySymbol->Name.size(), val);
			currentObjectPtrs.push_back(pRubyBase);
			RubySymbol::sSymbolLinks.push_back(paRubySymbol);

			for (repCount = 0; repCount < val; ++repCount)
			{
				ParseRecursive(ppToken, pEnd, static_cast<RubyObject*>(pRubyBase)->ObjectElementPtrs);
			}
		}
		else if (**ppToken == ';')
		{
			++(*ppToken);
			ProcessFixnum(ppToken, &val);

			RubySymbol* pLinkedSymbol = RubySymbol::sSymbolLinks[val];

			ProcessFixnum(ppToken, &val); // member count
			val *= 2;

			pRubyBase = new RubyObject(pLinkedSymbol->Name.c_str(), pLinkedSymbol->Name.size(), val);
			currentObjectPtrs.push_back(pRubyBase);

			for (repCount = 0; repCount < val; ++repCount)
			{
				ParseRecursive(ppToken, pEnd, static_cast<RubyObject*>(pRubyBase)->ObjectElementPtrs);
			}
		}
		else
		{
			assert(false);
		}

		break;

	case eRubyTokens::TYPE_LINK:
		++(*ppToken);
		ProcessFixnum(ppToken, &val);
		val += 1;
		currentObjectPtrs.push_back(RubyBase::sObjectReferences[val]);
		break;

	case eRubyTokens::TYPE_USERDEF:
		++(*ppToken);
		
		if (**ppToken == ';')
		{
			++(*ppToken);
			ProcessFixnum(ppToken, &val);

			RubySymbol* pRubyUserDefinedSymbol = RubySymbol::sSymbolLinks[val];
			if (pRubyUserDefinedSymbol->Name == "Table" || pRubyUserDefinedSymbol->Name == "Color" || pRubyUserDefinedSymbol->Name == "Tone")
			{
				ProcessFixnum(ppToken, &val);
				currentObjectPtrs.push_back(new RubyUserDefined(pRubyUserDefinedSymbol->Name.c_str(), pRubyUserDefinedSymbol->Name.size(), reinterpret_cast<char*>(*ppToken), val));
				*ppToken += val;
			}
		}
		else
		{
			++(*ppToken);
			
			paRubySymbol = ProcessSymbol(ppToken);
			assert(paRubySymbol != nullptr);

			RubySymbol::sSymbolLinks.push_back(paRubySymbol);

			if (paRubySymbol->Name == "Table" || paRubySymbol->Name == "Color" || paRubySymbol->Name == "Tone")
			{
				ProcessFixnum(ppToken, &val);

				pRubyBase = new RubyUserDefined(paRubySymbol->Name.c_str(), paRubySymbol->Name.size(), reinterpret_cast<char*>(*ppToken), val);
				*ppToken += val;

				currentObjectPtrs.push_back(pRubyBase);
				RubyObject::sObjectReferences.push_back(pRubyBase);
			}
		}

		break;

	default:
		wprintf(L"not registered token: %s\n", RubyTokenToString(static_cast<eRubyTokens>(**ppToken)));
		assert(0);
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

void PrintRxdataRecursive(const RubyBase* const pRubyBase, const int32_t indent)
{
	for (int32_t i = 0; i < indent; ++i)
	{
		wprintf(L"  ");
	}
	switch (pRubyBase->Type)
	{
	case eRubyTokens::TYPE_NIL:
		wprintf(L"nil\n");
		break;
	case eRubyTokens::TYPE_TRUE:
		wprintf(L"true\n");
		break;
	case eRubyTokens::TYPE_FALSE:
		wprintf(L"false\n");
		break;
	case eRubyTokens::TYPE_FIXNUM:
		wprintf(L"%d\n", static_cast<const RubyFixnum*>(pRubyBase)->Value);
		break;
	case eRubyTokens::TYPE_EXTENDED:
		assert(0);
		break;
	case eRubyTokens::TYPE_UCLASS:
		assert(0);
		break;
	case eRubyTokens::TYPE_OBJECT:
		printf("object of class %s\n", static_cast<const RubyObject*>(pRubyBase)->ClassName.c_str());
		for (RubyBase* pChild : static_cast<const RubyObject*>(pRubyBase)->ObjectElementPtrs)
		{
			PrintRxdataRecursive(pChild, indent + 1);
		}
		break;
	case eRubyTokens::TYPE_DATA:
		assert(0);
		break;
	case eRubyTokens::TYPE_USERDEF:
		printf("User-defined class %s\n", static_cast<const RubyUserDefined*>(pRubyBase)->ClassName.c_str());
		if (static_cast<const RubyUserDefined*>(pRubyBase)->ClassName == "Table")
		{
			RubyTable* pRubyTable;

			pRubyTable = reinterpret_cast<RubyTable*>((static_cast<const RubyUserDefined*>(pRubyBase)->PABuffer));
			for (int32_t i = 0; i < indent; ++i)
			{
				wprintf(L"  ");
			}
			wprintf(L"- Dimension = %u\n", pRubyTable->Dimension);

			for (int32_t i = 0; i < indent; ++i)
			{
				wprintf(L"  ");
			}
			wprintf(L"- SizeX = %u\n", pRubyTable->SizeX);

			for (int32_t i = 0; i < indent; ++i)
			{
				wprintf(L"  ");
			}
			wprintf(L"- SizeY = %u\n", pRubyTable->SizeY);

			for (int32_t i = 0; i < indent; ++i)
			{
				wprintf(L"  ");
			}
			wprintf(L"- SizeZ = %u\n", pRubyTable->SizeZ);

			for (int32_t i = 0; i < indent; ++i)
			{
				wprintf(L"  ");
			}
			wprintf(L"- ElementCount = %u\n", pRubyTable->ElementCount);

			for (int32_t i = 0; i < indent; ++i)
			{
				wprintf(L"  ");
			}
			wprintf(L"- Elements =\n");
			for (uint32_t z = 0; z < pRubyTable->SizeZ; ++z)
			{
				for (uint32_t y = 0; y < pRubyTable->SizeY; ++y)
				{
					for (uint32_t x = 0; x < pRubyTable->SizeX; ++x)
					{
						int16_t element = pRubyTable->Elements[x + y * pRubyTable->SizeX + z * pRubyTable->SizeX * pRubyTable->SizeY];
						wprintf(L"%6hd ", element);
					}
					wprintf(L"\n");
				}
			}
		}
		else if (static_cast<const RubyUserDefined*>(pRubyBase)->ClassName == "Color")
		{
			RubyColor* pRubyColor;
			pRubyColor = reinterpret_cast<RubyColor*>((static_cast<const RubyUserDefined*>(pRubyBase)->PABuffer));

			for (int32_t i = 0; i < indent; ++i)
			{
				wprintf(L"  ");
			}
			wprintf(L"(%hhu, %hhu, %hhu, %hhu)\n",
				static_cast<uint8_t>(pRubyColor->Red),
				static_cast<uint8_t>(pRubyColor->Green),
				static_cast<uint8_t>(pRubyColor->Blue),
				static_cast<uint8_t>(pRubyColor->Alpha)
			);
		}
		else if (static_cast<const RubyUserDefined*>(pRubyBase)->ClassName == "Tone")
		{
			RubyTone* pRubyTone;
			pRubyTone = reinterpret_cast<RubyTone*>((static_cast<const RubyUserDefined*>(pRubyBase)->PABuffer));

			for (int32_t i = 0; i < indent; ++i)
			{
				wprintf(L"  ");
			}
			wprintf(L"(%hhu, %hhu, %hhu, %hhu)\n",
				static_cast<uint8_t>(pRubyTone->Red),
				static_cast<uint8_t>(pRubyTone->Green),
				static_cast<uint8_t>(pRubyTone->Blue),
				static_cast<uint8_t>(pRubyTone->Gray)
			);
		}
		
		break;
	case eRubyTokens::TYPE_USRMARSHAL:
		assert(0);
		break;
	case eRubyTokens::TYPE_FLOAT:
		wprintf(L"%.1lf\n", static_cast<const RubyFloat*>(pRubyBase)->Value);
		break;
	case eRubyTokens::TYPE_BIGNUM:
		break;
	case eRubyTokens::TYPE_STRING:
		printf("\"%s\"\n", static_cast<const RubyString*>(pRubyBase)->Value.c_str());
		break;
	case eRubyTokens::TYPE_REGEXP:
		assert(0);
		break;
	case eRubyTokens::TYPE_ARRAY:
		wprintf(L"[\n");
		for (RubyBase* pChild : static_cast<const RubyArray*>(pRubyBase)->ArrayElementPtrs)
		{
			PrintRxdataRecursive(pChild, indent + 1);
		}
		for (int32_t i = 0; i < indent; ++i)
		{
			wprintf(L"  ");
		}
		wprintf(L"]\n");
		break;
	case eRubyTokens::TYPE_HASH:
		wprintf(L"{\n");
		for (RubyBase* pChild : static_cast<const RubyHash*>(pRubyBase)->HashElementPtrs)
		{
			PrintRxdataRecursive(pChild, indent + 1);
		}
		for (int32_t i = 0; i < indent; ++i)
		{
			wprintf(L"  ");
		}
		wprintf(L"}\n");
		break;
	case eRubyTokens::TYPE_HASH_DEF:
		assert(0);
		break;
	case eRubyTokens::TYPE_STRUCT:
		printf("%s = Struct.new\n{\n", static_cast<const RubyStruct*>(pRubyBase)->Name.c_str());
		for (RubyBase* pChild : static_cast<const RubyStruct*>(pRubyBase)->StructMemberPtrs)
		{
			PrintRxdataRecursive(pChild, indent + 1);
		}
		wprintf(L"}\n");
		break;
	case eRubyTokens::TYPE_MODULE_OLD:
		assert(0);
		break;
	case eRubyTokens::TYPE_CLASS:
		printf("class %s\n", static_cast<const RubyClass*>(pRubyBase)->Name.c_str());
		break;
	case eRubyTokens::TYPE_MODULE:
		assert(0);
		break;
	case eRubyTokens::TYPE_SYMBOL:
		printf(":%s\n", static_cast<const RubySymbol*>(pRubyBase)->Name.c_str());
		break;
	case eRubyTokens::TYPE_SYMLINK:
		assert(0);
		break;
	case eRubyTokens::TYPE_IVAR:
		assert(0);
		break;
	case eRubyTokens::TYPE_LINK:
		assert(0);
		break;
	default:
		assert(0);
		break;
	}
}
