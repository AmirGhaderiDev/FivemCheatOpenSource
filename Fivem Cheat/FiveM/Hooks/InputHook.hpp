#pragma once

#include "../Managers/FMemoryManager.hpp"

namespace InputHook 
{
	uintptr_t Pattern = sigscan("conhost-v2.dll", "88 0D ? ? ? ? 80 F1 01 ");
	using Focus = void(*)(bool);
	void EnableMouseFocus(bool mode) {
		Focus setmousefocus = (Focus)(Pattern);
		setmousefocus(mode);
	}
}