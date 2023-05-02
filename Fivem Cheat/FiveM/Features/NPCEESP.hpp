#pragma once
#include "../Includes/Includes.h"
#include "../Includes/Vector.h"
#include "../Includes/BoneHashes.h"
#include "../Includes/Globals.hpp"
#include "../Managers/MathManager.hpp"
#include "../Includes/WeaponHashes.h"

#include <xlocbuf>
#include <locale>
#include <codecvt>
#include <xmmintrin.h>
#define RENDERER Globals::renderer 


void NPCESP() {
	if (Globals::LocalPlayer) {
		if (Globals::MenuOptions::NPCESP) {
			uintptr_t ReplayInterfacePatternFixed = *(uintptr_t*)(Globals::ReplayInterfacePattern + *(int*)(Globals::ReplayInterfacePattern + 0x3) + 0x7);
			uintptr_t PedReplayInterface = *(uintptr_t*)(ReplayInterfacePatternFixed + 0x18);
			int MaxPeds = *(int*)(PedReplayInterface + 0x108);
			Globals::maxpeds = MaxPeds;
			for (int i = 0; i < MaxPeds; i++) {
				uintptr_t PedList = *(uintptr_t*)(PedReplayInterface + 0x100);
                uintptr_t pCPed = *(uintptr_t*)(PedList + (i * 0x10));
                if (!pCPed) continue;

                 if (pCPed == Globals::LocalPlayer) continue;

                CPed* cped = (CPed*)(pCPed);
                
                BYTE EntityType = cped->btEntityType;
                EntityType = EntityType << 11 >> 25;
                float Health = *(float*)(pCPed + 0x280);
                float Armor = *(float*)(pCPed + 0x14B8);
                Vec3 EntPos = *(Vec3*)(pCPed + 0x90);
                Vec3 LocPos = *(Vec3*)(Globals::LocalPlayer + 0x90);

                ImVec2 Ent2DPos = WorldToScreen(EntPos);
                ImVec2 LocPos2D = WorldToScreen(LocPos);

                ImVec2 Head = GetBonePosW2S(pCPed, SKEL_Head);

                double distance = sqrt(pow(LocPos.x - EntPos.x, 2) + pow(LocPos.y - EntPos.y, 2) + pow(LocPos.y - EntPos.y, 2)) * 0.625;

                if (distance <= Globals::NPCESPOptions::espmaxdist) {

                    ImVec2 LeftFoot = GetBonePosW2S(pCPed, SKEL_L_Foot);
                    ImVec2 RightFoot = GetBonePosW2S(pCPed, SKEL_R_Foot);
                    float FootAdv = (LeftFoot.y + RightFoot.y) / 2;
                    float height = fabs(Head.y - FootAdv) * 1.2;
                    float width = height / 2.5;

                    if (Globals::NPCESPOptions::Corner) {
                        RENDERER->DrawCornerBox(ImVec2(Ent2DPos.x + width / 2, Ent2DPos.y + height / 2), ImVec2(width, height), Globals::Colors::NPCESPCorner, 1);
                    }

                    if (Globals::NPCESPOptions::Corner) {
                        RENDERER->DrawCornerBox(ImVec2(Ent2DPos.x + width / 2, Ent2DPos.y + height / 2), ImVec2(width, height), Globals::Colors::NPCESPCorner, 1);
                    }

                    if (Globals::NPCESPOptions::Skeleton) {
                        ImVec2 Back = GetBonePosW2S(pCPed, SKEL_Neck_1);

                        ImVec2 LeftClavicle = GetBonePosW2S(pCPed, SKEL_L_Clavicle);
                        ImVec2 LeftElbow = GetBonePosW2S(pCPed, MH_L_Elbow);
                        ImVec2 LeftUpperArm = GetBonePosW2S(pCPed, SKEL_L_UpperArm);
                        ImVec2 LeftForearm = GetBonePosW2S(pCPed, SKEL_L_Forearm);
                        ImVec2 LeftHand = GetBonePosW2S(pCPed, SKEL_L_Hand);

                        ImVec2 RightClavicle = GetBonePosW2S(pCPed, SKEL_R_Clavicle);
                        ImVec2 RightElbow = GetBonePosW2S(pCPed, MH_R_Elbow);
                        ImVec2 RightUpperArm = GetBonePosW2S(pCPed, SKEL_R_UpperArm);
                        ImVec2 RightForearm = GetBonePosW2S(pCPed, SKEL_R_Forearm);
                        ImVec2 RightHand = GetBonePosW2S(pCPed, SKEL_R_Hand);

                        ImVec2 Pelvis = GetBonePosW2S(pCPed, SKEL_Pelvis);

                        ImVec2 LeftThigh = GetBonePosW2S(pCPed, SKEL_L_Thigh);
                        ImVec2 LeftCalf = GetBonePosW2S(pCPed, SKEL_L_Calf);

                        ImVec2 RightThigh = GetBonePosW2S(pCPed, SKEL_R_Thigh);
                        ImVec2 RightCalf = GetBonePosW2S(pCPed, SKEL_R_Calf);

                        // BACK / SPINE
                        RENDERER->DrawLine(Head, Back, Globals::Colors::NPCESPSkeleton, 1);

                        // LEFT ARM
                        RENDERER->DrawLine(Back, LeftUpperArm, Globals::Colors::NPCESPSkeleton, 1);
                        RENDERER->DrawLine(LeftUpperArm, LeftForearm, Globals::Colors::NPCESPSkeleton, 1);
                        RENDERER->DrawLine(LeftForearm, LeftHand, Globals::Colors::NPCESPSkeleton, 1);

                        // RIGHT ARM
                        RENDERER->DrawLine(Back, RightUpperArm, Globals::Colors::NPCESPSkeleton, 1);
                        RENDERER->DrawLine(RightUpperArm, RightForearm, Globals::Colors::NPCESPSkeleton, 1);
                        RENDERER->DrawLine(RightForearm, RightHand, Globals::Colors::NPCESPSkeleton, 1);

                        // SPINE
                        RENDERER->DrawLine(Back, Pelvis, Globals::Colors::NPCESPSkeleton, 1);

                        // LEFT LEG
                        RENDERER->DrawLine(Pelvis, LeftThigh, Globals::Colors::NPCESPSkeleton, 1);
                        RENDERER->DrawLine(LeftThigh, LeftCalf, Globals::Colors::NPCESPSkeleton, 1);
                        RENDERER->DrawLine(LeftCalf, LeftFoot, Globals::Colors::NPCESPSkeleton, 1);

                        // RIGHT LEG
                        RENDERER->DrawLine(Pelvis, RightThigh, Globals::Colors::NPCESPSkeleton, 1);
                        RENDERER->DrawLine(RightThigh, RightCalf, Globals::Colors::NPCESPSkeleton, 1);
                        RENDERER->DrawLine(RightCalf, RightFoot, Globals::Colors::NPCESPSkeleton, 1);
                    }

                    if (Globals::NPCESPOptions::Health) {

                        float HealthPercentage = height / 75 * (Health - 100);
                        float fixedhealth = Health - 100;
                        if (Globals::NPCESPOptions::HealthBarBasedOnHealth) {
                            ImColor col;
                            if (fixedhealth == 75) {
                                col = ImColor(81, 252, 141, 255);
                            }
                            else if (fixedhealth < 75 && fixedhealth > 50) {
                                col = ImColor(191, 245, 64, 255);
                            }
                            else if (fixedhealth < 50 && fixedhealth > 25) {
                                col = ImColor(221, 245, 64, 255);
                            }
                            else if (fixedhealth < 25 && fixedhealth > 0) {
                                col = ImColor(245, 79, 64, 255);
                            }
                            if (Health > 0) {
                                RENDERER->DrawHealthBar(ImVec2(Ent2DPos.x + (width / 1.87), Ent2DPos.y + height / 2), ImVec2(4, HealthPercentage), col);
                            }
                            RENDERER->DrawBox(ImVec2(Ent2DPos.x + (width / 1.86), Ent2DPos.y - height / 2), ImVec2(4, height), ImColor(40, 41, 40, 255), 1);
                        }
                        else {
                            if (Health > 0) {
                                RENDERER->DrawHealthBar(ImVec2(Ent2DPos.x + (width / 1.87), Ent2DPos.y + height / 2), ImVec2(4, HealthPercentage), Globals::Colors::NPCESPHealthbar);
                            }
                            RENDERER->DrawBox(ImVec2(Ent2DPos.x + (width / 1.86), Ent2DPos.y - height / 2), ImVec2(4, height), ImColor(40, 41, 40, 255), 1);
                        }
                    }
                    if (Globals::NPCESPOptions::DarkBackground) {
                        RENDERER->DrawLine(ImVec2(Ent2DPos.x - width / 2, (Ent2DPos.y + height / 2) + 10), ImVec2(Ent2DPos.x + width / 2, (Ent2DPos.y + height / 2) + 10), ImColor(40, 40, 40, 160), 20);
                    }

                    ImGui::PushFont(rudy18);

                    if (Globals::NPCESPOptions::Name) {
                        std::string namestr = "[ ";
                        namestr += cped->pCPlayerInfo->sName;
                        namestr += " ]";
                        float font_size = 18 * namestr.size() / 2;
                        RENDERER->DrawTextA(ImVec2((Ent2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), (Ent2DPos.y - height / 2) - 18), Globals::Colors::NPCESPDistance, namestr.c_str());
                    }

                    using convert_type = std::codecvt_utf8<wchar_t>;
                    std::wstring_convert<convert_type, wchar_t> converter;
                    if (Globals::NPCESPOptions::Distance) {
                        std::string text;
                        text = "[ " + std::to_string(static_cast<int>(distance)) + "m ]";
                        float font_size = 18 * text.size() / 2;
                        RENDERER->DrawTextA(ImVec2((Ent2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ent2DPos.y + height / 2), Globals::Colors::NPCESPDistance, text.c_str());
                    }
                    /*if (cped->pCWeaponManager) {
                        if (cped->pCWeaponManager->CWeaponCur) {
                            if (Globals::NPCESPOptions::Distance && Globals::NPCESPOptions::Weapon) {
                                std::string text;
                                text = std::to_string(static_cast<int>(distance)) + "m | " + converter.to_bytes(get_weapon_name((DWORD)cped->pCWeaponManager->CWeaponCur->dwNameHash));
                                float font_size = 18 * text.size() / 2;
                                RENDERER->DrawTextA(ImVec2((Ent2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ent2DPos.y + height / 2), Globals::Colors::NPCESPDistance, text.c_str());
                            }
                            else if (Globals::NPCESPOptions::Weapon && !Globals::NPCESPOptions::Distance) {
                                std::string text;
                                text = converter.to_bytes(get_weapon_name((DWORD)cped->pCWeaponManager->CWeaponCur->dwNameHash));
                                float font_size = 18 * text.size() / 2;
                                RENDERER->DrawTextA(ImVec2((Ent2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ent2DPos.y + height / 2), Globals::Colors::NPCESPDistance, text.c_str());
                            }
                            else if (!Globals::NPCESPOptions::Weapon && Globals::NPCESPOptions::Distance) {
                                std::string text = std::to_string(static_cast<int>(distance)) + "m";
                                float font_size = 18 * text.size() / 2;
                                RENDERER->DrawTextA(ImVec2((Ent2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ent2DPos.y + height / 2), Globals::Colors::NPCESPDistance, text.c_str());
                            }
                        }
                    }*/
                    ImGui::PopFont();
                    if (Globals::NPCESPOptions::Armor) {
                        float ArmorPercentage = height / 100 * Armor;
                        RENDERER->DrawHealthBar(ImVec2(Ent2DPos.x - (width / 1.85), Ent2DPos.y + height / 2), ImVec2(4, ArmorPercentage), ImColor(126, 148, 247, 255));
                        RENDERER->DrawBox(ImVec2(Ent2DPos.x - (width / 1.86), Ent2DPos.y - height / 2), ImVec2(4, height), ImColor(40, 41, 40, 255), 1);
                    }

                    if (Globals::NPCESPOptions::Box) {
                        RENDERER->DrawBox(ImVec2(Ent2DPos.x + width / 2, Ent2DPos.y - height / 2), ImVec2(width, height), Globals::Colors::NPCESPBox, 1);
                    }
                }
			}
		}
	}
}