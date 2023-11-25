#include <cstdint>

#pragma pack(push)
#pragma pack(1)
struct BitmapHeader {
    char magic_number[2];
    uint32_t size;
    uint32_t reserved;
    uint32_t offset;
};
#pragma pack(pop)
