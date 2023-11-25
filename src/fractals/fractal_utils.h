#pragma once

#include "objects/rgb_color.h"
#include <cmath>
#include <cstdint>

namespace Fractals {
    // Color Function by Inigo Quilez
    static RGBColor color(double t) {
        double a[3]{0.5, 0.5, 0.5};
        double b[3]{0.5, 0.5, 0.5};
        double c[3]{1.0, 1.0, 1.0};

        double d[3]{0.0, 0.10, 0.20};

        const double i_dont_know_what_this_is = 6.28318;

        double red = b[0] * std::cos((i_dont_know_what_this_is * (c[0] * t + d[0]))) + a[0];
        double green = b[1] * std::cos((i_dont_know_what_this_is * (c[1] * t + d[1]))) + a[1];
        double blue = b[2] * std::cos((i_dont_know_what_this_is * (c[2] * t + d[2]))) + a[2];

        return RGBColor(red, green, blue);
    }
}
