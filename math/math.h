#ifndef MATHLIB_H
#define MATHLIB_H

#define PI 3.14159265358979323846f

union Vec3;
union Vec4;
union Quaternion;

union Vec2 {
    struct {
        f32 x, y;
    };
    struct {
        f32 u, v;
    };
    struct {
        f32 width, height;
    };
    
    Vec2();
    Vec2(f32 value);
    Vec2(f32 x, f32 y);
    Vec2(f32 data[]);
    Vec2(const Vec2& vec);
    Vec2(Vec3 vec);
    Vec2(Vec4 vec);
    
    f32& operator[](int index);
};

union Vec3 {
    struct {
        f32 x, y, z;
    };
    struct {
        f32 u, v, w;
    };
    struct {
        f32 r, g, b;
    };
    
    Vec3();
    Vec3(f32 value);
    Vec3(f32 x, f32 y, f32 z);
    Vec3(f32 data[]);
    Vec3(Vec2 vec);
    Vec3(Vec2 vec, f32 z);
    Vec3(const Vec3& vec);
    Vec3(Vec4 vec);
    
    f32& operator[](int index);
    
};

union Vec4 {
    struct {
        f32 x, y, z, w;
    };
    struct {
        f32 r, g, b, a;
    };
    
    Vec4();
    Vec4(f32 value);
    Vec4(f32 x, f32 y, f32 z, f32 w);
    Vec4(f32 data[]);
    Vec4(Vec2 vec);
    Vec4(Vec3 vec);
    Vec4(Vec3 vec, f32 w);
    Vec4(const Vec4& vec);
    Vec4(Quaternion quaternion);
    
    f32 operator[](int index);
};

union Quaternion {
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    f32 data[4];
    
    Quaternion();
    Quaternion(f32 x, f32 y, f32 z, f32 w);
    Quaternion(Vec4 vec);
    Quaternion(Vec3 axis, f32 angle);
};

union Matrix4;

union Matrix3 {
    f32 data[9];
    struct {
        f32 _0;
        f32 _1;
        f32 _2;
        f32 _3;
        f32 _4;
        f32 _5;
        f32 _6;
        f32 _7;
        f32 _8;
    };
    
    Matrix3();
    Matrix3(f32[]);
    Matrix3(Vec3 vec_1, Vec3 vec_2, Vec3 vec_3);
    Matrix3(Matrix4 mat);
    
    Matrix3 operator=(Matrix3 mat);
    Vec3 operator[](int index);
};

union Matrix4 {
    f32 data[16];
    struct {
        f32 _0;
        f32 _1;
        f32 _2;
        f32 _3;
        f32 _4;
        f32 _5;
        f32 _6;
        f32 _7;
        f32 _8;
        f32 _9;
        f32 _10;
        f32 _11;
        f32 _12;
        f32 _13;
        f32 _14;
        f32 _15;
    };
    
    Matrix4();
    Matrix4(const f32[]);
    Matrix4(Vec4 vec_1, Vec4 vec_2, Vec4 vec_3, Vec4 vec_4);
    
    Matrix4 operator=(Matrix4 mat);
    Vec4 operator[](int index);
};

const Matrix3 IDENTITY_3X3;
const Matrix4 IDENTITY_4X4;

struct RandomSeries {
    u32 state;
};

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

function Vec3
rotate(Vec3 vec, Vec3 axis, f32 angle) {
    Quaternion rotation = make_quaternion(axis, angle);
    Quaternion vec_quaternion;
    
    vec_quaternion.x = vec.x;
    vec_quaternion.y = vec.y;
    vec_quaternion.z = vec.z;
    vec_quaternion.w = 0.0f;
    vec_quaternion = rotation * vec_quaternion * conjugate(rotation);
    
    vec.x = vec_quaternion.x;
    vec.y = vec_quaternion.y;
    vec.z = vec_quaternion.z;
    
    return vec;
}

function inline f32
rad(f32 degrees) {
    return degrees * (PI/180);
}

function inline f32
deg(f32 radians) {
    return radians * (180/PI);
}

function inline f32
lerp(f32 t, f32 x, f32 y) {
    f32 result = (1.0f - t)*x + t*y;
    
    return result;
}

function inline f64
lerp(f64 t, f64 x, f64 y) {
    f64 result = (1.0 - t)*x + t*y;
    
    return result;
}

function inline Vec2
lerp(f32 t, Vec2 a, Vec2 b) {
    return a + t*(b - a);
}

function inline Vec3
lerp(f32 t, Vec3 a, Vec3 b) {
    return a + t*(b - a);
}

function inline f32
smoothstep(f32 t) {
    return (3 - 2*t)*(t*t);
}

function inline f64
smoothstep(f64 t) {
    return (3 - 2*t)*(t*t);
}

function Vec3
newell_normal(u32 num_vertices, Vec3 *vertices) {
    u32 i,j;
    Vec3 normal;
    for (i=num_vertices-1,j=0; j < num_vertices; i=j++) {
        Vec3 u = vertices[i];
        Vec3 v = vertices[j];
        normal.x += (u.y - v.y) * (u.z + v.z);
        normal.y += (u.z - v.z) * (u.x + v.x);
        normal.z += (u.x - v.x) * (u.y + v.y);
    }
    
    normal = normalize(normal);
    
    return normal;
}

function inline RandomSeries
random_seed(u32 seed = 78953890) {
    RandomSeries series;
    series.state = seed;
    
    return series;
}

function inline u32
random_next_u32(RandomSeries *series) {
    u32 result = series->state;
    result ^= result << 13;
    result ^= result >> 17;
    result ^= result << 5;
    series->state = result;
    
    return result;
}

// function inline u32
// random_choice(RandomSeries *series, u32 min, u32 max) {

// }

function inline f32
random_unilateral(RandomSeries *series) {
    f32 divisor = 1.0f / (f32)U32_MAX;
    f32 result = divisor*(f32)random_next_u32(series);
    
    return result;
}

function inline f32
random_bilateral(RandomSeries *series) {
    f32 result = 2.0f*random_unilateral(series) - 1.0f;
    
    return result;
}

function inline f32
random_between(RandomSeries *series, f32 min, f32 max) {
    return lerp(random_unilateral(series), min, max);
}


#endif
