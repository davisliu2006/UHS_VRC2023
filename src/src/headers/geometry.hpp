#pragma once

#include <cmath>
#include <iostream>

#include "custom_math.hpp"

using namespace std;

// DATA TYPES

// vector2

struct vector2 {
    double x, y;

    vector2() {}
    vector2(double x1, double y1) {
        x = x1;
        y = y1;
    }
    vector2(double dir) {
        x = cos(dir);
        y = sin(dir);
    }

    double mag2() const {
        return x*x+y*y;
    }
    double mag() const {
        return sqrt(mag2());
    }
    double dir() const {
        return 0;
    }
    vector2 unit() const {
        double m = mag();
        return vector2(x/m, y/m);
    }
};

// print vector2
inline ostream& operator <<(ostream& out, const vector2& v) {
    out << v.x << ' ' << v.y;
    return out;
}

// vector2 negative
inline vector2 operator -(const vector2& v) {
    return vector2(-v.x, -v.y);
}

// vector2 addition
inline vector2 operator +(const vector2& v1, const vector2& v2) {
    return vector2(v1.x+v2.x, v1.y+v2.y);
}
inline vector2 operator +=(vector2& v1, const vector2& v2) {
    v1.x += v2.x; v1.y += v2.y;
    return v1;
}
inline vector2 operator -(const vector2& v1, const vector2& v2) {
    return vector2(v1.x-v2.x, v1.y-v2.y);
}
inline vector2 operator -=(vector2& v1, const vector2& v2) {
    v1.x -= v2.x; v1.y -= v2.y;
    return v1;
}

// vector2 scalar multiplication
inline vector2 operator *(const vector2& v, double scale) {
    return vector2(v.x*scale, v.y*scale);
}
inline vector2 operator *=(vector2& v, double scale) {
    v.x *= scale; v.y *= scale;
    return v;
}
inline vector2 operator /(const vector2& v, double scale) {
    return vector2(v.x/scale, v.y/scale);
}
inline vector2 operator /=(vector2& v, double scale) {
    v.x /= scale; v.y /= scale;
    return v;
}

// vector3

struct vector3 {
    double x, y, z;

    vector3() {}
    vector3(double x1, double y1, double z1) {
        x = x1;
        y = y1;
        z = z1;
    }

    double mag2() const {
        return x*x+y*y+z*z;
    }
    double mag() const {
        return sqrt(mag2());
    }
    vector3 unit() const {
        double m = mag();
        return vector3(x/m, y/m, z/m);
    }
};

// print vector3
inline ostream& operator <<(ostream& out, const vector3& v) {
    out << v.x << ' ' << v.y << ' ' << v.z;
    return out;
}

// vector2 negative
inline vector3 operator -(const vector3& v) {
    return vector3(-v.x, -v.y, -v.z);
}

// vector3 addition
inline vector3 operator +(const vector3& v1, const vector3& v2) {
    return vector3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}
inline vector3 operator +=(vector3& v1, const vector3& v2) {
    v1.x += v2.x; v1.y += v2.y; v1.z += v2.z;
    return v1;
}
inline vector3 operator -(const vector3& v1, const vector3& v2) {
    return vector3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}
inline vector3 operator -=(vector3& v1, const vector3& v2) {
    v1.x -= v2.x; v1.y -= v2.y; v1.z -= v2.z;
    return v1;
}

// vector3 scalar multiplication
inline vector3 operator *(const vector3& v, double scale) {
    return vector3(v.x*scale, v.y*scale, v.z*scale);
}
inline vector3 operator *=(vector3& v, double scale) {
    v.x *= scale; v.y *= scale; v.z *= scale;
    return v;
}
inline vector3 operator /(const vector3& v, double scale) {
    return vector3(v.x/scale, v.y/scale, v.z/scale);
}
inline vector3 operator /=(vector3& v, double scale) {
    v.x /= scale; v.y /= scale; v.z /= scale;
    return v;
}