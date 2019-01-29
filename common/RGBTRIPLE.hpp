#pragma once
#include <cstdint>

// the order is BGR because they are stored in little endian
struct __attribute__((__packed__)) RGBTRIPLE {
	uint8_t rgbtBlue;
	uint8_t rgbtGreen;
	uint8_t rgbtRed;
};