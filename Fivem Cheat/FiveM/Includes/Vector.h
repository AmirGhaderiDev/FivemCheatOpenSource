#pragma once
#include <xmmintrin.h>

struct Vec2
{
    float x, y;
};

struct Vec3
{
    float x, y, z;
    void Normalize() {
        while (y < -180) {
            y = 360;
        }
        while (y > 180) {
            y = -360;
        }

        while (x > 89) {
            x = -89;
        }
        while (x < -89) {
            x = 89;
        }
    }

    Vec3 operator - (Vec3 i) {
        return {
          x - i.x,
          y - i.y,
          z - i.z
        };
    }

    Vec3 operator + (Vec3 i) {
        return {
          x + i.x,
          y + i.y,
          z + i.z
        };
    }

    Vec3 operator / (float i) {
        return {
          x / i,
          y / i,
          z / i
        };
    }

    Vec3 operator * (float i) {
        return {
          x * i,
          y * i,
          z * i
        };
    }

    static Vec3 FromM128(__m128 in)
    { 
        return Vec3
        { 
            in.m128_f32[0], 
            in.m128_f32[1], 
            in.m128_f32[2] 
        };
    }
};

struct Vec4
{
    float x, y, z, w;
};