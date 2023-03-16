#ifndef MATRIX_H
#define MATRIX_H

//
// Matrix3
//

Matrix3::Matrix3() {
    this->data[0] = 1.0f; this->data[1] = 0.0f; this->data[2] = 0.0f;
    this->data[3] = 0.0f; this->data[4] = 1.0f; this->data[5] = 0.0f;
    this->data[6] = 0.0f; this->data[7] = 0.0f; this->data[8] = 1.0f;
}

Matrix3::Matrix3(f32 *data) {
    this->data[0] = data[0]; this->data[1] = data[1]; this->data[2] = data[2];
    this->data[3] = data[3]; this->data[4] = data[4]; this->data[5] = data[5];
    this->data[6] = data[6]; this->data[7] = data[7]; this->data[8] = data[8];
}

Matrix3::Matrix3(Vec3 vec_1, Vec3 vec_2, Vec3 vec_3) {
    this->data[0] = vec_1.x; this->data[1] = vec_2.x; this->data[2] = vec_3.x;
    this->data[3] = vec_1.y; this->data[4] = vec_2.y; this->data[5] = vec_3.y;
    this->data[6] = vec_1.z; this->data[7] = vec_2.z; this->data[8] = vec_3.z;
}

Matrix3::Matrix3(Matrix4 mat) {
    this->data[0] = mat.data[0]; this->data[1] = mat.data[1]; this->data[2] = mat.data[2];
    this->data[3] = mat.data[4]; this->data[4] = mat.data[5]; this->data[5] = mat.data[6];
    this->data[6] = mat.data[8]; this->data[7] = mat.data[9]; this->data[8] = mat.data[10];
}

void print(Matrix3 mat) {
    printf("%f\t%f\t%f\n", mat.data[0], mat.data[1], mat.data[2]);
    printf("%f\t%f\t%f\n", mat.data[3], mat.data[4], mat.data[5]);
    printf("%f\t%f\t%f\n", mat.data[6], mat.data[7], mat.data[8]);
}

Matrix3 operator+(Matrix3 mat_1, Matrix3 mat_2) {
    Matrix3 result;
    
    for (int i = 0; i < 9; ++i) {
        result.data[i] = mat_1.data[i] + mat_2.data[i];
    }
    
    return result;
}

Matrix3 operator-(Matrix3 mat_1, Matrix3 mat_2) {
    Matrix3 result;
    
    for (int i = 0; i < 9; ++i) {
        result.data[i] = mat_1.data[i] - mat_2.data[i];
    }
    
    return result;
}

Matrix3 operator*(f32 scalar, Matrix3 mat) {
    Matrix3 result;
    
    for (int i = 0; i < 9; ++i) {
        result.data[i] = mat.data[i] * scalar;
    }
    
    return result;
}

Matrix3 operator*(Matrix3 mat, f32 scalar) {
    return scalar * mat;
}

Matrix3& operator*=(Matrix3& mat, f32 scalar) {
    for (int i = 0; i < 9; ++i) {
        mat.data[i] *= scalar;
    }
    
    return mat;
}

Matrix3 operator*(Matrix3 mat_1, Matrix3 mat_2) {
    Matrix3 result;
    
    for (int i = 0; i < 9; ++i) {
        int row = i/3;
        int col = i%3;
        result.data[i] = mat_1.data[row*3] * mat_2.data[col] + mat_1.data[row*3+1] * mat_2.data[col+3] + mat_1.data[row*3+2] * mat_2.data[col+6];
    }
    
    return result;
}

Matrix3& operator*=(Matrix3 &mat_1, Matrix3 mat_2) {
    Matrix3 tmp;
    
    for (int i = 0; i < 9; ++i) {
        int row = i/3;
        int col = i%3;
        tmp.data[i] = mat_1.data[row*3] * mat_2.data[col] + mat_1.data[row*3+1] * mat_2.data[col+3] + mat_1.data[row*3+2] * mat_2.data[col+6];
    }
    
    mat_1 = tmp;
    
    return mat_1;
}

Vec3 operator*(Matrix3 mat, Vec3 vec) {
    Vec3 result;
    
    result.x = mat.data[0] * vec.x + mat.data[1] * vec.y + mat.data[2] * vec.z;
    result.y = mat.data[3] * vec.x + mat.data[4] * vec.y + mat.data[5] * vec.z;
    result.z = mat.data[6] * vec.x + mat.data[7] * vec.y + mat.data[8] * vec.z;
    
    return result;
}

Matrix3 Matrix3::operator=(Matrix3 mat) {
    for (int i = 0; i < 9; ++i) {
        this->data[i] = mat.data[i];
    }
    
    return *this;
}

Matrix3& operator+=(Matrix3& mat_1, Matrix3 mat_2) {
    for (int i = 0; i < 9; ++i) {
        mat_1.data[i] += mat_2.data[i];
    }
    
    return mat_1;
}

Matrix3& operator-=(Matrix3& mat_1, Matrix3 mat_2) {
    for (int i = 0; i < 9; ++i) {
        mat_1.data[i] -= mat_2.data[i];
    }
    
    return mat_1;
}

Vec3 Matrix3::operator[](int index) {
    Vec3 result;
    
    result.x = this->data[index];
    result.y = this->data[index+3];
    result.z = this->data[index+6];
    
    return result;
}

Matrix3 transpose(Matrix3 mat) {
    Matrix3 result;
    
    result.data[0] = mat.data[0];
    result.data[1] = mat.data[3];
    result.data[2] = mat.data[6];
    result.data[3] = mat.data[1];
    result.data[4] = mat.data[4];
    result.data[5] = mat.data[7];
    result.data[6] = mat.data[2];
    result.data[7] = mat.data[5];
    result.data[8] = mat.data[8];
    
    return result;
}

f32 determinant(Matrix3 mat) {
    f32 val1 = mat.data[0] * (mat.data[4] * mat.data[8] - mat.data[5] * mat.data[7]);
    f32 val2 = mat.data[1] * (mat.data[3] * mat.data[8] - mat.data[5] * mat.data[6]);
    f32 val3 = mat.data[2] * (mat.data[3] * mat.data[7] - mat.data[4] * mat.data[6]);
    
    return val1 - val2 + val3;
}

Matrix3 adjugate(Matrix3 mat) {
    f32 c[9];
    Matrix3 result;
    
    c[0] =  (mat.data[4] * mat.data[8] - mat.data[5] * mat.data[7]);
    c[1] = -(mat.data[3] * mat.data[8] - mat.data[5] * mat.data[6]);
    c[2] =  (mat.data[3] * mat.data[7] - mat.data[4] * mat.data[6]);
    c[3] = -(mat.data[1] * mat.data[8] - mat.data[2] * mat.data[7]);
    c[4] =  (mat.data[0] * mat.data[8] - mat.data[2] * mat.data[6]);
    c[5] = -(mat.data[0] * mat.data[7] - mat.data[1] * mat.data[6]);
    c[6] =  (mat.data[1] * mat.data[5] - mat.data[2] * mat.data[4]);
    c[7] = -(mat.data[0] * mat.data[5] - mat.data[2] * mat.data[3]);
    c[8] =  (mat.data[0] * mat.data[4] - mat.data[1] * mat.data[3]);
    
    result = Matrix3(c);
    
    return transpose(result);
}

Matrix3 inverse(Matrix3 mat) {
    return 1.0f/determinant(mat) * adjugate(mat);
}

Matrix3 scale(Matrix3 mat, Vec3 scale) {
    Matrix3 result = mat;
    
    result.data[0] = scale.x;
    result.data[4] = scale.y;
    result.data[8] = scale.z;
    
    return result;
}

Matrix3 skew_symmetric(Vec3 vec) {
    Matrix3 result;
    
    result.data[0] = 0.0f;
    result.data[1] = -vec.z;
    result.data[2] = vec.y;
    result.data[3] = vec.z;
    result.data[4] = 0.0f;
    result.data[5] = -vec.x;
    result.data[6] = -vec.y;
    result.data[7] = vec.x;
    result.data[8] = 0.0f;
    
    return result;
}

//
// Matrix4
//

Matrix4::Matrix4() {
    this->data[0] = 1.0f; this->data[1] = 0.0f; this->data[2] = 0.0f; this->data[3] = 0.0f;
    this->data[4] = 0.0f; this->data[5] = 1.0f; this->data[6] = 0.0f; this->data[7] = 0.0f;
    this->data[8] = 0.0f; this->data[9] = 0.0f; this->data[10] = 1.0f; this->data[11] = 0.0f;
    this->data[12] = 0.0f; this->data[13] = 0.0f; this->data[14] = 0.0f; this->data[15] = 1.0f;
}

Matrix4::Matrix4(const f32 data[]) {
    this->data[0] = data[0]; this->data[1] = data[1]; this->data[2] = data[2]; this->data[3] = data[3];
    this->data[4] = data[4]; this->data[5] = data[5]; this->data[6] = data[6]; this->data[7] = data[7];
    this->data[8] = data[8]; this->data[9] = data[9]; this->data[10] = data[10]; this->data[11] = data[11];
    this->data[12] = data[12]; this->data[13] = data[13]; this->data[14] = data[14]; this->data[15] = data[15];
}

Matrix4::Matrix4(Vec4 vec_1, Vec4 vec_2, Vec4 vec_3, Vec4 vec_4) {
    this->data[0] = vec_1.x; this->data[1] = vec_2.x; this->data[2] = vec_3.x; this->data[3] = vec_4.x;
    this->data[4] = vec_1.y; this->data[5] = vec_2.y; this->data[6] = vec_3.y; this->data[7] = vec_4.y;
    this->data[8] = vec_1.z; this->data[9] = vec_2.z; this->data[10] = vec_3.z; this->data[11] = vec_4.z;
    this->data[12] = vec_1.w; this->data[13] = vec_2.w; this->data[14] = vec_3.w; this->data[15] = vec_4.w;
}

void print(Matrix4 mat) {
    printf("%f\t%f\t%f\t%f\n", mat.data[0], mat.data[1], mat.data[2], mat.data[3]);
    printf("%f\t%f\t%f\t%f\n", mat.data[4], mat.data[5], mat.data[6], mat.data[7]);
    printf("%f\t%f\t%f\t%f\n", mat.data[8], mat.data[9], mat.data[10], mat.data[11]);
    printf("%f\t%f\t%f\t%f\n", mat.data[12], mat.data[13], mat.data[14], mat.data[15]);
}

Matrix4 operator+(Matrix4 mat_1, Matrix4 mat_2) {
    Matrix4 result;
    
    for (int i = 0; i < 16; ++i) {
        result.data[i] = mat_1.data[i] + mat_2.data[i];
    }
    
    return result;
}

Matrix4 operator-(Matrix4 mat_1, Matrix4 mat_2) {
    Matrix4 result;
    
    for (int i = 0; i < 16; ++i) {
        result.data[i] = mat_1.data[i] - mat_2.data[i];
    }
    
    return result;
}

Matrix4 operator*(f32 scalar, Matrix4 mat) {
    Matrix4 result;
    
    for (int i = 0; i < 16; ++i) {
        result.data[i] = mat.data[i] * scalar;
    }
    
    return result;
}

Matrix4 operator*(Matrix4 mat, f32 scalar) {
    return scalar * mat;
}

Matrix4 operator*(Matrix4 mat_1, Matrix4 mat_2) {
    Matrix4 result;
    
    for (int i = 0; i < 16; ++i) {
        int row = i/4;
        int col = i%4;
        result.data[i] = mat_1.data[row*4] * mat_2.data[col] + mat_1.data[row*4+1] * mat_2.data[col+4] + mat_1.data[row*4+2] * mat_2.data[col+8] + mat_1.data[row*4+3] * mat_2.data[col+12];
    }
    
    return result;
}

Vec4 operator*(Matrix4 mat, Vec4 vec) {
    Vec4 result;
    
    result.x = mat.data[0] * vec.x + mat.data[1] * vec.y + mat.data[2] * vec.z + mat.data[3] * vec.w;
    result.y = mat.data[4] * vec.x + mat.data[5] * vec.y + mat.data[6] * vec.z + mat.data[7] * vec.w;
    result.z = mat.data[8] * vec.x + mat.data[9] * vec.y + mat.data[10] * vec.z + mat.data[11] * vec.w;
    result.w = mat.data[12] * vec.x + mat.data[13] * vec.y + mat.data[14] * vec.z + mat.data[15] * vec.w;
    
    return result;
}

Matrix4 Matrix4::operator=(Matrix4 mat) {
    for (int i = 0; i < 16; ++i) {
        this->data[i] = mat.data[i];
    }
    
    return *this;
}

Matrix4& operator+=(Matrix4& mat_1, Matrix4 mat_2) {
    for (int i = 0; i < 16; ++i) {
        mat_1.data[i] += mat_2.data[i];
    }
    
    return mat_1;
}

Matrix4& operator-=(Matrix4& mat_1, Matrix4 mat_2) {
    for (int i = 0; i < 16; ++i) {
        mat_1.data[i] -= mat_2.data[i];
    }
    
    return mat_1;
}

Vec4 Matrix4::operator[](int index) {
    Vec4 result;
    
    result.x = this->data[index];
    result.y = this->data[index+4];
    result.z = this->data[index+8];
    result.w = this->data[index+12];
    
    return result;
}

Matrix4 transpose(Matrix4 mat) {
    Matrix4 result;
    
    result.data[0] = mat.data[0];
    result.data[1] = mat.data[4];
    result.data[2] = mat.data[8];
    result.data[3] = mat.data[12];
    result.data[4] = mat.data[1];
    result.data[5] = mat.data[5];
    result.data[6] = mat.data[9];
    result.data[7] = mat.data[13];
    result.data[8] = mat.data[2];
    result.data[9] = mat.data[6];
    result.data[10] = mat.data[10];
    result.data[11] = mat.data[14];
    result.data[12] = mat.data[3];
    result.data[13] = mat.data[7];
    result.data[14] = mat.data[11];
    result.data[15] = mat.data[15];
    
    return result;
}

Matrix4 translate(Matrix4 mat, Vec3 vec) {
    Matrix4 result = mat;
    Vec4 tmp_vec;
    
    tmp_vec = mat[0] * vec.x + mat[1] * vec.y + mat[2] * vec.z + mat[3];
    result.data[3] = tmp_vec.x;
    result.data[7] = tmp_vec.y;
    result.data[11] = tmp_vec.z;
    result.data[15] = tmp_vec.w;
    
    return result;
}

function Matrix4
size(Matrix4 mat, Vec3 vec) {
    mat.data[0] = vec.x;
    mat.data[5] = vec.y;
    mat.data[10] = vec.z;
    
    return mat;
}

Matrix3 _sub_matrix(Matrix4 mat, int index) {
    f32 data[9];
    
    int coeficient_row = index/4;
    int coeficient_col = index%4;
    
    int added_values = 0;
    for (int i = 0; i < 16; ++i) {
        int row = i/4;
        int col = i%4;
        
        if (row == coeficient_row) continue;
        if (col == coeficient_col) continue;
        
        data[added_values++] = mat.data[i];
    }
    
    return Matrix3(data);
}

f32 determinant(Matrix4 mat) {
    f32 val1 = mat.data[0] * determinant(_sub_matrix(mat, 0));
    f32 val2 = mat.data[1] * determinant(_sub_matrix(mat, 1));
    f32 val3 = mat.data[2] * determinant(_sub_matrix(mat, 2));
    f32 val4 = mat.data[3] * determinant(_sub_matrix(mat, 3));
    
    return val1 - val2 + val3 - val4;
}

Matrix4 adjugate(Matrix4 mat) {
    f32 c[16];
    
    c[0] =  determinant(_sub_matrix(mat, 0));
    c[1] = -determinant(_sub_matrix(mat, 1));
    c[2] =  determinant(_sub_matrix(mat, 2));
    c[3] = -determinant(_sub_matrix(mat, 3));
    c[4] = -determinant(_sub_matrix(mat, 4));
    c[5] =  determinant(_sub_matrix(mat, 5));
    c[6] = -determinant(_sub_matrix(mat, 6));
    c[7] =  determinant(_sub_matrix(mat, 7));
    c[8] =  determinant(_sub_matrix(mat, 8));
    c[9] = -determinant(_sub_matrix(mat, 9));
    c[10] =  determinant(_sub_matrix(mat, 10));
    c[11] = -determinant(_sub_matrix(mat, 11));
    c[12] = -determinant(_sub_matrix(mat, 12));
    c[13] =  determinant(_sub_matrix(mat, 13));
    c[14] = -determinant(_sub_matrix(mat, 14));
    c[15] =  determinant(_sub_matrix(mat, 15));
    
    Matrix4 result(c);
    
    return transpose(result);
}

Matrix4 inverse(Matrix4 mat) {
    return 1.0f/determinant(mat) * adjugate(mat);
}

Matrix4 scale(Matrix4 mat, Vec3 scale) {
    Matrix4 result = mat;
    
    result.data[0] *= scale.x;
    result.data[5] *= scale.y;
    result.data[10] *= scale.z;
    
    return result;
}

Matrix4 rotate(Matrix4 mat, Vec3 axis, f32 angle) {
    Matrix3 rotation;
    
    axis = normalize(axis);
    f32 cos_angle = (f32)cos(angle);
    f32 sin_angle = (f32)sin(angle);
    
    rotation.data[0] = cos_angle + (f32)pow(axis.x, 2)*(1 - cos_angle);
    rotation.data[1] = axis.x * axis.y * (1 - cos_angle) - axis.z * sin_angle;
    rotation.data[2] = axis.x * axis.z * (1 - cos_angle) + axis.y * sin_angle;
    rotation.data[3] = axis.y * axis.x * (1 - cos_angle) + axis.z * sin_angle;
    rotation.data[4] = cos_angle + (f32)pow(axis.y, 2)*(1 - cos_angle);
    rotation.data[5] = axis.y * axis.z * (1 - cos_angle) - axis.x * sin_angle;
    rotation.data[6] = axis.z * axis.x * (1 - cos_angle) - axis.y * sin_angle;
    rotation.data[7] = axis.z * axis.y * (1 - cos_angle) + axis.x * sin_angle;
    rotation.data[8] = cos_angle + (f32)pow(axis.z, 2)*(1 - cos_angle);
    
    Matrix4 result(mat[0] * rotation[0].x + mat[1] * rotation[0].y + mat[2] * rotation[0].z,
                   mat[0] * rotation[1].x + mat[1] * rotation[1].y + mat[2] * rotation[1].z,
                   mat[0] * rotation[2].x + mat[1] * rotation[2].y + mat[2] * rotation[2].z,
                   mat[3]);
    
    return result;
}

Matrix4 x_rotation(f32 angle) {
    return rotate(IDENTITY_4X4, Vec3(1.0f, 0.0f, 0.0f), angle);
}

Matrix4 y_rotation(f32 angle) {
    return rotate(IDENTITY_4X4, Vec3(0.0f, 1.0f, 0.0f), angle);
}

Matrix4 z_rotation(f32 angle) {
    return rotate(IDENTITY_4X4, Vec3(0.0f, 0.0f, 1.0f), angle);
}

Matrix4 look_at(Vec3 eye_point, Vec3 look_at_point, Vec3 world_up) {
    Matrix4 result;
    
    Vec3 view_z_axis = normalize(eye_point - look_at_point);
    world_up = normalize(world_up);
    Vec3 view_x_axis = normalize(cross(world_up, view_z_axis));
    Vec3 view_y_axis = normalize(cross(view_z_axis, view_x_axis));
    
    result.data[0] = view_x_axis.x;
    result.data[1] = view_x_axis.y;
    result.data[2] = view_x_axis.z;
    result.data[3] = 0.0f;
    result.data[4] = view_y_axis.x;
    result.data[5] = view_y_axis.y;
    result.data[6] = view_y_axis.z;
    result.data[7] = 0.0f;
    result.data[8] = view_z_axis.x;
    result.data[9] = view_z_axis.y;
    result.data[10] = view_z_axis.z;
    result.data[11] = 0.0f;
    result.data[12] = 0.0f;
    result.data[13] = 0.0f;
    result.data[14] = 0.0f;
    result.data[15] = 1.0f;
    
    result = translate(result, -eye_point);
    
    return result;
}

Matrix4 perspective(f32 fov, f32 aspect, f32 z_near, f32 z_far) {
    Matrix4 result;
    f32 tan_half_fov = (f32)tan(fov / 2.0f);
    
    result.data[0] = 1.0f / (aspect * tan_half_fov);
    result.data[5] = 1.0f / tan_half_fov;
    result.data[10] = - (z_far + z_near) / (z_far - z_near);
    result.data[11] = - (2.0f * z_far * z_near) / (z_far - z_near);
    result.data[14] = - 1.0f;
    result.data[15] = 0.0f;
    
    return result;
}

Matrix4 orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 z_near, f32 z_far) {
    Matrix4 result;
    
    result.data[0] = 2.0f / (right - left);
    result.data[3] = - (right + left) / (right - left);
    result.data[5] = 2.0f / (top - bottom);
    result.data[7] = - (top + bottom) / (top - bottom);
    result.data[10] = -2.0f / (z_far - z_near);
    result.data[11] = - (z_far + z_near) / (z_far - z_near);
    result.data[15] = 1.0f;
    
    return result;
}

#endif
