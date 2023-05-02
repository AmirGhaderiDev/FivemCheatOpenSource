#include "Renderer.h"

bool Renderer::OnScreen(ImVec2 coords)
{
    if (coords.x < 0.1f || coords.y < 0.1 || coords.x > this->GetWindowSize().x || coords.y > this->GetWindowSize().y)
    {
        return false;
    }
    else {
        return true;
    }
}

void Renderer::DrawCornerBox(ImVec2 pos, ImVec2 dim, ImColor col, int thickness)
{
    if (this->OnScreen(pos)) {
        float cornersizex = dim.x / 3;
        float cornersizey = dim.y / 4;

        ImDrawList* drawlist = this->GetDrawList();

        drawlist->AddLine(ImVec2(pos), ImVec2(pos.x - cornersizex, pos.y), col, thickness);

        drawlist->AddLine(ImVec2(pos.x - dim.x, pos.y), ImVec2((pos.x - dim.x) + cornersizex, pos.y), col, thickness);

        drawlist->AddLine(ImVec2(pos.x - dim.x, pos.y), ImVec2(pos.x - dim.x, pos.y - cornersizey), col, thickness);

        drawlist->AddLine(ImVec2(pos.x - dim.x, (pos.y - dim.y)), ImVec2(pos.x - dim.x, (pos.y - dim.y) + cornersizey), col, thickness);

        drawlist->AddLine(ImVec2(pos.x - dim.x, (pos.y - dim.y)), ImVec2((pos.x - dim.x) + cornersizex, pos.y - dim.y), col, thickness);

        drawlist->AddLine(ImVec2(pos.x, (pos.y - dim.y)), ImVec2(pos.x - cornersizex, pos.y - dim.y), col, thickness);

        drawlist->AddLine(ImVec2(pos.x, (pos.y - dim.y)), ImVec2(pos.x, (pos.y - dim.y) + cornersizey), col, thickness);

        drawlist->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x, pos.y - cornersizey), col, thickness);

    }
}

void Renderer::DrawBox(ImVec2 pos, ImVec2 dim, ImColor color, int thickness)
{
    if (this->OnScreen(pos))
    {
        this->GetDrawList()->AddLine(pos, ImVec2(pos.x - dim.x, pos.y), color, thickness);
        this->GetDrawList()->AddLine(ImVec2(pos.x - dim.x, pos.y), ImVec2(pos.x - dim.x, pos.y + dim.y), color, thickness);
        this->GetDrawList()->AddLine(ImVec2(pos.x - dim.x, pos.y + dim.y), ImVec2(pos.x, pos.y + dim.y), color, thickness);
        this->GetDrawList()->AddLine(ImVec2(pos.x, pos.y + dim.y), ImVec2(pos.x, pos.y), color, thickness);
    }
}

void Renderer::DrawFovCircle(float radius, int segments, ImColor color, int thickness)
{
    this->GetDrawList()->AddCircle(ImVec2(this->GetWindowMiddle().x, this->GetWindowMiddle().y), radius, color, segments);
}

void Renderer::DrawCrosshair(ImColor color, int size, int thickness)
{
    this->GetDrawList()->AddLine(this->GetWindowMiddle(), ImVec2(this->GetWindowMiddle().x - size, this->GetWindowMiddle().y), color, thickness);
    this->GetDrawList()->AddLine(this->GetWindowMiddle(), ImVec2(this->GetWindowMiddle().x + size, this->GetWindowMiddle().y), color, thickness);
    this->GetDrawList()->AddLine(this->GetWindowMiddle(), ImVec2(this->GetWindowMiddle().x, this->GetWindowMiddle().y + size), color, thickness);
    this->GetDrawList()->AddLine(this->GetWindowMiddle(), ImVec2(this->GetWindowMiddle().x, this->GetWindowMiddle().y - size), color, thickness);
}

void Renderer::DrawLine(ImVec2 dst, ImVec2 src, ImColor col, int thickness)
{
    if (this->OnScreen(dst) && this->OnScreen(src))
    {
        this->GetDrawList()->AddLine(src, dst, col, thickness);
    }
}

void Renderer::DrawText(ImVec2 pos, ImColor col, const char* text)
{
    this->GetDrawList()->AddText(pos, col, text, 0);
}

void Renderer::DrawHealthBar(ImVec2 pos, ImVec2 dim, ImColor col)
{
    if (this->OnScreen(pos))
    {
        
        this->GetDrawList()->AddLine(pos, ImVec2(pos.x, pos.y - dim.y), col, dim.x);
    }
}


void Renderer::DrawFilledCircle(ImVec2 pos, float radius, float segments, ImColor col)
{
    this->GetDrawList()->AddCircleFilled(pos, radius, col, segments);
}

ImDrawList* Renderer::GetDrawList() {
    return ImGui::GetBackgroundDrawList();
}

bool Renderer::IsFullscreen(HWND windowHandle)
{
    MONITORINFO monitorInfo = { 0 };
    monitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(MonitorFromWindow(windowHandle, MONITOR_DEFAULTTOPRIMARY), &monitorInfo);

    RECT windowRect;
    GetWindowRect(windowHandle, &windowRect);

    return windowRect.left == monitorInfo.rcMonitor.left &&
           windowRect.right == monitorInfo.rcMonitor.right &&
           windowRect.top == monitorInfo.rcMonitor.top &&
           windowRect.bottom == monitorInfo.rcMonitor.bottom;
}

ImVec2 Renderer::GetWindowSize()
{
    RECT rect;
    HWND hwnd = GetActiveWindow();
    if (GetWindowRect(hwnd, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        if (this->IsFullscreen(hwnd))
        {
            return ImVec2(width, height);
        }
        return ImVec2((width - 17), (height - 35));
    }
    return ImVec2(0, 0);
}

ImVec2 Renderer::GetWindowMiddle()
{
    RECT rect;
    HWND hwnd = GetActiveWindow();
    if (GetWindowRect(hwnd, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        if (this->IsFullscreen(hwnd))
        {
            return ImVec2(width / 2, height / 2);
        }
        return ImVec2((width - 17) / 2, (height - 35) / 2);
    }
    return ImVec2(0, 0);
}