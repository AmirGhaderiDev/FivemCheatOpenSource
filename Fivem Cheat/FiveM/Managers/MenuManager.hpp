#pragma once

#include <Windows.h>
#include <psapi.h>
#include "../Includes/Globals.hpp"
#include "../Includes/Vector.h"
#include "../Renderer/Renderer.h"

#pragma comment(lib, "psapi.lib")

namespace MenuThreads
{
    DWORD_PTR GetProcessBaseAddress(DWORD processID)
    {
        DWORD_PTR baseAddress = 0;
        HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
        HMODULE* moduleArray;
        LPBYTE moduleArrayBytes;
        DWORD bytesRequired;
        if (processHandle)
        {
            if (K32EnumProcessModules(processHandle, NULL, 0, &bytesRequired))
            {
                if (bytesRequired)
                {
                    moduleArrayBytes = (LPBYTE)LocalAlloc(LPTR, bytesRequired);
                    if (moduleArrayBytes)
                    {
                        unsigned int moduleCount;
                        moduleCount = bytesRequired / sizeof(HMODULE);
                        moduleArray = (HMODULE*)moduleArrayBytes;
                        if (EnumProcessModules(processHandle, moduleArray, bytesRequired, &bytesRequired))
                        {
                            baseAddress = (DWORD_PTR)moduleArray[0];
                        }
                        LocalFree(moduleArrayBytes);
                    }
                }
            }
            CloseHandle(processHandle);
        }
        return baseAddress;
    }

    void MemberUpdate()
    {
        while (true)
        {
            Globals::BaseAddress = GetProcessBaseAddress(GetCurrentProcessId());
            Globals::WorldPointer = *(uintptr_t*)(Globals::BaseAddress + 0x247F840);
            if (Globals::WorldPointer)
            {
                Globals::LocalPlayer = *(uintptr_t*)(Globals::WorldPointer + 0x8);
            }
            Sleep(1000);
        }
    }
}