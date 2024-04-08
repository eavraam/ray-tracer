#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <iostream>

// using
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


//> utility

// transform degrees to radians
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
// returns a random real number in [0,1)
inline double random_double() {
    return rand() / (RAND_MAX + 1.0f);
}
/*
# A modern C++ approach to getting a random number generator

#include <random>
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
*/

// returns a random real number in [min,max)
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

//< utility

// common headers
#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"


#endif