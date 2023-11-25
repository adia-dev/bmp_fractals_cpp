#include "fractals/fractal_utils.h"
#include "objects/rgb_color.h"
#include <cmath>
#include <cstdio>
#include <fractals/mandelbrot.h>
#include <iostream>
#include <string>

#include <BMP/BMP.h>

int main(int argc, char *argv[]) {
  const uint32_t width = 1920;
  const uint32_t height = 1080;

  BMP image(width, height, RGBColor(0.0, 0.0, 0));

  image.for_each_pixels([&](uint32_t x, uint32_t y) {
    double u = x / (double)height;
    double v = y / (double)height;

    double t =
        Fractals::Mandelbrot::generate(2.5 * (u - 0.5) - 1.4, 2.5 * (v - 0.5));

    RGBColor c = Fractals::color(std::fmod((2.0 * t + 0.5), 1.0));

    image.set_pixel(x, y, c);
  });

  image.write("../out/mandelbrot.bmp");

  return 0;
}
