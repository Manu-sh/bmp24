#pragma once
#include <cstdint>

// TODO bug?
/* expressed in little endian */
enum BitmapType: uint16_t {
	BM = 0x4d42,
	BA = 0x414d,
	CI = 0x4943,
	CP = 0x5043,
	IC = 0x4349,
	PT = 0x5450
};

enum ColorDepth: uint8_t {
	BPP1  = 1,
	BPP2  = 2,
	BPP4  = 4,
	BPP8  = 8,
	BPP16 = 16,
	BPP24 = 24,
	BPP32 = 32
};

/* BI_RGB: no compression */
enum Compression: uint8_t { 
	BI_RGB, 
	BI_RLE8, 
	BI_RLE4, 
	BI_BITFIELDS, 
	BI_JPEG, 
	BI_PNG, 
	BI_ALPHABITFIELDS, 
	BI_CMYK, 
	BI_CMYKRLE8, 
	BI_CMYKRLE4 
};