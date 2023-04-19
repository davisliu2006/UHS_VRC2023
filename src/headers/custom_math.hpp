#pragma once

#include <cmath>

using namespace std;

// trigonometry
inline double rad(double x) {return x*M_PI/180;}
inline double deg(double x) {return x*180/M_PI;};
inline double angl_360(double x) {
    x = fmod(x, 360);
    if (x < 0) {x += 360;}
    return x;
}
inline double angl_180(double x) {
    x = fmod(x, 360);
    if (x > 180) {x -= 360;}
    else if (x <= -180) {x += 360;}
    return x;
}

// simple math
template <class type>
inline type sq(type x) {return x*x;}
template <class type>
inline type sign(type x) {
    return (x >= 0? 1 : -1);
}
template <class type>
inline type in_range(type var, type lo, type hi) {
    return lo <= var && var <= hi;
}