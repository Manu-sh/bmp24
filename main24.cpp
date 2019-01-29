#include "Bitmap24/WinBitmap24.hpp"

#include <iostream>
#include <cstdint>
#include <cassert>
#include <complex>

extern "C" {
	#include <omp.h>
}

using namespace std;

int main() try {

	WinBitmap24 bmp(1920,1080);

	size_t const ixsize = bmp.height();
	size_t const iysize = bmp.width();

	// slightly modified version of the algorithm present on rosette code: http://rosettacode.org/wiki/Mandelbrot_set#C.2B.2B
	double cxmin = -2.5, cxmax = 2.5, cymin = -2.5, cymax = 2.5;
	unsigned max_i = 1000, i;

	#pragma omp parallel for
	for (size_t ix = 0; ix < ixsize; ++ix) {
		for (size_t iy = 0; iy < iysize; ++iy) {

			std::complex<double> c{
				cxmin + ix / (ixsize-1.0) * (cxmax - cxmin), 
				cymin + iy / (iysize-1.0) * (cymax - cymin)
			}, z = 0;

			for (i = 0; i < max_i && std::abs(z) < 4.0; ++i)
				z = cos(z * pow(c, 3));

			const uint8_t col = (uint8_t)(z.real() * 1);
			bmp.setPixel(ix, iy, (i == max_i) ? RGBTRIPLE{0,0,0} : RGBTRIPLE{col,col,col});
		}
	}

	bmp.saveBitmap("mandelbrot.bmp");

} catch (exception &e) {
	cerr << "=> " << e.what() << endl;
}