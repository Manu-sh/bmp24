#include "WinBitmap24.hpp"

#include "../common/utils.hpp"
#include "../common/constants.hpp"

#include <iostream>

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <string>
#include <stdexcept>
#include <filesystem>

WinBitmap24::WinBitmap24(int32_t width, int32_t height) {

	assert(width > 0);
	assert((row_size(width, ColorDepth::BPP24) - (width * sizeof(RGBTRIPLE))) == row_padding(width, ColorDepth::BPP24));

	m_padding = row_padding(width, ColorDepth::BPP24);
	m_size    = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + abs(height * (width * sizeof(RGBTRIPLE) + m_padding));
	m_height  = abs(height);
	m_width   = width;

	m_bmfh.setType(BitmapType::BM);

	/* specifies the size of the file in bytes. (including padding) */
	m_bmfh.setSize(m_size);
	m_bmfh.setOffBits(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
	m_bmfh.setReserved1(0).setReserved2(0);

	m_bmih.setSize(sizeof(BITMAPINFOHEADER));
	m_bmih.setWidth(width);
	m_bmih.setHeight(height);
	m_bmih.setPlanes(1);
	m_bmih.setBitCount(ColorDepth::BPP24);

	m_bmih.setCompression(0).setSizeImage(0).setXPelsPerMeter(0).setYPelsPerMeter(0).setClrUsed(0).setClrImportant(0);

	// without padding
	m_mtx.resize(m_height, m_width);
}

WinBitmap24::WinBitmap24(const char *filename) {

	using std::ios_base;

	const auto bmpFileSize = std::filesystem::file_size(filename);
	std::ifstream fbmp;

	fbmp.exceptions(ios_base::badbit);
	fbmp.open(filename, ios_base::in|ios_base::binary);

	if (!fbmp) throw std::invalid_argument(std::string("Unable to open file: ") + filename);

	if (!fbmp.read((char *)&this->m_bmfh, sizeof(m_bmfh)) || !fbmp.read((char *)&this->m_bmih, sizeof(m_bmih)))
		throw std::invalid_argument("Premature end of file");

	if (m_bmfh.getType() != BitmapType::BM)
		throw std::invalid_argument("Not a windows bitmap");

	if (m_bmih.getBitCount() != ColorDepth::BPP24)
		throw std::invalid_argument("Invalid color depth (truecolor only)");

	if (m_bmih.getCompression() != Compression::BI_RGB)
		throw std::invalid_argument("Compression not unsupported");

	if (m_bmih.getWidth() <= 0 || abs(m_bmih.getHeight()) <= 0) 
		throw std::invalid_argument("Width <= 0");

	if (m_bmih.getPlanes() != 1) 
		throw std::invalid_argument("Planes != 1");

	if (m_bmfh.getOffBits() >= bmpFileSize || m_bmfh.getSize() != bmpFileSize)
		throw std::invalid_argument("Bitmap hdr: invalid size");

	m_width   = m_bmih.getWidth();
	m_height  = abs(m_bmih.getHeight());
	m_padding = row_padding(m_width, ColorDepth::BPP24);

	const auto rowByteSize = m_width * sizeof(RGBTRIPLE);
	const auto bmpFilePixelArray = m_height * (rowByteSize + m_padding);

	// including padding
	m_size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpFilePixelArray;

	if (bmpFileSize - fbmp.tellg() != bmpFilePixelArray)
		throw std::invalid_argument("Bitmap hdr invalid width/height");

	// without padding
	m_mtx.resize(m_height, m_width);

	assert((row_size(m_width, ColorDepth::BPP24) - (m_width * sizeof(RGBTRIPLE))) == row_padding(m_width, ColorDepth::BPP24));

	for (uint32_t i = 0; i < m_mtx.rows(); ++i) {

		if (!m_mtx.row_mem_fill(i, fbmp))
			throw std::invalid_argument("Premature end of file");

		fbmp.seekg(m_padding, ios_base::cur);
	}

}

RGBTRIPLE & WinBitmap24::operator()(uint32_t r, uint32_t c) {
	return m_mtx(r,c);
}

WinBitmap24 & WinBitmap24::setPixel(uint32_t r, uint32_t c, RGBTRIPLE bgr) {
	return this->operator()(r,c) = bgr, *this;
}

void WinBitmap24::saveBitmap(const char *filename) const
{ 
	using std::ios_base;

	std::ofstream fbmp;
	fbmp.exceptions(ios_base::failbit|ios_base::badbit);
	fbmp.open(filename, ios_base::out|ios_base::binary|ios_base::trunc);

	fbmp.write((char *)&m_bmfh, sizeof(m_bmfh));
	fbmp.write((char *)&m_bmih, sizeof(m_bmih));

	for (uint32_t i = 0; i < m_mtx.rows(); ++i) {

		m_mtx.row_mem_write(i, fbmp);

		/* add padding */
		for (uint32_t i = 0; i < m_padding; ++i)
			fbmp.put('\0');
	}

}