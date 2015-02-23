#include <complex>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include <gmpxx.h>
#include <png++/png.hpp>

#define ESCAPE 4
#define MAX_ITERATIONS 255

mpf_class xmin;
mpf_class xmax;
mpf_class ymin;
mpf_class ymax;
mpf_class xinc;
mpf_class yinc;

png::image<png::index_pixel> image;

void render_pixel(size_t y, size_t x) {
	mpf_class posx = xmin + x * xinc;
	mpf_class posy = ymax - y * yinc;
	std::complex<mpf_class> v0(posx, posy);
	std::complex<mpf_class> v(0, 0);

	int iter = 0;

	while (std::norm(v) < ESCAPE && iter < MAX_ITERATIONS) {
		v = std::pow(v, 2) + v0;
		iter++;
	}

	image[y][x] = iter;
}

int main(int argc, char *argv[]) {
	// check arguments
	if (argc < 8) {
		std::cout << "Usage: " << argv[0] << " xmin xmax ymin ymax width height"
				<< " outfile" << std::endl;
		return 1;
	}

	// parse arguments
	std::string arg_xmin(argv[1]);
	std::string arg_xmax(argv[2]);
	std::string arg_ymin(argv[3]);
	std::string arg_ymax(argv[4]);
	std::string arg_width(argv[5]);
	std::string arg_height(argv[6]);
	std::string arg_output(argv[7]);

	xmin = mpf_class(arg_xmin);
	xmax = mpf_class(arg_xmax);
	ymin = mpf_class(arg_ymin);
	ymax = mpf_class(arg_ymax);

	size_t dim[2];
	dim[0] = atoi(arg_width.c_str());
	dim[1] = atoi(arg_height.c_str());

	// set up image
	png::palette pal(256);
	for (size_t i = 0; i < pal.size(); ++i) {
		pal[i] = png::color(i, i, i);
	}

	image = png::image<png::index_pixel>(dim[0], dim[1]);
	image.set_palette(pal);

	// render image
	xinc = (xmax - xmin) / dim[0];
	yinc = (ymax - ymin) / dim[1];

	for (size_t y = 0; y < image.get_height(); ++y) {
		for (size_t x = 0; x < image.get_width(); ++x) {
			render_pixel(y, x);
		}
	}

	// write out image
	image.write(arg_output);
	return 0;
}
