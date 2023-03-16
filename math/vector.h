#ifndef VECTOR_H
#define VECTOR_H

//
// Vec2
//

Vec2::Vec2() {
    this->x = 0.0f;
    this->y = 0.0f;
}

Vec2::Vec2(f32 value) {
    this->x = value;
    this->y = value;
}

Vec2::Vec2(f32 x, f32 y) {
    this->x = x;
    this->y = y;
}

Vec2::Vec2(f32 data[]) {
    this->x = data[0];
    this->y = data[1];
}

Vec2::Vec2(const Vec2& vec) {
    this->x = vec.x;
    this->y = vec.y;
}

Vec2::Vec2(Vec3 vec) {
    this->x = vec.x;
    this->y = vec.y;
}

Vec2::Vec2(Vec4 vec) {
    this->x = vec.x;
    this->y = vec.y;
}

void print(Vec2 vec) {
    printf("%f\t%f\t\n", vec.x, vec.y);
}

Vec2 operator+(Vec2 vec_1, f32 scalar) {
    Vec2 result;
    
    result.x = vec_1.x + scalar;
    result.y = vec_1.y + scalar;
    
    return result;
}

Vec2& operator+=(Vec2 &vec_1, f32 scalar) {
    vec_1.x += scalar;
    vec_1.y += scalar;
    
    return vec_1;
}

Vec2 operator+(Vec2 vec_1, Vec2 vec_2) {
    Vec2 result;
    
    result.x = vec_1.x + vec_2.x;
    result.y = vec_1.y + vec_2.y;
    
    return result;
}

Vec2& operator+=(Vec2 &vec_1, Vec2 vec_2) {
    vec_1.x += vec_2.x;
    vec_1.y += vec_2.y;
    
    return vec_1;
}

Vec2 operator-(Vec2 vec) {
    Vec2 result;
    
    result.x = -vec.x;
    result.y = -vec.y;
    
    return result;
}

Vec2 operator-(Vec2 vec_1, f32 scalar) {
    Vec2 result;
    
    result.x = vec_1.x - scalar;
    result.y = vec_1.y - scalar;
    
    return result;
}

Vec2& operator-=(Vec2 &vec_1, f32 scalar) {
    vec_1.x -= scalar;
    vec_1.y -= scalar;
    
    return vec_1;
}

Vec2 operator-(Vec2 vec_1, Vec2 vec_2) {
    Vec2 result;
    
    result.x = vec_1.x - vec_2.x;
    result.y = vec_1.y - vec_2.y;
    
    return result;
}

Vec2& operator-=(Vec2 &vec_1, Vec2 vec_2) {
    vec_1.x -= vec_2.x;
    vec_1.y -= vec_2.y;
    
    return vec_1;
}

Vec2 operator*(Vec2 vec_1, Vec2 vec_2) {
    Vec2 result;
    
    result.x = vec_1.x * vec_2.x;
    result.y = vec_1.y * vec_2.y;
    
    return result;
}

Vec2 operator*(f32 scalar, Vec2 vec) {
    Vec2 result;
    
    result.x = scalar * vec.x;
    result.y = scalar * vec.y;
    
    return result;
}

Vec2 operator*(Vec2 vec, f32 scalar) {
    Vec2 result;
    
    result = scalar * vec;
    
    return result;
}

Vec2 operator/(Vec2 vec, f32 scalar) {
    Vec2 result;
    
    result.x = vec.x / scalar;
    result.y = vec.y / scalar;
    
    return result;
}

Vec2& operator/=(Vec2& vec, f32 scalar) {
    vec.x /= scalar;
    vec.y /= scalar;
    
    return vec;
}

Vec2 operator/(Vec2 vec_1, Vec2 vec_2) {
    Vec2 result;
    
    result.x = vec_1.x / vec_2.x;
    result.y = vec_1.y / vec_2.y;
    
    return result;
}

Vec2& operator/=(Vec2& vec_1, Vec2 vec_2) {
    vec_1.x /= vec_2.x;
    vec_1.y /= vec_2.y;
    
    return vec_1;
}

Vec2& operator*=(Vec2& vec_1, Vec2 vec_2) {
    vec_1.x *= vec_2.x;
    vec_1.y *= vec_2.y;
    
    return vec_1;
}

Vec2& operator*=(Vec2& vec, f32 scalar) {
    vec.x *= scalar;
    vec.y *= scalar;
    
    return vec;
}

bool operator==(Vec2 vec_1, Vec2 vec_2) {
    return vec_1.x == vec_2.x && vec_1.y == vec_2.y;
}

bool operator!=(Vec2 vec_1, Vec2 vec_2) {
    return !(vec_1 == vec_2);
}

f32& Vec2::operator[](int index) {
    switch (index) {
        case 0: return this->x;
        case 1: return this->y;
    }
    
    return this->x;
}

f32 length(Vec2 vec) {
    return (f32)sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

f32 squared_length(Vec2 vec) {
    return (f32)(pow(vec.x, 2) + pow(vec.y, 2));
}

Vec2 abs(Vec2 vec) {
    Vec2 result;
    
    result.x = vec.x >= 0 ? vec.x : -vec.x;
    result.y = vec.y >= 0 ? vec.y : -vec.y;
    
    return result;
}

Vec2 normalize(Vec2 vec) {
    f32 len = length(vec);
    
    return Vec2(vec.x/len, vec.y/len);
}

//
// Vec3
//

Vec3::Vec3() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

Vec3::Vec3(f32 value) {
    this->x = value;
    this->y = value;
    this->z = value;
}

Vec3::Vec3(f32 x, f32 y, f32 z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3::Vec3(f32 data[]) {
    this->x = data[0];
    this->y = data[1];
    this->z = data[2];
}

Vec3::Vec3(Vec2 vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = 0.0f;
}

Vec3::Vec3(Vec2 vec, f32 z) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = z;
}

Vec3::Vec3(const Vec3& vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
}

Vec3::Vec3(Vec4 vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
}

void print(Vec3 vec) {
    printf("%f\t%f\t%f\n", vec.x, vec.y, vec.z);
}

Vec3 operator+(Vec3 vec_1, Vec3 vec_2) {
    Vec3 result;
    
    result.x = vec_1.x + vec_2.x;
    result.y = vec_1.y + vec_2.y;
    result.z = vec_1.z + vec_2.z;
    
    return result;
}

Vec3 operator-(Vec3 vec) {
    Vec3 result;
    
    result.x = -vec.x;
    result.y = -vec.y;
    result.z = -vec.z;
    
    return result;
}

Vec3 operator-(Vec3 vec_1, Vec3 vec_2) {
    Vec3 result;
    
    result.x = vec_1.x - vec_2.x;
    result.y = vec_1.y - vec_2.y;
    result.z = vec_1.z - vec_2.z;
    
    return result;
}

Vec3 operator*(Vec3 vec_1, Vec3 vec_2) {
    Vec3 result;
    
    result.x = vec_1.x * vec_2.x;
    result.y = vec_1.y * vec_2.y;
    result.z = vec_1.z * vec_2.z;
    
    return result;
}

Vec3 operator*(f32 scalar, Vec3 vec) {
    Vec3 result;
    
    result.x = scalar * vec.x;
    result.y = scalar * vec.y;
    result.z = scalar * vec.z;
    
    return result;
}

Vec3 operator*(Vec3 vec, f32 scalar) {
    Vec3 result;
    
    result = scalar * vec;
    
    return result;
}

Vec3 operator/(Vec3 vec, f32 scalar) {
    Vec3 result;
    
    result.x = vec.x / scalar;
    result.y = vec.y / scalar;
    result.z = vec.z / scalar;
    
    return result;
}

Vec3& operator/=(Vec3& vec, f32 scalar) {
    vec.x /= scalar;
    vec.y /= scalar;
    vec.z /= scalar;
    
    return vec;
}

Vec3 operator/(Vec3 vec_1, Vec3 vec_2) {
    Vec3 result;
    
    result.x = vec_1.x / vec_2.x;
    result.y = vec_1.y / vec_2.y;
    result.z = vec_1.z / vec_2.z;
    
    return result;
}

Vec3& operator/=(Vec3& vec_1, Vec3 vec_2) {
    vec_1.x /= vec_2.x;
    vec_1.y /= vec_2.y;
    vec_1.z /= vec_2.z;
    
    return vec_1;
}

Vec3& operator+=(Vec3& vec_1, Vec3 vec_2) {
    vec_1.x += vec_2.x;
    vec_1.y += vec_2.y;
    vec_1.z += vec_2.z;
    
    return vec_1;
}

Vec3& operator-=(Vec3& vec_1, Vec3 vec_2) {
    vec_1.x -= vec_2.x;
    vec_1.y -= vec_2.y;
    vec_1.z -= vec_2.z;
    
    return vec_1;
}

Vec3& operator*=(Vec3& vec_1, Vec3 vec_2) {
    vec_1.x *= vec_2.x;
    vec_1.y *= vec_2.y;
    vec_1.z *= vec_2.z;
    
    return vec_1;
}

Vec3& operator*=(Vec3& vec, f32 scalar) {
    vec.x *= scalar;
    vec.y *= scalar;
    vec.z *= scalar;
    
    return vec;
}

f32& Vec3::operator[](int index) {
    switch (index) {
        case 0: return this->x;
        case 1: return this->y;
        case 2: return this->z;
    }
    
    return this->x;
}

f32 length(Vec3 vec) {
    return (f32)sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

f32 squared_length(Vec3 vec) {
    return (f32)(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

Vec3 abs(Vec3 vec) {
    Vec3 result;
    
    result.x = vec.x >= 0 ? vec.x : -vec.x;
    result.y = vec.y >= 0 ? vec.y : -vec.y;
    result.z = vec.z >= 0 ? vec.z : -vec.z;
    
    return result;
}

Vec3 normalize(Vec3 vec) {
    f32 len = length(vec);
    
    return Vec3(vec.x/len, vec.y/len, vec.z/len);
}

f32 dot(Vec3 vec_1, Vec3 vec_2) {
    return  vec_1.x * vec_2.x +
        vec_1.y * vec_2.y +
        vec_1.z * vec_2.z;
}

Vec3 cross(Vec3 vec_1, Vec3 vec_2) {
    Vec3 result;
    
    result.x = vec_1.y * vec_2.z - vec_1.z * vec_2.y;
    result.y = vec_1.z * vec_2.x - vec_1.x * vec_2.z;
    result.z = vec_1.x * vec_2.y - vec_1.y * vec_2.x;
    
    return result;
}

//
// Vec4
//

Vec4::Vec4() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 1.0f;
}

Vec4::Vec4(f32 value) {
    this->x = value;
    this->y = value;
    this->z = value;
    this->w = value;
}

Vec4::Vec4(f32 x, f32 y, f32 z, f32 w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4::Vec4(f32 data[]) {
    this->x = data[0];
    this->y = data[1];
    this->z = data[2];
    this->w = data[3];
}

Vec4::Vec4(Vec2 vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = 0.0f;
    this->w = 1.0f;
}

Vec4::Vec4(Vec3 vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
    this->w = 1.0f;
}

Vec4::Vec4(Vec3 vec, f32 w) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
    this->w = w;
}

Vec4::Vec4(const Vec4& vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
    this->w = vec.w;
}

Vec4::Vec4(Quaternion quaternion) {
    this->x = quaternion.x;
    this->y = quaternion.y;
    this->z = quaternion.z;
    this->w = quaternion.w;
}

void print(Vec4 vec) {
    printf("%f\t%f\t%f\t%f\n", vec.x, vec.y, vec.z, vec.w);
}

f32 length(Vec4 vec) {
    return (f32)sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2) + pow(vec.w, 2));
}

// Vec4 normalize(Vec4 vec) {
// }

Vec4 operator+(Vec4 vec_1, Vec4 vec_2) {
    Vec4 result;
    
    result.x = vec_1.x + vec_2.x;
    result.y = vec_1.y + vec_2.y;
    result.z = vec_1.z + vec_2.z;
    result.w = vec_1.w + vec_2.w;
    
    return result;
}

Vec4 operator-(Vec4 vec) {
    Vec4 result;
    
    result.x = -vec.x;
    result.y = -vec.y;
    result.z = -vec.z;
    result.w = -vec.w;
    
    return result;
}

Vec4 operator-(Vec4 vec_1, Vec4 vec_2) {
    Vec4 result;
    
    result.x = vec_1.x - vec_2.x;
    result.y = vec_1.y - vec_2.y;
    result.z = vec_1.z - vec_2.z;
    result.w = vec_1.w - vec_2.w;
    
    return result;
}

Vec4 operator*(Vec4 vec_1, Vec4 vec_2) {
    Vec4 result;
    
    result.x = vec_1.x * vec_2.x;
    result.y = vec_1.y * vec_2.y;
    result.z = vec_1.z * vec_2.z;
    result.w = vec_1.w * vec_2.w;
    
    return result;
}

Vec4 operator*(f32 scalar, Vec4 vec) {
    Vec4 result;
    
    result.x = scalar * vec.x;
    result.y = scalar * vec.y;
    result.z = scalar * vec.z;
    result.w = scalar * vec.w;
    
    return result;
}

Vec4 operator*(Vec4 vec, f32 scalar) {
    Vec4 result;
    
    result = scalar * vec;
    
    return result;
}

Vec4& operator+=(Vec4& vec_1, Vec4 vec_2) {
    vec_1.x += vec_2.x;
    vec_1.y += vec_2.y;
    vec_1.z += vec_2.z;
    vec_1.w += vec_2.w;
    
    return vec_1;
}

Vec4& operator-=(Vec4& vec_1, Vec4 vec_2) {
    vec_1.x -= vec_2.x;
    vec_1.y -= vec_2.y;
    vec_1.z -= vec_2.z;
    vec_1.w -= vec_2.w;
    
    return vec_1;
}

Vec4& operator*=(Vec4& vec_1, Vec4 vec_2) {
    vec_1.x *= vec_2.x;
    vec_1.y *= vec_2.y;
    vec_1.z *= vec_2.z;
    vec_1.w *= vec_2.w;
    
    return vec_1;
}

Vec4& operator*=(Vec4& vec, f32 scalar) {
    vec.x *= scalar;
    vec.y *= scalar;
    vec.z *= scalar;
    vec.w *= scalar;
    
    return vec;
}

Vec4 operator/(Vec4 vec, f32 scalar) {
    Vec4 result;
    
    result.x = vec.x / scalar;
    result.y = vec.y / scalar;
    result.z = vec.z / scalar;
    result.w = vec.w / scalar;
    
    return result;
}

Vec4& operator/=(Vec4& vec, f32 scalar) {
    vec.x /= scalar;
    vec.y /= scalar;
    vec.z /= scalar;
    vec.w /= scalar;
    
    return vec;
}

Vec4 operator/(Vec4 vec_1, Vec4 vec_2) {
    Vec4 result;
    
    result.x = vec_1.x / vec_2.x;
    result.y = vec_1.y / vec_2.y;
    result.z = vec_1.z / vec_2.z;
    result.w = vec_1.w / vec_2.w;
    
    return result;
}

Vec4& operator/=(Vec4& vec_1, Vec4 vec_2) {
    vec_1.x /= vec_2.x;
    vec_1.y /= vec_2.y;
    vec_1.z /= vec_2.z;
    vec_1.w /= vec_2.w;
    
    return vec_1;
}

f32 Vec4::operator[](int index) {
    switch (index) {
        case 0: return this->x;
        case 1: return this->y;
        case 2: return this->z;
        case 3: return this->w;
    }
    
    return -1.0f;
}

#endif
