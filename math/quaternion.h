#ifndef QUATERNION_H
#define QUATERNION_H

Quaternion::Quaternion() {
    x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;
}

Quaternion::Quaternion(f32 x, f32 y, f32 z, f32 w) {
    this->x = x, this->y = y, this->z = z, this->w = w;
}

Quaternion::Quaternion(Vec4 vec) {
    this->x = vec.x, this->y = vec.y, this->z = vec.z, this->w = vec.w;
}

Quaternion::Quaternion(Vec3 axis, f32 angle) {
    Vec3 tmp = axis * (f32)sin(angle/2.0f);
    x = tmp.x;
    y = tmp.y;
    z = tmp.z;
    w = (f32)cos(angle/2.0f);
}

function Quaternion
make_quaternion(Vec3 axis, f32 angle) {
    Quaternion result;
    
    Vec3 tmp = axis * (f32)sin(angle/2.0f);
    result.x = tmp.x;
    result.y = tmp.y;
    result.z = tmp.z;
    result.w = (f32)cos(angle/2.0f);
    
    return result;
}

Quaternion& operator*=(Quaternion& q1, Quaternion q2);

void print(Quaternion q) {
    printf("Quaternion { x: %f, y: %f, z: %f, w: %f }\n", q.x, q.y, q.z, q.w);
}

Quaternion operator+(Quaternion q1, Vec3 vec) {
    Quaternion result;
    Quaternion q2(vec.x, vec.y, vec.z, 0.0f);
    
    q2 *= q1;
    
    result.w = q1.w + q2.w * 0.5f;
    result.x = q1.x + q2.x * 0.5f;
    result.y = q1.y + q2.y * 0.5f;
    result.z = q1.z + q2.z * 0.5f;
    
    return result;
}

Quaternion& operator+=(Quaternion& q1, Vec3 vec) {
    Quaternion q2(vec.x, vec.y, vec.z, 0.0f);
    
    q2 *= q1;
    
    q1.w += q2.w * 0.5f;
    q1.x += q2.x * 0.5f;
    q1.y += q2.y * 0.5f;
    q1.z += q2.z * 0.5f;
    
    return q1;
}

Quaternion operator*(Quaternion q1, Quaternion q2) {
    Quaternion result;
    
#if 0
    result.w = (q2.w * q1.w) - (q2.x * q1.x) - (q2.y * q1.y) - (q2.z * q1.z);
    result.x = (q2.w * q1.x) + (q2.x * q1.w) + (q2.y * q1.z) - (q2.z * q1.y);
    result.y = (q2.w * q1.y) + (q2.y * q1.w) + (q2.z * q1.x) - (q2.x * q1.z);
    result.z = (q2.w * q1.z) + (q2.z * q1.w) + (q2.x * q1.y) - (q2.y * q1.x);
#endif
    // result.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
    // result.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
    // result.y = q1.w*q2.y + q1.x*q2.z + q1.y*q2.w - q1.z*q2.x;
    // result.z = q1.w*q2.z + q1.x*q2.y + q1.y*q2.x - q1.z*q2.w;
    
    result.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
    result.x = q1.w*q2.x + q1.x*q2.w - q1.y*q2.z - q1.z*q2.y;
    result.y = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w - q1.z*q2.x;
    result.z = q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w;
    
    return result;
}

Quaternion& operator*=(Quaternion& q1, Quaternion q2) {
    Quaternion result;
    
#if 0
    // Irrlicht
    result.w = (q2.w * q1.w) - (q2.x * q1.x) - (q2.y * q1.y) - (q2.z * q1.z);
    result.x = (q2.w * q1.x) + (q2.x * q1.w) + (q2.y * q1.z) - (q2.z * q1.y);
    result.y = (q2.w * q1.y) + (q2.y * q1.w) + (q2.z * q1.x) - (q2.x * q1.z);
    result.z = (q2.w * q1.z) + (q2.z * q1.w) + (q2.x * q1.y) - (q2.y * q1.x);
    
#endif
    // New
    // result.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
    // result.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
    // result.y = q1.w*q2.y + q1.x*q2.z + q1.y*q2.w - q1.z*q2.x;
    // result.z = q1.w*q2.z + q1.x*q2.y + q1.y*q2.x - q1.z*q2.w;
    // Old
    result.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
    result.x = q1.w*q2.x + q1.x*q2.w - q1.y*q2.z - q1.z*q2.y;
    result.y = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w - q1.z*q2.x;
    result.z = q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w;
    
    q1 = result;
    
    return q1;
}

function Matrix4
get_matrix(Quaternion q) {
    Matrix4 rotation = IDENTITY_4X4;
    rotation.data[0] = 1 - 2.0f*q.y*q.y - 2.0f*q.z*q.z;
    rotation.data[1] = 2.0f*q.x*q.y + 2.0f*q.z*q.w;
    rotation.data[2] = 2.0f*q.x*q.z - 2.0f*q.y*q.w;
    
    rotation.data[4] = 2.0f*q.x*q.y - 2.0f*q.z*q.w;
    rotation.data[5] = 1 - 2.0f*q.x*q.x - 2.0f*q.z*q.z;
    rotation.data[6] = 2.0f*q.y*q.z + 2.0f*q.x*q.w;
    
    rotation.data[8] = 2.0f*q.x*q.z + 2.0f*q.y*q.w;
    rotation.data[9] = 2.0f*q.y*q.z - 2.0f*q.x*q.w;
    rotation.data[10] = 1 - 2.0f*q.x*q.x - 2.0f*q.y*q.y;
    
    return rotation;
}

function Quaternion
conjugate(Quaternion q) {
    Quaternion result;
    
    result.x = -q.x;
    result.y = -q.y;
    result.z = -q.z;
    result.w = q.w;
    
    return result;
}

function Quaternion
normalize(Quaternion q) {
    f32 d = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
    
    if (d == 0.0f) {
        q.w = 1.0;
        return q;
    }
    
    d = 1.0f/(f32)sqrt(d);
    q.x *= d;
    q.y *= d;
    q.z *= d;
    q.w *= d;
    
    return q;
}

void normalize(Quaternion *q) {
    f32 d = q->x*q->x + q->y*q->y + q->z*q->z + q->w*q->w;
    
    if (d == 0.0f) {
        q->w = 1.0;
        return;
    }
    
    d = 1.0f/(f32)sqrt(d);
    q->x *= d;
    q->y *= d;
    q->z *= d;
    q->w *= d;
}

Quaternion rotate_by_vector(Quaternion q1, Vec3 vec) {
    Quaternion q2(vec.x, vec.y, vec.z, 0);
    return q1 * q2;
}

Vec3 get_direction(Quaternion q) {
    Vec3 dir;
    
    f32 half_angle = (f32)acos(q.w);
    dir.x = q.x / (f32)sin(half_angle);
    dir.y = q.y / (f32)sin(half_angle);
    dir.z = q.z / (f32)sin(half_angle);
    
    return normalize(dir);
}

f32 get_angle(Quaternion q) {
    Vec3 axis;
    f32 scale = (f32)sqrt(q.x*q.x + q.y*q.y + q.z*q.z);
    
    if (scale == 0.0f || q.w > 1.0f || q.w < -1.0f) {
        return 0.0f;
    }
    
    f32 invscale = 1.0f/scale;
    axis.z = q.z * invscale;
    
    if (axis.z == -1.0) {
        return 2 * PI - 2.0f * (f32)acos(q.w);
    }
    
    return 2.0f * (f32)acos(q.w);
}

#endif
