#pragma once

#include "imgui.h"

namespace ImGui
{
	inline void SetupStyle()
	{
		auto& style = ImGui::GetStyle();

		style.FrameBorderSize = 0;
		style.WindowRounding = 0;
		style.FrameRounding = 3;
		style.TabRounding = 0;
		style.ScrollbarRounding = 0;
		style.FramePadding = ImVec2(8, 6);
		style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
		style.Colors[ImGuiCol_TitleBg] = ImColor(34, 35, 52, 255);			 // The top bar color
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(247, 197, 59, 255);	 // When you press in the imgui menu
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(15, 15, 15, 50);	 // When the title is collapsed
		style.Colors[ImGuiCol_WindowBg] = ImColor(27, 27, 38, 255);			 // Window Background
		style.Colors[ImGuiCol_Button] = ImColor(18, 19, 26, 255);			 // button color
		style.Colors[ImGuiCol_ButtonActive] = ImColor(18, 19, 26, 255);	         // button color when pressed
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(33, 34, 43, 255);		     // button when hovered
		style.Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);		 // check mark color
		style.Colors[ImGuiCol_FrameBg] = ImColor(34, 35, 52, 255);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(36, 37, 36, 255);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(45, 46, 64, 102);
		style.Colors[ImGuiCol_Header] = ImColor(24, 24, 24, 255);			 // for collapsing headers , etc
		style.Colors[ImGuiCol_HeaderActive] = ImColor(54, 53, 55);
		style.Colors[ImGuiCol_HeaderHovered] = ImColor(24, 24, 24, 100);
		style.Colors[ImGuiCol_ResizeGrip] = ImColor(51, 49, 50, 255);		 // the resize grip thing bottom right
		style.Colors[ImGuiCol_ResizeGripActive] = ImColor(54, 53, 55);		 // when you hold it / active
		style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(51, 49, 50, 255); // when you hover over it
		style.Colors[ImGuiCol_SliderGrab] = ImColor(247, 197, 59, 255);
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(250, 207, 90, 255);
		style.Colors[ImGuiCol_Border] = ImColor(54, 54, 54);
		style.Colors[ImGuiCol_Separator] = ImColor(54, 54, 54);
		style.Colors[ImGuiCol_SeparatorActive] = ImColor(54, 54, 54);
		style.Colors[ImGuiCol_SeparatorHovered] = ImColor(54, 54, 54);

		// tabs 
		style.Colors[ImGuiCol_Tab] = ImColor(51, 51, 64, 220);
		style.Colors[ImGuiCol_TabHovered] = ImColor(59, 59, 66, 204);
		style.Colors[ImGuiCol_TabActive] = ImColor(63, 63, 77, 255);
	}
};