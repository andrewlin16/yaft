#include <cstdlib>
#include <iostream>
#include <sstream>

#include <png++/png.hpp>

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

	size_t dim[2];
	dim[0] = atoi(arg_width.c_str());
	dim[1] = atoi(arg_height.c_str());

	// set up image
	png::palette pal(256);
	for (size_t i = 0; i < pal.size(); ++i) {
		pal[i] = png::color(i, i, i);
	}

	png::image<png::index_pixel> image(dim[0], dim[1]);
	image.set_palette(pal);

	// render image
	for (size_t y = 0; y < image.get_height(); ++y) {
		for (size_t x = 0; x < image.get_width(); ++x) {
			image[y][x] = (y * x) % 256;
		}
	}

	// write out image
	image.write(arg_output);
	return 0;
}
