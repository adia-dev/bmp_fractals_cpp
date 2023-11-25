#include <fstream>
#include <iostream>
#include <memory>

#include "BMP.h"

BMP::BMP(uint32_t width, uint32_t height) {
  header.magic_number[0] = 'B';
  header.magic_number[1] = 'M';
  header.reserved = 0;

  info_header.size = sizeof(info_header);
  info_header.width = width;
  info_header.height = height;
  info_header.planes = 1;
  info_header.bpp = 24;
  info_header.compression = 0;
  info_header.x_pixels_per_m = 0;
  info_header.y_pixels_per_m = 0;
  info_header.colors_used = 0;
  info_header.important_colors = 0;

  data = std::make_unique<uint8_t[]>(width * height * 3);

  padding = (4 - (width * 3) % 4) % 4;
  row_size = width * 3 + padding;
  bmp_size = row_size * height;

  header.size = bmp_size + sizeof(header) + sizeof(info_header);
  header.offset = sizeof(header) + sizeof(info_header);

  info_header.image_size = bmp_size;
}

BMP::BMP(uint32_t width, uint32_t height, Pixel color) : BMP(width, height) {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      uint32_t index = (y * width + x) * 3;

      data[index] = color.blue;
      data[index + 1] = color.green;
      data[index + 2] = color.red;
    }
  }
}

BMP::BMP(uint32_t width, uint32_t height, uint8_t color[3])
    : BMP(width, height) {

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      uint32_t index = (y * width + x) * 3;

      data[index] = color[0];
      data[index + 1] = color[1];
      data[index + 2] = color[2];
    }
  }
}

void BMP::set_pixel(uint32_t x, uint32_t y, uint8_t pixel[3]) {
  if (x < 0 || x >= info_header.width || y < 0 || y >= info_header.height) {
    std::cerr << "Error: Pixel coordinates out of bounds\n";
    return;
  }

  uint32_t index = (y * info_header.width + x) * 3;
  data[index] = pixel[0];
  data[index + 1] = pixel[1];
  data[index + 2] = pixel[2];
}

void BMP::set_pixel(uint32_t x, uint32_t y, const Pixel &pixel) {
  if (x < 0 || x >= info_header.width || y < 0 || y >= info_header.height) {
    std::cerr << "Error: Pixel coordinates out of bounds\n";
    return;
  }

  uint32_t index = (y * info_header.width + x) * 3;
  data[index] = pixel.blue;
  data[index + 1] = pixel.green;
  data[index + 2] = pixel.red;
}

void BMP::write(const std::string &filename) {
  std::ofstream file(filename, std::ios::out | std::ios::binary);

  if (!file) {
    std::cerr << "Error: Cannot create BMP file " << filename << "\n";
    return;
  }

  const char padding_data[3] = {0, 0, 0};

  file.write(reinterpret_cast<const char *>(&header), sizeof(header));
  file.write(reinterpret_cast<const char *>(&info_header), sizeof(info_header));

  for (int y = 0; y < info_header.height; ++y) {
    file.write(
        reinterpret_cast<const char *>(data.get() + y * info_header.width * 3),
        info_header.width * 3);
    file.write(padding_data, padding);
  }
}
