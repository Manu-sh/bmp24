#pragma once
#include <cstdint>

extern "C" {
	#include <endian.h>
}

/* __attribute__((__packed__)): prevents compiler from doing padding this is required if
because for example BITMAPFILEHEADER must be exactly 14 byte but compiler add padding
ad become 16 byte so the bmp result malformed */ 

/* the order is important */
class __attribute__((__packed__)) BITMAPFILEHEADER {

	public:
		inline BITMAPFILEHEADER & setType(uint16_t bfType);
		inline BITMAPFILEHEADER & setSize(uint32_t bfSize);
		inline BITMAPFILEHEADER & setReserved1(uint16_t bfReserved1);
		inline BITMAPFILEHEADER & setReserved2(uint16_t bfReserved2);
		inline BITMAPFILEHEADER & setOffBits(uint32_t bfOffBits);

		uint16_t getType()      const noexcept { return le16toh(bfType);      }
		uint32_t getSize()      const noexcept { return le32toh(bfSize);      }
		uint16_t getReserved1() const noexcept { return le16toh(bfReserved1); }
		uint16_t getReserved2() const noexcept { return le16toh(bfReserved2); }
		uint32_t getOffBits()   const noexcept { return le32toh(bfOffBits);   }

	private:
		uint16_t bfType;
		uint32_t bfSize; /* specifies the size of the file in bytes. (with padding) */
		uint16_t bfReserved1;
		uint16_t bfReserved2;
		uint32_t bfOffBits; /* specifies the offset from the beginning of the file to the bitmap data. */
};


inline BITMAPFILEHEADER & BITMAPFILEHEADER::setType(uint16_t bfType) {
	return this->bfType = htole16(bfType), *this; 
}

inline BITMAPFILEHEADER & BITMAPFILEHEADER::setSize(uint32_t bfSize) {
	return this->bfSize = htole32(bfSize), *this; 
}

inline BITMAPFILEHEADER & BITMAPFILEHEADER::setReserved1(uint16_t bfReserved1) {
	return this->bfReserved1 = htole16(bfReserved1), *this;
}

inline BITMAPFILEHEADER & BITMAPFILEHEADER::setReserved2(uint16_t bfReserved2) {
	return this->bfReserved2 = htole16(bfReserved2), *this; 
}

inline BITMAPFILEHEADER & BITMAPFILEHEADER::setOffBits(uint32_t bfOffBits) { 
	return this->bfOffBits = htole32(bfOffBits), *this; 
}