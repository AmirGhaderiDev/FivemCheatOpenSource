#pragma once
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

#include "Helper.h"

class LL
{
public:
	Helper* helper = new Helper;
	bool Inject();
};

