#pragma once

#include <cmath>

using namespace std;

// trigonometry
inline double rad(double x) {return x*M_PI/180;}
inline double deg(double x) {return x*180/M_PI;};

// polynomial
template <class type>
inline type sq(type x) {return x*x;}
