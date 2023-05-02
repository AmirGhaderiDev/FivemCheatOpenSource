#pragma once

#include "../Includes/Globals.hpp"
#include "../Includes/Vector.h"

float pythag(ImVec2 src, ImVec2 dst)
{
    return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
}

float pythagVec3(Vec3 src, Vec3 dst)
{
    return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2) + pow(src.z - dst.z, 2));
}

void SetAngle(Vec3 target, CPlayerAngles* ANGLES)
{
    uintptr_t CNav = *(uintptr_t*)(Globals::LocalPlayer + 0x30);
    Vec3 current_angles = ANGLES->ViewAngles2;
    Vec3 MyPos = ANGLES->Crosshair_Location;
    Vec3 delta = { MyPos.x - target.x, MyPos.y - target.z , MyPos.y - target.y };
    float hyp = pythagVec3(MyPos, target);
    Vec3 Out = { (target.x - MyPos.x) / hyp, (target.y - MyPos.y) / hyp, (target.z - MyPos.z) / hyp };
    Vec3 delta_angles = current_angles - Out;
    Vec3 final_smooth = current_angles - delta_angles / Globals::AimbotOptions::smoothing;
    ANGLES->ViewAngles2 = final_smooth;
}

ImVec2 WorldToScreen(Vec3 pos)
{
    auto& io = ImGui::GetIO();
    ImVec2 tempVec2;
    reinterpret_cast<bool(__fastcall*)(Vec3*, float*, float*)>(Globals::w2s)(&pos, &tempVec2.x, &tempVec2.y);
    tempVec2.x *= io.DisplaySize.x;
    tempVec2.y *= io.DisplaySize.y;
    return tempVec2;
}

ImVec2 GetBonePosW2S(const int64_t cPed, const int32_t wMask)
{
    __m128 tempVec4;
    reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(Globals::BonePosPtr)(cPed, &tempVec4, wMask);
    return WorldToScreen(Vec3::FromM128(tempVec4));
}

Vec3 GetBonePos(const int64_t cPed, const int32_t wMask)
{
    __m128 tempVec4;
    reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(Globals::BonePosPtr)(cPed, &tempVec4, wMask);
    return Vec3::FromM128(tempVec4);
}