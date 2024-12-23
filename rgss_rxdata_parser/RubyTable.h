#pragma once

#include <cstdint>

struct RubyTable final
{
	uint32_t Dimension;
	uint32_t SizeX;
	uint32_t SizeY;
	uint32_t SizeZ;
	uint32_t ElementCount;
#pragma warning(push)
#pragma warning(disable : 4200)
	int16_t PElement[0];
#pragma warning(pop)
};