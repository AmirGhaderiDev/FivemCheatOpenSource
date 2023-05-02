#include "../Includes/Globals.hpp"

void Vehicle()
{
	if (Globals::LocalPlayer)
	{
		if (Globals::MenuOptions::primcarcolorenabled)
		{
			CPed* localplayer = (CPed*)(Globals::LocalPlayer);
			if (localplayer->isInVehicle())
			{
				localplayer->pCVehicleLast->CVehicleColorOptions->CVehicleColor->SetColorPrimary((BYTE)Globals::Colors::PrimaryVehicleColor.Value.x * 255, (BYTE)Globals::Colors::PrimaryVehicleColor.Value.y * 255, (BYTE)Globals::Colors::PrimaryVehicleColor.Value.z * 255, (BYTE)Globals::Colors::PrimaryVehicleColor.Value.w * 255);
			}
		}
	}
}