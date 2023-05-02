#include "../Managers/FMemoryManager.hpp"


namespace NetHook {
	uintptr_t GetPingPattern = sigscan("net.dll", "48 8B 49 10 48 85 C9 74 07 48 8B 01 48 FF 60 58");
	using GetPing = __int64(*)();
	GetPing getPing = (GetPing)(GetPingPattern);
	Globals::ping = getPing();
}