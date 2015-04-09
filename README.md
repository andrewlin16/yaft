yaft
====

YAFT (Yet Another Fractal Tool) is a command-line program that renders a portion
of the [Mandelbrot Set](http://en.wikipedia.org/wiki/Mandelbrot_set) to a PNG
file.

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

YAFT uses [GMP](https://gmplib.org/) and [png++](http://www.nongnu.org/pngpp/).
On Debian/Ubuntu systems, you will need to install the `libgmp-dev` and the
`libpng++-dev` packages to build this package.

License
-------

yaft is licensed under the MIT license. See LICENSE.txt.
