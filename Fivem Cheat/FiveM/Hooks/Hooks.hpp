#include "../Managers/FMemoryManager.hpp"
#include "../Includes/Globals.hpp"

namespace GlueHook 
{
	uintptr_t SetNicknamePattern = sigscan("glue.dll", "40 56 48 81 EC ? ? ? ?");
	using SetNick = void(*)(std::string);
	void SetNickname(std::string name) {
		SetNick setNickname = (SetNick)(SetNicknamePattern);
		setNickname(name);
	}
}
