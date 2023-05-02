#pragma once
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
#define RENDERER Globals::renderer 

void ObjectESP() {
	if (Globals::LocalPlayer) {
		if (Globals::MenuOptions::objectesp) {
			uintptr_t ReplayInterfacePatternFixed = *(uintptr_t*)(Globals::ReplayInterfacePattern + *(int*)(Globals::ReplayInterfacePattern + 0x3) + 0x7);
			uintptr_t ObjectReplayInterface = *(uintptr_t*)(ReplayInterfacePatternFixed + 0x28);
			int maxpickups = *(int*)(ObjectReplayInterface + 0x160);
			uintptr_t ObjectList = *(uintptr_t*)(ObjectReplayInterface + 0x0158);
			for (int i = 0; i < maxpickups; i++) {
				

				uintptr_t Object = *(uintptr_t*)(ObjectList + (i * 0x10));
				if (!Object) continue;

				uintptr_t ObjectInfo = *(uintptr_t*)(Object + 0x20);
				int32_t WeaponHash = *(int32_t*)(ObjectInfo + 0x18);

				Vec3 vPosition = *(Vec3*)(Object + 0x90);
				ImVec2 vScreenPosition = WorldToScreen(vPosition);
				if (Globals::ObjectESPOptions::Distance) {

					std::string text = std::to_string(WeaponHash);
					float font_size = 18 * text.size() / 2;
					RENDERER->DrawTextA(ImVec2(vScreenPosition), Globals::Colors::ObjectDistance, text.c_str());
				}
			}

		}
	}
}