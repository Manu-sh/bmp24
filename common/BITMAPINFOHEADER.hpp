#pragma once
#include <cstdint>

extern "C" {
	#include <endian.h>
}

class __attribute__((__packed__)) BITMAPINFOHEADER {

	public:
		inline BITMAPINFOHEADER & setSize(uint32_t biSize);
		inline BITMAPINFOHEADER & setWidth(int32_t biWidth);
		inline BITMAPINFOHEADER & setHeight(int32_t biHeight);
		inline BITMAPINFOHEADER & setPlanes(uint16_t biPlanes);
		inline BITMAPINFOHEADER & setBitCount(uint16_t biBitCount);
		inline BITMAPINFOHEADER & setCompression(uint32_t biCompression);
		inline BITMAPINFOHEADER & setSizeImage(uint32_t biSizeImage);
		inline BITMAPINFOHEADER & setXPelsPerMeter(int32_t biXPelsPerMeter);
		inline BITMAPINFOHEADER & setYPelsPerMeter(int32_t biYPelsPerMeter);
		inline BITMAPINFOHEADER & setClrUsed(uint32_t biClrUsed);
		inline BITMAPINFOHEADER & setClrImportant(uint32_t biClrImportant);

		uint32_t getSize()          const noexcept { return le32toh(biSize);          }
		 int32_t getWidth()         const noexcept { return le32toh(biWidth);         }
		 int32_t getHeight()        const noexcept { return le32toh(biHeight);        }
		uint16_t getPlanes()        const noexcept { return le16toh(biPlanes);        }
		uint16_t getBitCount()      const noexcept { return le16toh(biBitCount);      }
		uint32_t getCompression()   const noexcept { return le32toh(biCompression);   }
		uint32_t getSizeImage()     const noexcept { return le32toh(biSizeImage);     }
		 int32_t getXPelsPerMeter() const noexcept { return le32toh(biXPelsPerMeter); }
		 int32_t getYPelsPerMeter() const noexcept { return le32toh(biYPelsPerMeter); }
		uint32_t getClrUsed()       const noexcept { return le32toh(biClrUsed);       }
		uint32_t getClrImportant()  const noexcept { return le32toh(biClrImportant);  }

	private:
		uint32_t biSize; // specifies the size of the BITMAPINFOHEADER structure, in bytes
		int32_t biWidth;
		int32_t biHeight; // can be negative

		uint16_t biPlanes;
		uint16_t biBitCount; // color depth

		uint32_t biCompression;
		uint32_t biSizeImage; // specifies the size of the image data, in bytes. If there is no compression, it is valid to set this member to zero.
		int32_t biXPelsPerMeter;
		int32_t biYPelsPerMeter;
		uint32_t biClrUsed;
		uint32_t biClrImportant;
};


inline BITMAPINFOHEADER & BITMAPINFOHEADER::setSize(uint32_t biSize) { 
	return this->biSize = htole32(biSize), *this; 
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setWidth(int32_t biWidth) {  
	return this->biWidth = htole32(biWidth), *this; 
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setHeight(int32_t biHeight) { 
	return this->biHeight = htole32(biHeight), *this; 
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setPlanes(uint16_t biPlanes) { 
	return this->biPlanes = htole16(biPlanes), *this;
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setBitCount(uint16_t biBitCount) { 
	return this->biBitCount = htole16(biBitCount), *this; 
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setCompression(uint32_t biCompression) { 
	return this->biCompression = htole32(biCompression), *this;
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setSizeImage(uint32_t biSizeImage) { 
	return this->biSizeImage = htole32(biSizeImage), *this;
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setXPelsPerMeter(int32_t biXPelsPerMeter) { 
	return this->biXPelsPerMeter = htole32(biXPelsPerMeter), *this;
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setYPelsPerMeter(int32_t biYPelsPerMeter) { 
	return this->biYPelsPerMeter = htole32(biYPelsPerMeter), *this; 
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setClrUsed(uint32_t biClrUsed) { 
	return this->biClrUsed = htole32(biClrUsed), *this; 
}

inline BITMAPINFOHEADER & BITMAPINFOHEADER::setClrImportant(uint32_t biClrImportant) { 
	return this->biClrImportant = htole32(biClrImportant), *this; 
}