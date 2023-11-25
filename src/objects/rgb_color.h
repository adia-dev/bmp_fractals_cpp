#pragma once

#include <cstdint>
#include <cstdio>

struct RGBColor {
  RGBColor(double r, double g, double b)
      : red(r * 255.0), green(g * 255.0), blue(b * 255.0) {}
  RGBColor(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}

  void print() const {
      printf("RGBColor { r: %u, g: %u, b: %u }\n", red, green, blue);
  }

  uint8_t red;
  uint8_t green;
  uint8_t blue;
};
