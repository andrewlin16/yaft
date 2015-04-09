yaft
====

YAFT (Yet Another Fractal Tool) is a command-line program that renders a portion
of the [Mandelbrot Set](http://en.wikipedia.org/wiki/Mandelbrot_set) to a PNG
file.

Details
-------

YAFT is written in C++ and makes use of C++11 features, mainly its threading
support.

YAFT uses [GMP](https://gmplib.org/) to render the fractal with arbitrary
precision. It specifically uses the C++ class interfaces in GMP.

YAFT uses [png++](http://www.nongnu.org/pngpp/), which is a C++ wrapper for
[libpng](http://www.libpng.org/pub/png/libpng.html), to render the fractal image
output to a PNG file.

YAFT uses an [escape time
algorithm](https://en.wikipedia.org/wiki/Mandelbrot_set#Escape_time_algorithm)
to render the Mandelbrot fractal. Each thread renders chunks/sections of 2048
pixels.

Usage
-----

YAFT takes in rendering parameters through command line arguments. Running YAFT
without any arguments will print out usage instructions:

```
Usage: ./yaft xmin xmax ymin ymax width height outfile
```

* xmin: the left boundary of the render window
* xmax: the right boundary of the render window
* ymin: the bottom boundary of the render window
* ymax: the top boundary of the render window
* width: the width of the rendered image in pixels
* height: the height of the rendered image in pixels
* outfile: the file path/name to save the rendered image to

Examples can be seen in the `test.sh` and `bigtest.sh` files.

Example: `./yaft -1.5 0.5 -1 1 256 256 test.png` will render the fractal in a
window with corners (-1.5, -1) to (0.5, 1) and output it to a 256x256 image
named `test.png`.

On Debian/Ubuntu systems, you will need to install the `libgmp-dev` and the
`libpng++-dev` packages to build this package.

License
-------

yaft is licensed under the MIT license. See LICENSE.txt.
