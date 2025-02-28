#pragma once
#include <cstdint>

// the order is BGR because they are stored in little endian

/* following comments it's just for me:
	the order of members of a struct is guaranteed to be as declared, 
	only bitfields of type > 8 byte suffer from compiler reordering issues 
	due to endianess es. bitfields of unsigned integer see /usr/include/netinet/ip.h 
*/
struct __attribute__((__packed__)) RGBTRIPLE {
	uint8_t rgbtBlue;
	uint8_t rgbtGreen;
	uint8_t rgbtRed;
};


static_assert(sizeof(RGBTRIPLE) == 3);
