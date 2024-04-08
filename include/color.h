#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

// alias of vec3 for readability
using Color = vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0) {
        return sqrt(linear_component);
    }
    return 0;
}

void write_color(std::ostream &out, Color pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // apply linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // translate the [0,1] component values to the byte range [0,255].
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif