#pragma once

#include "../common/RGBTRIPLE.hpp"
#include "../common/BITMAPFILEHEADER.hpp"
#include "../common/BITMAPINFOHEADER.hpp"
#include "Matrix.hpp"

class WinBitmap24 {

	WinBitmap24(const WinBitmap24 &o) = delete;
	WinBitmap24 & operator=(const WinBitmap24 &o) = delete;

	public:
		explicit WinBitmap24(const char *filename);
		explicit WinBitmap24(int32_t width, int32_t height);

		uint32_t width()  const noexcept { return m_width;  }
		uint32_t height() const noexcept { return m_height; }
		uint32_t size()   const noexcept { return m_size;   }

		// first arg is height (row), second width (column)
		WinBitmap24 & setPixel(uint32_t r, uint32_t c, RGBTRIPLE bgr);
		RGBTRIPLE & operator()(uint32_t r, uint32_t c);

		void saveBitmap(const char *filename) const;

	private:
		BITMAPFILEHEADER m_bmfh;
		BITMAPINFOHEADER m_bmih;

		Matrix<RGBTRIPLE> m_mtx;
		uint32_t m_width, m_height, m_padding, m_size;
};