#include <iostream>
#include <string>

#include <BMP/BMP.h>

int main (int argc, char *argv[]) {
    BMP image(100, 100);
    image.write("../out/red_pixel.bmp");

    return 0;
}
