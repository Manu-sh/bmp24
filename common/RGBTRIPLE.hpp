#pragma once
#include <cstdint>

// the order is BGR because they are stored in little endian
// the order of members of a struct is guaranteed to be as declared, only bitfields suffer from compiler reordering problems due to endianess
struct __attribute__((__packed__)) RGBTRIPLE {
	uint8_t rgbtBlue;
	uint8_t rgbtGreen;
	uint8_t rgbtRed;
};


static_assert(sizeof(RGBTRIPLE) == 3);
