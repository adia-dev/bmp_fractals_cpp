#pragma once

#include <cstdint>

#pragma pack(push)
#pragma pack(1)
struct ColorTable {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t reserved;
};
#pragma pack(pop)
