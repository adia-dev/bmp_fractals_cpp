#pragma once

#include <cstdint>
#include <string>

#include <objects/pixel.h>

#include "bitmap_header.h"
#include "color_table.h"
#include "info_header.h"

typedef std::unique_ptr<uint8_t[]> PixelData;

#pragma pack(push)
#pragma pack(1)
class BMP {
public:
  BMP(uint32_t width, uint32_t height);
  BMP(uint32_t width, uint32_t height, Pixel color);
  BMP(uint32_t width, uint32_t height, uint8_t color[3]);

  void set_pixel(uint32_t x, uint32_t y, uint8_t pixel[3]);
  void set_pixel(uint32_t x, uint32_t y, const Pixel &pixel);

  void write(const std::string &filename);

  const uint8_t *pixels() const { return data.get(); }

  uint32_t width() const { return info_header.width; }
  uint32_t height() const { return info_header.height; }

private:
  BitmapHeader header;
  InfoHeader info_header;
  ColorTable *color_table;
  PixelData data;

  uint32_t padding;
  uint32_t row_size;
  uint32_t bmp_size;
};
#pragma pack(pop)
