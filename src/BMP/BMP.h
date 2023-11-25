#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bitmap_header.h"
#include "color_table.h"
#include "info_header.h"

typedef uint8_t *PixelData;

#pragma pack(push)
#pragma pack(1)
struct BMP {

  BMP(uint32_t width, uint32_t height) {
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

    padding = (4 - (width * 3) % 4) % 4;
    row_size = width * 3 + padding;
    bmp_size = row_size * height;

    header.size = bmp_size + sizeof(header) + sizeof(info_header);
    header.offset = sizeof(header) + sizeof(info_header);

    info_header.image_size = bmp_size;
  }

  void write(const std::string &filename) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);

    if (!file) {
      std::cerr << "Error: Cannot create BMP file " << filename << "\n";
      return;
    }

    file.write(reinterpret_cast<const char *>(&header), sizeof(header));
    file.write(reinterpret_cast<const char *>(&info_header),
               sizeof(info_header));

    std::vector<uint8_t> buffer(row_size, 0);

    for (int y = 0; y < info_header.height; ++y) {

      for (int x = 0; x < info_header.width; ++x) {
          buffer[x * 3 + 2] = 255;
      }

      file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    }
  }

  BitmapHeader header;
  InfoHeader info_header;
  ColorTable *color_table;
  PixelData *data;

  uint32_t padding;
  uint32_t row_size;
  uint32_t bmp_size;
};
#pragma pack(pop)
