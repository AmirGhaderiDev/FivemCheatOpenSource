#include "LL.h"

bool LL::Inject()
{
	std::string dllname = "InfantryCheats - FiveM.dll";
	DWORD pid = 0;
	
	while (!pid)
	{
		pid = this->helper->GetPid("FiveM_GTAProcess.exe");
		std::cout << "Waiting for fivem\n";
		system("cls");
	}
	Sleep(1000);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

	if (hProcess == INVALID_HANDLE_VALUE) {
		std::cout << "Shit booboo handle is invalid pepesad:(\n";
		return 0;
	}

	LPVOID loadLibrary = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

	if (!loadLibrary) {
		std::cout << "Shit booboo loadLibrary is invalid pepesad:(\n";
		return 0;
	}

	LPVOID AllocatedMemory = VirtualAllocEx(hProcess, 0, dllname.length(), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!AllocatedMemory) {
		std::cout << "Shit booboo failed to alloc mem (GET MORE RAM RETARD) pepesad:(\n";
		return 0;
	}

	if (!WriteProcessMemory(hProcess, AllocatedMemory, dllname.c_str(), dllname.length(), 0)) {
		std::cout << "Shit booboo failed to wpm pepesad:(\n";
		return 0;
	}

	HANDLE RemoteThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)loadLibrary, AllocatedMemory, 0, 0);
	if (RemoteThread == INVALID_HANDLE_VALUE) {
		std::cout << "Shit booboo RemoteThread handle is invalid pepesad:(\n";
		return 0;
	}


	CloseHandle(hProcess);
	CloseHandle(RemoteThread);

	std::cout << "Successo!!! presso deleto !! pepehappy\n";
	return 1;
}
