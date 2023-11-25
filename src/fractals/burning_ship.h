#pragma once

#include <cmath>
#include <cstdint>
#include <objects/complex.h>
#include <utility>

namespace Fractals {
namespace BurningShip {
static std::pair<double, uint16_t> generate(double x, double y,
                                            uint16_t max_iterations = 256) {
  Complex z;
  Complex c(x, y);

  uint16_t i = 0;
  while (i < max_iterations && z.sq_mag() < 32.0) {
    z = z.abs();
    z = z.mul(z).add(c);
    i++;
  }

  double smooth_iteration_counter =
      ((double)i - std::log2(std::log2(z.sq_mag())));

  return std::make_pair((smooth_iteration_counter / ((double)max_iterations)),
                        i);
}
} // namespace BurningShip
} // namespace Fractals
