#pragma once

#include "../Includes/BoneHashes.h"
#include "../Includes/Globals.hpp"
#include "../Managers/MathManager.hpp"

uintptr_t oGetTPSCamera_pattern = sigscan("FiveM_GTAProcess.exe", "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D3 48 8B F8 E8 ? ? ? ? 8B 8B ? ? ? ?");
typedef CPlayerAngles* (__fastcall* GetTPSCamera_t)(__int64 pECX, __int64 pEDX);
GetTPSCamera_t oGetTPSCamera;


CPlayerAngles* GetCurrentCamera(CGameCameraAngles* pGameCam)
{
    if (!oGetTPSCamera_pattern) return 0;
    CPlayerAngles* pPlayerAngles = NULL;
    if (pGameCam)
    {
        oGetTPSCamera = (GetTPSCamera_t)(oGetTPSCamera_pattern + *(int*)(oGetTPSCamera_pattern + 8) + 12);
        uintptr_t secondtpscamthing = *(DWORD*)(oGetTPSCamera_pattern + *(int*)(oGetTPSCamera_pattern + 3) + 7);
        __int64 qwEDX = pGameCam->pMyCameraManagerAngles->pMyCameraAngles->pTPSCamEDX;
        if (!qwEDX) return 0;
        pPlayerAngles = oGetTPSCamera(secondtpscamthing, (DWORD)qwEDX);
        if (pPlayerAngles)
        {
            pPlayerAngles = (CPlayerAngles*)(DWORD(pPlayerAngles) + 0x390);
        }
        else
        {
            pPlayerAngles = pGameCam->pMyCameraManagerAngles->pMyCameraAngles->pMyFPSAngles;
        }
    }
    return pPlayerAngles;
}


uintptr_t GetClosestPlayer() 
{
    uintptr_t ClosestPlayer = 0;
    float closestdist = FLT_MAX;
    float dist;
    if (!Globals::AimbotOptions::npclockon) {
        if (!Globals::PlayerListPattern) return 0;
        uintptr_t pCNetworkPlayerMgr = *(uintptr_t*)((Globals::PlayerListPattern + *(int*)(Globals::PlayerListPattern + 0x3)) + 0x7);
        if (pCNetworkPlayerMgr)
        {
            int PlayerCount = *(int*)(pCNetworkPlayerMgr + 0x0178);
            for (int i = 0; i < PlayerCount + 2; i++)
            {
                uintptr_t pCNetGamePlayer = *(uintptr_t*)(pCNetworkPlayerMgr + 0x178 + (i * 0x8));
                if (!pCNetGamePlayer) continue;
                if (pCNetGamePlayer < 10000) continue;

                uintptr_t pCPlayerInfo = *(uintptr_t*)(pCNetGamePlayer + 0xA8);
                if (!pCPlayerInfo) continue;

                uintptr_t pCPed = *(uintptr_t*)(pCPlayerInfo + 0x01C8);
                if (!pCPed) continue;

                if (pCPed == Globals::LocalPlayer) continue;

                Vec3 EntPos = *(Vec3*)(pCPed + 0x90);

                float Health = *(float*)(pCPed + 0x280);
                if (Globals::AimbotOptions::ignoredead) {
                    if (Health < 0 || Health == 0) continue;
                }
                ImVec2 Head = GetBonePosW2S(pCPed, SKEL_Head);
                ImVec2 middle = Globals::renderer->GetWindowMiddle();
                dist = pythag(middle, Head);

                if (dist < closestdist)
                {
                    closestdist = dist;
                    ClosestPlayer = pCPed;
                }
            }
        }
    }
    else {
        uintptr_t ReplayInterfacePatternFixed = *(uintptr_t*)(Globals::ReplayInterfacePattern + *(int*)(Globals::ReplayInterfacePattern + 0x3) + 0x7);
        uintptr_t PedReplayInterface = *(uintptr_t*)(ReplayInterfacePatternFixed + 0x18);
        if (PedReplayInterface) {
            int MaxPeds = *(int*)(PedReplayInterface + 0x108);
            for (int i = 0; i < MaxPeds; i++) {
                uintptr_t PedList = *(uintptr_t*)(PedReplayInterface + 0x100);
                uintptr_t pCPed = *(uintptr_t*)(PedList + (i * 0x10));
                if (!pCPed) continue;

                if (pCPed == Globals::LocalPlayer) continue;

                CPed* cped = (CPed*)(pCPed);
                if (!cped) continue;
                Vec3 EntPos = *(Vec3*)(pCPed + 0x90);


                float Health = *(float*)(pCPed + 0x280);
                if (Globals::AimbotOptions::ignoredead) {
                    if (Health < 0 || Health == 0) continue;
                }
                ImVec2 Ent2DPos = WorldToScreen(EntPos);

                ImVec2 Head = GetBonePosW2S(pCPed, SKEL_Head);
                ImVec2 middle = Globals::renderer->GetWindowMiddle();
                dist = pythag(middle, Head);

                if (dist < closestdist)
                {
                    closestdist = dist;
                    ClosestPlayer = pCPed;
                }
            }
        }
    }
    return ClosestPlayer;
}

void Aimbot()
{
    if (Globals::MenuOptions::Aimbot)
    {
        if (Globals::LocalPlayer)
        {
            CGameCameraAngles* pGameCamManager = (CGameCameraAngles*)(Globals::pGameCamManager_pattern + *(DWORD*)(Globals::pGameCamManager_pattern + 0x3) + 0x7);
            uintptr_t pCPed = GetClosestPlayer();
            if (!pCPed) return;
            ImVec2 Head = GetBonePosW2S(pCPed, SKEL_Head);
            ImVec2 middle = Globals::renderer->GetWindowMiddle();
            float dist = pythag(middle, Head);
            if (dist <= Globals::AimbotOptions::radius)
            {

                if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
                {
                    CPlayerAngles* PlayerAngles = GetCurrentCamera(pGameCamManager);
                    if (!PlayerAngles) return;
                    switch (Globals::AimbotOptions::aimbotbone)
                    {
                    case 0:
                        SetAngle(GetBonePos(pCPed, SKEL_Head), PlayerAngles);
                        break;
                    case 1:
                        SetAngle(GetBonePos(pCPed, SKEL_Spine3), PlayerAngles);
                        break;
                    case 2:
                        SetAngle(GetBonePos(pCPed, SKEL_L_Calf), PlayerAngles);
                        break;
                    case 3:
                        SetAngle(GetBonePos(pCPed, SKEL_R_Calf), PlayerAngles);
                        break;
                    case 4:
                        SetAngle(GetBonePos(pCPed, SKEL_R_UpperArm), PlayerAngles);
                        break;
                    case 5:
                        SetAngle(GetBonePos(pCPed, SKEL_L_UpperArm), PlayerAngles);
                        break;
                    }
                }
            }
        }
    }
}