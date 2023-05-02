#pragma once

#include "../Includes/Globals.hpp"

uintptr_t weaponinfo, weaponmanager, playerinfo;

void Misc()
{
	if (Globals::AimbotOptions::FovCircle)
	{
		if (!Globals::AimbotOptions::FilledFovCircle)
		{
			Globals::renderer->DrawFovCircle(Globals::AimbotOptions::radius, 128, Globals::Colors::AimbotFovColor, 2);
		}
		else
		{
			Globals::renderer->DrawFilledCircle(Globals::renderer->GetWindowMiddle(), Globals::AimbotOptions::radius, 128, Globals::Colors::AimbotFovColor);
		}
	}

	if (Globals::Settings::Crosshair)
	{
		Globals::renderer->DrawCrosshair(Globals::Colors::CrosshairColor, Globals::Settings::CrosshairSize, 2);
	}

	if (Globals::LocalPlayer)
	{
		playerinfo = *(uintptr_t*)(Globals::LocalPlayer + 0x10B8);
		weaponmanager = *(uintptr_t*)(Globals::LocalPlayer + 0x10C8);
		if (weaponmanager)
		{
			weaponinfo = *(uintptr_t*)(weaponmanager + 0x20);
		}
		if (weaponinfo)
		{
			if (Globals::MenuOptions::reloadspeedenabled)
			{
				*(float*)(weaponinfo + 0x12C) = Globals::MenuOptions::reloadspeed;
			}
			if (Globals::MenuOptions::NoRecoil)
			{
				*(float*)(weaponinfo + 0x2E8) = Globals::MenuOptions::recoil;
			}
			if (Globals::MenuOptions::NoSpread)
			{
				*(float*)(weaponinfo + 0x74) = Globals::MenuOptions::spread;
			}
			//if (Globals::FOVOptions::aimfovenabled) {
			//	uintptr_t someweaponthingy = *(uintptr_t*)(weaponinfo + 0x20);
			//	if (someweaponthingy) {
			//		*(float*)(someweaponthingy + 0x2F0) = Globals::FOVOptions::aimfov;
			//	}
			//}
		}
		if (playerinfo)
		{
			if (Globals::MenuOptions::runspeedenabled)
			{
				*(float*)(playerinfo + 0x14C) = Globals::MenuOptions::runspeed;
			}
			if (Globals::MenuOptions::sneakwalkenabled)
			{
				*(float*)(playerinfo + 0x168) = Globals::MenuOptions::sneakwalkspeed;
			}
			if (Globals::FOVOptions::aimfovenabled) {
				
				
			}
		}
	}
}