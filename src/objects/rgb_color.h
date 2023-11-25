#pragma once

#include <algorithm>
#include <cstdint>
#include <cstdio>

struct RGBColor {
  RGBColor() = default;
  RGBColor(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}

  static RGBColor from_double(double r, double g, double b) {
    RGBColor color;

    if (r > 1.0 || g > 1.0 || b > 1.0) {
      color.red = static_cast<uint8_t>(std::min(255.0, std::max(0.0, r)));
      color.green = static_cast<uint8_t>(std::min(255.0, std::max(0.0, g)));
      color.blue = static_cast<uint8_t>(std::min(255.0, std::max(0.0, b)));
    } else {
      color.red = static_cast<uint8_t>(r * 255.0);
      color.green = static_cast<uint8_t>(g * 255.0);
      color.blue = static_cast<uint8_t>(b * 255.0);
    }

    return color;
  }

  RGBColor lerp(const RGBColor &other, double t) const {
    return RGBColor(this->red + (other.red - this->red) * t,
                    this->green + (other.green - this->green) * t,
                    this->blue + (other.blue - this->blue) * t);
  }

  static RGBColor from_hue(double hue) {
    hue *= 6;
    int i = static_cast<int>(hue);
    double f = hue - i;
    double q = 1 - f;

    switch (i % 6) {
    case 0:
      return {255, static_cast<uint8_t>(f * 255), 0};
    case 1:
      return {static_cast<uint8_t>(q * 255), 255, 0};
    case 2:
      return {0, 255, static_cast<uint8_t>(f * 255)};
    case 3:
      return {0, static_cast<uint8_t>(q * 255), 255};
    case 4:
      return {static_cast<uint8_t>(f * 255), 0, 255};
    case 5:
      return {255, 0, static_cast<uint8_t>(q * 255)};
    }

    return {0, 0, 0}; // Fallback for undefined hue
  }

  static std::vector<RGBColor> purple_blue_palette() {
    static std::vector<RGBColor> palette{
        {128, 0, 128},  {139, 0, 139},   {148, 0, 211},  {153, 50, 204},
        {186, 85, 211}, {147, 112, 219}, {138, 43, 226}, {106, 90, 205},
        {72, 61, 139},  {25, 25, 112}};
    return palette;
  }

  void print() const {
    printf("RGBColor { r: %u, g: %u, b: %u }\n", red, green, blue);
  }

  uint8_t red;
  uint8_t green;
  uint8_t blue;
};
