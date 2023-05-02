#pragma once
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

class Helper
{
public:
	DWORD GetPid(std::string name);
};

