#pragma once

#include <Windows.h>
#include <wincrypt.h>
#include "../Hooks/kiero/imgui/imgui.h"

class Renderer {
public:
    bool OnScreen(ImVec2 coords);
    void DrawCornerBox(ImVec2 pos, ImVec2 dim, ImColor col, int thickness);
    void DrawBox(ImVec2 pos, ImVec2 dim, ImColor color, int thickness);
    void DrawFovCircle(float radius, int segments, ImColor color, int thickness);
    void DrawCrosshair(ImColor color, int size, int thickness);
    void DrawLine(ImVec2 dst, ImVec2 src, ImColor col, int thickness);
    void DrawText(ImVec2 pos, ImColor col, const char* text);
    void DrawHealthBar(ImVec2 pos, ImVec2 dim, ImColor col);
    void DrawFilledCircle(ImVec2 pos, float radius, float segments, ImColor col);
    bool IsFullscreen(HWND windowHandle);
    ImDrawList* GetDrawList();
    ImVec2 GetWindowSize();
    ImVec2 GetWindowMiddle();
};