#include "objects/rgb_color.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

#include <fractals/fractal_utils.h>
#include <fractals/julia.h>
#include <fractals/burning_ship.h>
#include <fractals/mandelbrot.h>

#include <BMP/BMP.h>

int main(int argc, char *argv[]) {
  const uint32_t width = 1920;
  const uint32_t height = 1080;
  const uint16_t max_iterations = 256;

  BMP image(width, height, RGBColor(0.0, 0.0, 0));

  image.for_each_pixels([&](uint32_t x, uint32_t y) {
    double u = x / (double)height;
    double v = y / (double)height;

    auto [t, iterations] =
        /* Fractals::Mandelbrot::generate(2.5 * (u - 0.5) - 1.4, 2.5 * (v - 0.5), max_iterations); */
        /* Fractals::Julia::generate(2.5 * (u - 0.5) - 1.4, 2.5 * (v - 0.5), max_iterations); */
        Fractals::BurningShip::generate(2.5 * (u - 0.5) - 1.4, 2.5 * (v - 0.5), max_iterations);

    /* RGBColor c = Fractals::color(std::fmod((2.0 * t + 0.5), 1.0)); */
    /* RGBColor c = Fractals::logarithmicColoring(iterations, max_iterations);
     */
    /* RGBColor c = Fractals::sinusoidalColoring(iterations, max_iterations); */
    /* RGBColor c = Fractals::randomColoring(iterations); */
    RGBColor c =
        Fractals::gradient_palette(iterations, RGBColor::blue_green_palette());

    image.set_pixel(x, y, c);
  });

  image.write("../out/burning_ship.bmp");

  return 0;
}
