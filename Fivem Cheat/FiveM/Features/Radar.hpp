#include "../Includes/Includes.h"
#include "../Includes/Vector.h"
#include "../Includes/BoneHashes.h"
#include "../Includes/Globals.hpp"
#include "../Managers/MathManager.hpp"
#include "../Includes/WeaponHashes.h"

#include <xlocbuf>
#include <locale>
#include <codecvt>
#include <xmmintrin.h>
#include <directxmath.h>

#define M_PI           3.14159265358979323846  /* pi */
#define RENDERER Globals::renderer 

ImVec2 WorldToRadar(CGameCameraAngles* pGameCamManager, Vec3 Location, Vec3 localLocation,FLOAT RadarX, FLOAT RadarY, float RadarSize, float RadarZoom)
{
	ImVec2 Coord(0, 0);
	ImVec2 Return(0, 0);
	float rot = acosf(pGameCamManager->pMyCameraManagerAngles->pMyCameraAngles->pMyFPSAngles->ViewAngles2.x) * 180.0f / M_PI;
	if (asinf(pGameCamManager->pMyCameraManagerAngles->pMyCameraAngles->pMyFPSAngles->ViewAngles2.y) * 180.0f / M_PI < 0.0f) rot *= -1.0f;

	ImVec2 forwardVec(0, 0);
	float ForwardDirection = DirectX::XMConvertToRadians(rot);
	forwardVec.x = cos(ForwardDirection);
	forwardVec.y = sin(ForwardDirection);

	FLOAT CosYaw = forwardVec.x;
	FLOAT SinYaw = forwardVec.y;

	FLOAT DeltaX = Location.x - localLocation.x;
	FLOAT DeltaY = Location.y - localLocation.y;

	FLOAT LocationX = (DeltaY * CosYaw - DeltaX * SinYaw) / RadarZoom;
	FLOAT LocationY = (DeltaX * CosYaw + DeltaY * SinYaw) / RadarZoom;

	if (LocationX > RadarSize / 2.0f - 2.5f)
		LocationX = RadarSize / 2.0f - 2.5f;
	else if (LocationX < -(RadarSize / 2.0f - 2.5f))
		LocationX = -(RadarSize / 2.0f - 2.5f);

	if (LocationY > RadarSize / 2.0f - 2.5f)
		LocationY = RadarSize / 2.0f - 2.5f;
	else if (LocationY < -(RadarSize / 2.0f - 2.5f))
		LocationY = -(RadarSize / 2.0f - 2.5f);

	Return.x = -LocationX + RadarX;
	Return.y = -LocationY + RadarY;
	return Return;
}

void Radar()
{
	if (Globals::LocalPlayer)
	{
		if (Globals::MenuOptions::radar) {
			RENDERER->DrawBox(ImVec2(350, 150), ImVec2(300, 300), ImColor(255, 255, 255, 255), 3);
			RENDERER->DrawLine(ImVec2(200, 300), ImVec2(200, 150), ImColor(128, 128, 128, 200), 2);
			CGameCameraAngles* pGameCamManager = (CGameCameraAngles*)(Globals::pGameCamManager_pattern + *(DWORD*)(Globals::pGameCamManager_pattern + 0x3) + 0x7);
			if (Globals::Radar::npc) {
				uintptr_t ReplayInterfacePatternFixed = *(uintptr_t*)(Globals::ReplayInterfacePattern + *(int*)(Globals::ReplayInterfacePattern + 0x3) + 0x7);
				uintptr_t PedReplayInterface = *(uintptr_t*)(ReplayInterfacePatternFixed + 0x18);
				int MaxPeds = *(int*)(PedReplayInterface + 0x108);
				Globals::maxpeds = MaxPeds;
				for (int i = 0; i < MaxPeds; i++) {
					uintptr_t PedList = *(uintptr_t*)(PedReplayInterface + 0x100);
					uintptr_t pCPed = *(uintptr_t*)(PedList + (i * 0x10));
					if (!pCPed) continue;


					CPed* cped = (CPed*)(pCPed);

					Vec3 EntPos = *(Vec3*)(pCPed + 0x90);
					Vec3 LocPos = *(Vec3*)(Globals::LocalPlayer + 0x90);
					if (pCPed == Globals::LocalPlayer) {
						ImVec2 radar = WorldToRadar(pGameCamManager, EntPos, LocPos, 200, 300, Globals::Radar::size, Globals::Radar::zoomfactor);
						RENDERER->DrawFilledCircle(radar, 5, 120, Globals::Colors::LocalPlayerRadarColor);
					}
					else {
						ImVec2 radar = WorldToRadar(pGameCamManager, EntPos, LocPos, 200, 300, Globals::Radar::size, Globals::Radar::zoomfactor);
						RENDERER->DrawFilledCircle(radar, Globals::Radar::dotsizes, 120, Globals::Colors::NPCRadarColor);
					}
				}
			}
			if (Globals::Radar::player) {
				uintptr_t pCNetworkPlayerMgr = *(uintptr_t*)((Globals::PlayerListPattern + *(int*)(Globals::PlayerListPattern + 0x3)) + 0x7);
				if (pCNetworkPlayerMgr) {
					int PlayerCount = *(int*)(pCNetworkPlayerMgr + 0x0178);
					for (int i = 0; i < PlayerCount + 2; i++) {
						uintptr_t pCNetGamePlayer = *(uintptr_t*)(pCNetworkPlayerMgr + 0x178 + (i * 0x8));
						if (!pCNetGamePlayer) continue;
						if (pCNetGamePlayer < 10000) continue;

						uintptr_t pCPlayerInfo = *(uintptr_t*)(pCNetGamePlayer + 0xA8);
						if (!pCPlayerInfo) continue;

						uintptr_t pCPed = *(uintptr_t*)(pCPlayerInfo + 0x01C8);
						if (!pCPed) continue;



						CPed* cped = (CPed*)(pCPed);

						Vec3 EntPos = *(Vec3*)(pCPed + 0x90);
						Vec3 LocPos = *(Vec3*)(Globals::LocalPlayer + 0x90);
						if (pCPed == Globals::LocalPlayer) {
							ImVec2 radar = WorldToRadar(pGameCamManager, EntPos, LocPos, 200, 300, Globals::Radar::size, Globals::Radar::zoomfactor);
							RENDERER->DrawFilledCircle(radar, 5, 120, Globals::Colors::LocalPlayerRadarColor);
						}
						else {
							ImVec2 radar = WorldToRadar(pGameCamManager, EntPos, LocPos, 200, 300, Globals::Radar::size, Globals::Radar::zoomfactor);
							RENDERER->DrawFilledCircle(radar, Globals::Radar::dotsizes, 120, Globals::Colors::PlayerRadarColor);
						}
					}
				}
			}
		}
	}
}