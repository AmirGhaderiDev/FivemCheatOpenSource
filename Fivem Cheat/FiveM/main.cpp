#pragma warning( disable : 4996 )

#include "Includes/Includes.h"
#include "Includes/Globals.hpp"
#include "Includes/Font.hpp"

#include "Features/ESP.hpp"
#include "Features/Aimbot.hpp"
#include "Features/Misc.hpp"
#include "Features/Vehicles.hpp"
#include "Features/Radar.hpp"

#include "Hooks/InputHook.hpp"
#include "Hooks/Hooks.hpp"

#include "Managers/MenuManager.hpp"
#include "Features/NPCEESP.hpp"
#include "Features/ObjectESP.hpp"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
Config_Manager* cfg_manager = new Config_Manager;
HMODULE hModule;
Present oPresent;
ResizeBuffer oResizeBuffers;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
bool init = false;
ImFont* font;
std::vector<std::string> cfgs = cfg_manager->GetConfigs();

namespace Temp
{
    static float Corner[4] = { 1.f, 1.f, 1.3f, 1.f };
    static float Box[4] = { 0.3f, 1.f, 0.3f, 1.f };
    static float Distance[4] = { 0.3f, 1.f, 0.3f, 1.f };
    static float Skeleton[4] = { 1.f, .78f, 0.3f, 1.f };
    static float HealthOverride[4] = { 1.f, .78f, 0.3f, 1.f };
    static float NPCBox[4] = { 0.3f, 1.f, 0.3f, 1.f };
    static float NPCCorner[4] = { 1.f, 1.f, 1.3f, 1.f };
    static float NPCDistance[4] = { 0.3f, 1.f, 0.3f, 1.f };
    static float NPCSkeleton[4] = { 1.f, .78f, 0.3f, 1.f };
    static float NPCHealthOverride[4] = { 1.f, .78f, 0.3f, 1.f };
    static float Crosshair[4] = { 1.f, .78f, 0.3f, 1.f };
    static float AimbotFov[4] = { 1.f, 1.f, 1.f, 1.f };
    static float PrimaryCol[4] = { 1.f, 1.f, 1.f, 1.f };
    static float ObjectDistance[4] = { 1.f, 1.f, 1.f, 1.f };

    static float locradar[4] = { 1.f, 1.f, 1.f, 1.f };
    static float npcradar[4] = { 1.f, 1.f, 1.f, 1.f };
    static float playerradar[4] = { 1.f, 1.f, 1.f, 1.f };
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

    rudy10 = io.Fonts->AddFontFromMemoryTTF(rawData, sizeof(rawData), 10.f);
    rudy14 = io.Fonts->AddFontFromMemoryTTF(rawData, sizeof(rawData), 14.f);
    rudy16 = io.Fonts->AddFontFromMemoryTTF(rawData, sizeof(rawData), 16.f);
    rudy18 = io.Fonts->AddFontFromMemoryTTF(rawData, sizeof(rawData), 18.f);
    rudy22 = io.Fonts->AddFontFromMemoryTTF(rawData, sizeof(rawData), 22.f);
    rudy30 = io.Fonts->AddFontFromMemoryTTF(rawData, sizeof(rawData), 30.f);



    ImGui::SetupStyle();

	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (Menu_Open && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    ImGui_ImplDX11_InvalidateDeviceObjects();
    if (nullptr != mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = nullptr; }

    HRESULT Resized = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    ID3D11Texture2D* pBackBuffer;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
    pBackBuffer->Release();

    return Resized;
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;
        }
        else
        {
            return oPresent(pSwapChain, SyncInterval, Flags);
        }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::GetIO().WantSaveIniSettings = FALSE;

    // Handle Menu Opening and InputHook
    if (GetAsyncKeyState(VK_DELETE) & 1)
    {
        Menu_Open = !Menu_Open;
        ImGui::GetIO().MouseDrawCursor = Menu_Open;
        InputHook::EnableMouseFocus(Menu_Open);
    }

    ImGui::PushFont(rudy14);
    if (Globals::LocalPlayer) {
        // Cheat Loops -----//
        NPCESP();           //
        ESP();              //
        Vehicle();          //
        Aimbot();           //
        Radar();            //
        ObjectESP();        //
        Misc();             //
        //------------------//

    }
    ImGui::PopFont();
    ImGui::PushFont(rudy16);

    if (Menu_Open)
    {
        ImGui::Begin("InfantryCheats.club", &Menu_Open);
        ImGui::Columns(2, "##main", true);
        ImGui::SetColumnOffset(1, ImGui::GetWindowSize().x / 4);
        if (ImGui::Button("ESP", ImVec2(ImGui::GetWindowSize().x / 4, ImGui::GetWindowSize().y / 10)))
        {
            tab = 1;
        }
        if (ImGui::Button("NPC ESP", ImVec2(ImGui::GetWindowSize().x / 4, ImGui::GetWindowSize().y / 10)))
        {
            tab = 9;
        }
        if (ImGui::Button("Aimbot", ImVec2(ImGui::GetWindowSize().x / 4, ImGui::GetWindowSize().y / 10)))
        {
            tab = 2;
        }
        if (ImGui::Button("Weapons", ImVec2(ImGui::GetWindowSize().x / 4, ImGui::GetWindowSize().y / 10)))
        {
            tab = 3;
        }
        if (ImGui::Button("Vehicle", ImVec2(ImGui::GetWindowSize().x / 4, ImGui::GetWindowSize().y / 10)))
        {
            tab = 4;
        }
        if (ImGui::Button("Radar", ImVec2(ImGui::GetWindowSize().x / 4, ImGui::GetWindowSize().y / 10)))
        {
            tab = 5;
        }
        if (ImGui::Button("Misc", ImVec2(ImGui::GetWindowSize().x / 4, ImGui::GetWindowSize().y / 10)))
        {
            tab = 6;
        }
        if (ImGui::Button("Configs", ImVec2(ImGui::GetWindowSize().x / 4, ImGui::GetWindowSize().y / 10)))
        {
            tab = 7;
        }
        if (ImGui::Button("Settings", ImVec2(ImGui::GetWindowSize().x / 4, ImGui::GetWindowSize().y / 10)))
        {
            tab = 8;
        }

        ImGui::NextColumn();

        switch (tab)
        {
        case 1:
            ImGui::PushFont(rudy18);
            ImGui::TextColored(ImColor(247, 197, 59, 255), "Player ESP");
            ImGui::PopFont();
            ImGui::BeginChild("player esp", ImVec2(600, 450), TRUE);
            ImGui::Checkbox("Enable ESP", &Globals::MenuOptions::ESP);

            ImGui::Checkbox("Skeleton", &Globals::ESPOptions::Skeleton);
            ImGui::SameLine();
            ImGui::ColorEdit4("Skeleton Color", Temp::Skeleton, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::ESPSkeleton.Value.x = Temp::Skeleton[0];
            Globals::Colors::ESPSkeleton.Value.y = Temp::Skeleton[1];
            Globals::Colors::ESPSkeleton.Value.z = Temp::Skeleton[2];
            Globals::Colors::ESPSkeleton.Value.w = Temp::Skeleton[3];

            ImGui::Checkbox("Corner ESP", &Globals::ESPOptions::Corner);
            ImGui::SameLine();
            ImGui::ColorEdit4("Corner ESP Color", Temp::Corner, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::ESPCorner.Value.x = Temp::Corner[0];
            Globals::Colors::ESPCorner.Value.y = Temp::Corner[1];
            Globals::Colors::ESPCorner.Value.z = Temp::Corner[2];
            Globals::Colors::ESPCorner.Value.w = Temp::Corner[3];

            ImGui::Checkbox("Box", &Globals::ESPOptions::Box);
            ImGui::SameLine();
            ImGui::ColorEdit4("Box Color", Temp::Box, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::ESPBox.Value.x = Temp::Box[0];
            Globals::Colors::ESPBox.Value.y = Temp::Box[1];
            Globals::Colors::ESPBox.Value.z = Temp::Box[2];
            Globals::Colors::ESPBox.Value.w = Temp::Box[3];

            ImGui::Checkbox("Name", &Globals::ESPOptions::Name);
            ImGui::Checkbox("Health", &Globals::ESPOptions::Health);
            ImGui::SameLine();
            ImGui::ColorEdit4("Health Bar Color", Temp::HealthOverride, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::ESPHealthbar.Value.x = Temp::HealthOverride[0];
            Globals::Colors::ESPHealthbar.Value.y = Temp::HealthOverride[1];
            Globals::Colors::ESPHealthbar.Value.z = Temp::HealthOverride[2];
            Globals::Colors::ESPHealthbar.Value.w = Temp::HealthOverride[3];


            ImGui::Checkbox("Health Based Color", &Globals::ESPOptions::HealthBarBasedOnHealth);
            

            ImGui::Checkbox("Armor", &Globals::ESPOptions::Armor);
            ImGui::Checkbox("Distance", &Globals::ESPOptions::Distance);
            ImGui::SameLine();
            ImGui::ColorEdit4("Distance Color", Temp::Distance, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::ESPDistance.Value.x = Temp::Distance[0];
            Globals::Colors::ESPDistance.Value.y = Temp::Distance[1];
            Globals::Colors::ESPDistance.Value.z = Temp::Distance[2];
            Globals::Colors::ESPDistance.Value.w = Temp::Distance[3];

            ImGui::Checkbox("Weapon Name", &Globals::ESPOptions::Weapon);
            ImGui::Checkbox("Text Background Color", &Globals::ESPOptions::DarkBackground);
            ImGui::SliderInt("ESP Distance", &Globals::ESPOptions::espmaxdist, 1, 2000, "%d m");
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::PushFont(rudy18);
            ImGui::TextColored(ImColor(247, 197, 59, 255), "Object ESP");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::BeginChild("object esp", ImVec2(600, 450), TRUE);

            ImGui::Checkbox("Object ESP", &Globals::MenuOptions::objectesp);

            ImGui::Checkbox("Object Distance", &Globals::ObjectESPOptions::Distance);
            ImGui::SameLine();
            ImGui::ColorEdit4("Distance Color", Temp::ObjectDistance, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::ObjectDistance.Value.x = Temp::ObjectDistance[0];
            Globals::Colors::ObjectDistance.Value.y = Temp::ObjectDistance[1];
            Globals::Colors::ObjectDistance.Value.z = Temp::ObjectDistance[2];
            Globals::Colors::ObjectDistance.Value.w = Temp::ObjectDistance[3];

            ImGui::EndChild();

            

            break;
        case 9:
            ImGui::Checkbox("NPC ESP ", &Globals::MenuOptions::NPCESP);

            ImGui::Checkbox("NPC Skeleton", &Globals::NPCESPOptions::Skeleton);
            ImGui::SameLine();
            ImGui::ColorEdit4("NPC Skeleton Color", Temp::NPCSkeleton, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::NPCESPSkeleton.Value.x = Temp::NPCSkeleton[0];
            Globals::Colors::NPCESPSkeleton.Value.y = Temp::NPCSkeleton[1];
            Globals::Colors::NPCESPSkeleton.Value.z = Temp::NPCSkeleton[2];
            Globals::Colors::NPCESPSkeleton.Value.w = Temp::NPCSkeleton[3];

            ImGui::Checkbox("NPC Corner ESP", &Globals::NPCESPOptions::Corner);
            ImGui::SameLine();
            ImGui::ColorEdit4("NPC Corner ESP Color", Temp::NPCCorner, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::NPCESPCorner.Value.x = Temp::NPCCorner[0];
            Globals::Colors::NPCESPCorner.Value.y = Temp::NPCCorner[1];
            Globals::Colors::NPCESPCorner.Value.z = Temp::NPCCorner[2];
            Globals::Colors::NPCESPCorner.Value.w = Temp::NPCCorner[3];

            ImGui::Checkbox("NPC Box", &Globals::NPCESPOptions::Box);
            ImGui::SameLine();
            ImGui::ColorEdit4("NPC Box Color", Temp::NPCBox, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::NPCESPBox.Value.x = Temp::NPCBox[0];
            Globals::Colors::NPCESPBox.Value.y = Temp::NPCBox[1];
            Globals::Colors::NPCESPBox.Value.z = Temp::NPCBox[2];
            Globals::Colors::NPCESPBox.Value.w = Temp::NPCBox[3];

            ImGui::Checkbox("NPC Name", &Globals::NPCESPOptions::Name);
            ImGui::Checkbox("NPC Health", &Globals::NPCESPOptions::Health);
            ImGui::SameLine();
            ImGui::ColorEdit4("NPC Health Bar Color", Temp::NPCHealthOverride, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::NPCESPHealthbar.Value.x = Temp::NPCHealthOverride[0];
            Globals::Colors::NPCESPHealthbar.Value.y = Temp::NPCHealthOverride[1];
            Globals::Colors::NPCESPHealthbar.Value.z = Temp::NPCHealthOverride[2];
            Globals::Colors::NPCESPHealthbar.Value.w = Temp::NPCHealthOverride[3];

            ImGui::Checkbox("NPC Health Based Color", &Globals::NPCESPOptions::HealthBarBasedOnHealth);

            ImGui::Checkbox("NPC Armor", &Globals::NPCESPOptions::Armor);
            ImGui::Checkbox("NPC Distance", &Globals::NPCESPOptions::Distance);
            ImGui::SameLine();
            ImGui::ColorEdit4("NPC Distance Color", Temp::NPCDistance, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::NPCESPDistance.Value.x = Temp::NPCDistance[0];
            Globals::Colors::NPCESPDistance.Value.y = Temp::NPCDistance[1];
            Globals::Colors::NPCESPDistance.Value.z = Temp::NPCDistance[2];
            Globals::Colors::NPCESPDistance.Value.w = Temp::NPCDistance[3];

            ImGui::Checkbox("NPC Weapon Name", &Globals::NPCESPOptions::Weapon);
            ImGui::Checkbox("NPC Text Background Color", &Globals::NPCESPOptions::DarkBackground);
            ImGui::SliderInt("NPC ESP Distance", &Globals::NPCESPOptions::espmaxdist, 1, 2000, "%d m");
            break;
        case 2:
            ImGui::Checkbox("Enable Aimbot", &Globals::MenuOptions::Aimbot);

            ImGui::Checkbox("Draw FOV Circle", &Globals::AimbotOptions::FovCircle);
            ImGui::SameLine();
            ImGui::ColorEdit4("FOV Color", Temp::AimbotFov, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::AimbotFovColor.Value.x = Temp::AimbotFov[0];
            Globals::Colors::AimbotFovColor.Value.y = Temp::AimbotFov[1];
            Globals::Colors::AimbotFovColor.Value.z = Temp::AimbotFov[2];
            Globals::Colors::AimbotFovColor.Value.w = Temp::AimbotFov[3];
            ImGui::Checkbox("Ignore Dead Peds", &Globals::AimbotOptions::ignoredead);
            if (ImGui::Button("Add friend button")) {
               
            }
            ImGui::Checkbox("Lock on NPC's", &Globals::AimbotOptions::npclockon);
            ImGui::Checkbox("Filled FOV Circle", &Globals::AimbotOptions::FilledFovCircle);
            ImGui::SliderFloat("FOV", &Globals::AimbotOptions::radius, 5.f, 360.f, "%.2f");
            ImGui::Combo("Aim Bone", &Globals::AimbotOptions::aimbotbone, Globals::AimbotOptions::AimbotBones, IM_ARRAYSIZE(Globals::AimbotOptions::AimbotBones));
            ImGui::SliderInt("Smoothing", &Globals::AimbotOptions::smoothing, 1, 100);
            for (int i = 0; i < Globals::AimbotOptions::FriendsList->size(); i++) {
                if (Globals::AimbotOptions::FriendsList->at(i)) {
                    ImGui::Text(std::to_string(Globals::AimbotOptions::FriendsList->at(i)).c_str());
                    ImGui::SameLine();
                    if (ImGui::Button("remove")) {
                        Globals::AimbotOptions::FriendsList->at(i) = 0;
                    }
                }
            }
            break;
        case 3:
            ImGui::Checkbox("##reload", &Globals::MenuOptions::reloadspeedenabled);
            ImGui::SameLine();
            ImGui::SliderFloat("Reload Speed (Client-Sided)", &Globals::MenuOptions::reloadspeed, 0.1, 100, "%.2f");

            ImGui::Checkbox("##spread", &Globals::MenuOptions::NoSpread);
            ImGui::SameLine();
            ImGui::SliderFloat("Spread Amount", &Globals::MenuOptions::spread, 0, 10, "%0.2f");

            ImGui::Checkbox("##recoil", &Globals::MenuOptions::NoRecoil);
            ImGui::SameLine();
            ImGui::SliderFloat("Recoil Amount", &Globals::MenuOptions::recoil, 0, 10, "%0.2f");

            ImGui::Checkbox("##aimingfov", &Globals::FOVOptions::aimfovenabled);
            ImGui::SameLine();
            ImGui::SliderFloat("Aiming FOV", &Globals::FOVOptions::aimfov, 1, 180, "%0.2f");


            ImGui::Checkbox("Crosshair", &Globals::Settings::Crosshair);
            ImGui::SameLine();
            ImGui::ColorEdit4("Crosshair Color", Temp::Crosshair, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::CrosshairColor.Value.x = Temp::Crosshair[0];
            Globals::Colors::CrosshairColor.Value.y = Temp::Crosshair[1];
            Globals::Colors::CrosshairColor.Value.z = Temp::Crosshair[2];
            Globals::Colors::CrosshairColor.Value.w = Temp::Crosshair[3];

            if (Globals::Settings::Crosshair)
            {
                ImGui::SliderInt("Size", &Globals::Settings::CrosshairSize, 1, 50, 0);
            }

            break;
        case 4: 
            ImGui::Text("Vehicle Primary Color (Client-Sided)");
            ImGui::Checkbox("##primarycolor", &Globals::MenuOptions::primcarcolorenabled);
            ImGui::SameLine();
            ImGui::ColorEdit4("Vehicle Color", Temp::PrimaryCol, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::PrimaryVehicleColor.Value.x = Temp::PrimaryCol[0];
            Globals::Colors::PrimaryVehicleColor.Value.y = Temp::PrimaryCol[1];
            Globals::Colors::PrimaryVehicleColor.Value.z = Temp::PrimaryCol[2];
            Globals::Colors::PrimaryVehicleColor.Value.w = Temp::PrimaryCol[3];
            break;
        case 5:
            ImGui::Checkbox("Enable Radar", &Globals::MenuOptions::radar);
            ImGui::SliderFloat("Radar Zoom", &Globals::Radar::zoomfactor, 0, 5, "%0.2f");
            ImGui::SliderFloat("Radar Size", &Globals::Radar::size, 0, 300, "%0.2f");
            ImGui::SliderFloat("Radar Dot Sizes", &Globals::Radar::dotsizes, 0, 10, "%0.2f");
            ImGui::Text("Localplayer color");
            ImGui::ColorEdit4("LocalPlayer radar dot color", Temp::locradar, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::LocalPlayerRadarColor.Value.x = Temp::locradar[0];
            Globals::Colors::LocalPlayerRadarColor.Value.y = Temp::locradar[1];
            Globals::Colors::LocalPlayerRadarColor.Value.z = Temp::locradar[2];
            Globals::Colors::LocalPlayerRadarColor.Value.w = Temp::locradar[3];
            ImGui::Checkbox("NPC's", &Globals::Radar::npc);
            ImGui::SameLine();
            ImGui::ColorEdit4("NPC radar dot color", Temp::npcradar, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::NPCRadarColor.Value.x = Temp::npcradar[0];
            Globals::Colors::NPCRadarColor.Value.y = Temp::npcradar[1];
            Globals::Colors::NPCRadarColor.Value.z = Temp::npcradar[2];
            Globals::Colors::NPCRadarColor.Value.w = Temp::npcradar[3];
            ImGui::Checkbox("Players", &Globals::Radar::player);
            ImGui::SameLine();
            ImGui::ColorEdit4("Players radar dot color", Temp::playerradar, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            Globals::Colors::PlayerRadarColor.Value.x = Temp::playerradar[0];
            Globals::Colors::PlayerRadarColor.Value.y = Temp::playerradar[1];
            Globals::Colors::PlayerRadarColor.Value.z = Temp::playerradar[2];
            Globals::Colors::PlayerRadarColor.Value.w = Temp::playerradar[3];

            break;
        case 6:
            ImGui::Checkbox("##steathwalk", &Globals::MenuOptions::sneakwalkenabled);
            ImGui::SameLine();
            ImGui::SliderFloat("Stealth Walk Speed", &Globals::MenuOptions::sneakwalkspeed, 0.5, 10, "%.2f");

            ImGui::Checkbox("##runspeed", &Globals::MenuOptions::runspeedenabled);
            ImGui::SameLine();
            ImGui::SliderFloat("Run / Walk Speed", &Globals::MenuOptions::runspeed, .5, 10, "%0.2f");
            break;
        case 7:
           
            for (int i = 0; i < cfgs.size(); i++) {
                ImGui::PushFont(rudy18);
                ImGui::Text(cfgs.at(i).c_str());
                ImGui::PopFont();
                ImGui::SameLine();
                if (ImGui::Button("load")) {
                    cfg_manager->Load(cfgs.at(i));
                }
                ImGui::SameLine();
                if (ImGui::Button("save")) {
                    cfg_manager->Save(cfgs.at(i));
                }
            }

            if (ImGui::Button("reload cfg's")) {
                cfgs = cfg_manager->GetConfigs();
            }
            if (ImGui::Button("save cfg")) {
                cfg_manager->Save("default.ini");
            }
            if (ImGui::Button("load default cfg")) {
                cfg_manager->Load("default.ini");
            }
            break;
        case 8:
            if (ImGui::Button("Crash Game"))
            {
                *(int*)(0x4 + 0x3) = 94;
            }
            if (ImGui::Button("Unload"))
            {
                kiero::shutdown();
                FreeLibrary(hModule);
            }
            //ImGui::Text("Name: %s", Net::GetName());
            ImGui::Text("max peds: %d", Globals::maxpeds);
            break;
        }
        ImGui::End();
    }

    ImGui::PopFont();
    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    TCHAR szFileName[MAX_PATH];
    GetModuleFileName(NULL, szFileName, MAX_PATH);
    std::string szFileNameString = szFileName;
    if (szFileNameString.find("FiveM_GameProcess.exe") != std::string::npos)
    {
        Globals::GameProcessName = "FiveM_GameProcess.exe";
    }
    else if (szFileNameString.find("FiveM_GTAProcess.exe") != std::string::npos)
    {
        Globals::GameProcessName = "FiveM_GTAProcess.exe";
    }

	bool init_hook = false;
	do {
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
            kiero::bind(13, (void**)&oResizeBuffers, hkResizeBuffers);
			init_hook = true;
		}
	} while (!init_hook);

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MenuThreads::MemberUpdate, 0, 0, 0);
	return TRUE;
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), lpReserved, 0, 0);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}