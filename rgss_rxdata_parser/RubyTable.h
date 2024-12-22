#pragma once

#include <cstdint>

struct RubyTable final
{
	uint32_t Dimension;
	uint32_t SizeX;
	uint32_t SizeY;
	uint32_t SizeZ;
	uint32_t ElementCount;
	int16_t PElement[0];
};