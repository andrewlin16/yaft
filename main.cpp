#include <complex>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <thread>

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

int thread_limit;

png::index_pixel render_pixel(const mpf_class &posy, const mpf_class &posx) {
	std::complex<mpf_class> v0(posx, posy);
	std::complex<mpf_class> v(0, 0);

	int iter = 0;

	while (std::norm(v) < ESCAPE && iter < MAX_ITERATIONS) {
		v = std::pow(v, 2) + v0;
		iter++;
	}

	return iter;
}

void render_thread(int id) {
	std::cerr << ("thread " + std::to_string(id) + " go\n");

	size_t height = image.get_height();
	size_t width = image.get_width();

	size_t area = width * height;
	size_t pix = area * id / thread_limit;
	size_t pix_limit = area * (id + 1) / thread_limit;

	size_t y = pix / width;
	size_t x = pix % width;

	mpf_class pos_y = ymin + y * yinc;
	mpf_class pos_x = xmin + x * xinc;

	for (size_t i = pix; i < pix_limit; i++) {
		image[y][x] = render_pixel(pos_y, pos_x);

		x++;
		if (x == width) {
			x = 0;
			y++;

			pos_x = xmin;
			pos_y += yinc;
		} else {
			pos_x += xinc;
		}
	}

	std::cerr << ("thread " + std::to_string(id) + " done\n");
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

	thread_limit = std::thread::hardware_concurrency();
	std::thread *thread_pool = new std::thread[thread_limit];

	for (int i = 0; i < thread_limit; i++) {
		thread_pool[i] = std::thread(render_thread, i);
	}

	for (int i = 0; i < thread_limit; i++) {
		thread_pool[i].join();
	}

	// write out image
	image.write(arg_output);
	return 0;
}
