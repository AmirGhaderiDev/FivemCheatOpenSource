#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include <string>
#include <dxgi.h>
#include "Hooks/kiero/kiero.h"
#include "Hooks/kiero/imgui/imgui.h"
#include "Hooks/kiero/imgui/imgui_impl_win32.h"
#include "Hooks/kiero/imgui/imgui_impl_dx11.h"
#include "Hooks/kiero/imgui/imgui_style.h"

bool Menu_Open = false;
int tab = 0;
ImFont* rudy10;
ImFont* rudy14;
ImFont* rudy16;
ImFont* rudy18;
ImFont* rudy22;
ImFont* rudy30;
int seatbelt_button_counter = 0;

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* ResizeBuffer) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;