#pragma once
#include <iostream>
#include <vector>
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"

#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/QAngle.hpp"
#include "../Math/Resolver.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Modules.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/InputTypes.hpp"
#include "../Utils/Weapons.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Conversion
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI / 180.f) )

struct RCS {
    bool RCSEnabled = true;
    bool OnADS = true;
    float PitchPower = 3;
    float YawPower = 3;
    
    //Weapon Toggles
    //Light
    bool P2020 = true;
    bool RE45 = true;
    bool Alternator = true;
    bool R99 = true;
    bool R301 = true;
    bool Spitfire = true;
    bool G7 = true;
    
    //Heavy
    bool Flatline = true;
    bool Hemlock = true;
    bool Repeater = true;
    bool Rampage = true;
    bool CARSMG = true;
    
    //Energy
    bool Havoc = true;
    bool Devotion = true;
    bool LSTAR = true;
    bool TripleTake = true;
    bool Volt = true;
    bool Nemesis = true;
    
    //Shotgun
    bool Mozambique = true;
    bool EVA8 = true;
    bool Peacekeeper = true;
    bool Mastiff = true;
    
    //Snipers
    bool Longbow = true;
    bool ChargeRifle = true;
    bool Sentinel = true; 
    
    //Legendary
    bool Wingman = true; //Emotional damage!
    bool Prowler = true;
    bool Kraber = false;
    
    //---------------Advanced---------------//
    bool AdvancedRCS = false;
    float AdvancedPitchPower = 10;
    float AdvancedYawPower = 10;
    
    //Weapons
    //Light
    float P2020Pitch = 10;
    float P2020Yaw = 10;
    float RE45Pitch = 10;
    float RE45Yaw = 10;
    float AlternatorPitch = 10;
    float AlternatorYaw = 10;
    float R99Pitch = 10;
    float R99Yaw = 10;
    float R301Pitch = 10;
    float R301Yaw = 10;
    float SpitfirePitch = 10;
    float SpitfireYaw = 10;
    float G7Pitch = 10;
    float G7Yaw = 10;
    //Heavy
    float FlatlinePitch = 10;
    float FlatlineYaw = 10;
    float HemlockPitch = 10;
    float HemlockYaw = 10;
    float RepeaterPitch = 10;
    float RepeaterYaw = 10;
    float RampagePitch = 10;
    float RampageYaw = 10;
    float CARSMGPitch = 10;
    float CARSMGYaw = 10;
    //Energy
    float HavocPitch = 10;
    float HavocYaw = 10;
    float DevotionPitch = 10;
    float DevotionYaw = 10;
    float LSTARPitch = 10;
    float LSTARYaw = 10;
    float TripleTakePitch = 10;
    float TripleTakeYaw = 10;
    float VoltPitch = 10;
    float VoltYaw = 10;
    float NemesisPitch = 10;
    float NemesisYaw = 10;
    //Shotguns
    float MozambiquePitch = 10;
    float MozambiqueYaw = 10;
    float EVA8Pitch = 10;
    float EVA8Yaw = 10;
    float PeacekeeperPitch = 10;
    float PeacekeeperYaw = 10;
    float MastiffPitch = 10;
    float MastiffYaw = 10;
    //Snipers
    float LongbowPitch = 10;
    float LongbowYaw = 10;
    float ChargeRiflePitch = 10;
    float ChargeRifleYaw = 10;
    float SentinelPitch = 10;
    float SentinelYaw = 10;
    //Legendary
    float WingmanPitch = 10;
    float WingmanYaw = 10;
    float ProwlerPitch = 10;
    float ProwlerYaw = 10;
    float KraberPitch = 10;
    float KraberYaw = 10;
    
    
    XDisplay* X11Display;
    LocalPlayer* Myself;
    Level* Map;
    
    Vector2D previous_weaponPunchAngles;
    QAngle RCSLastPunch;
    
    std::set<int> RCSList = {};

    RCS(XDisplay* X11Display, Level* Map, LocalPlayer* Myself) {
        this->X11Display = X11Display;
        this->Map = Map;
        this->Myself = Myself;
    }

    void RenderUI() {
		if (ImGui::BeginTabItem("RCS", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
			ImVec2 TabSize;
			TabSize = ImGui::GetWindowSize();
			//RCS
			ImGui::Text("RCS - Recoil Control");
			if (ImGui::BeginChild("RCS Tab", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 270), true)) {
				ImGui::Text("RCS Tab");
				ImGui::Checkbox("Enabled", &RCSEnabled);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Toggle the RCS (Recoil Control)\nReduce the intensity of weapon's recoil.");
				
				if (RCSEnabled) {
					ImGui::Separator();    
					
					ImGui::Text("RCS Conditions");
					if (ImGui::CollapsingHeader("Conditions", nullptr)) {
					ImGui::Checkbox("On ADS?", &OnADS);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Toggle when the RCS will take control\nEnabled = Only when aiming.\nDisabled = Always.");
					}    
					
					ImGui::Separator();
					
					ImGui::Text("Intensity Settings");
					if (ImGui::CollapsingHeader("Settings", nullptr)) {
						ImGui::SliderFloat("Pitch", &PitchPower, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Pitch Power");
						ImGui::SliderFloat("Yaw", &YawPower, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Yaw Power");
					}
					
					ImGui::Separator();
					
					//Select Weapons
					ImGui::Text("Toggle Weapons");
					if (ImGui::CollapsingHeader("Light Weapons", nullptr)) {
						ImGui::Checkbox("P2020", &P2020);
						ImGui::SameLine();
						ImGui::Checkbox("RE-45 Auto", &RE45);
						ImGui::SameLine();
						ImGui::Checkbox("Alternator SMG", &Alternator);
						ImGui::SameLine();
						ImGui::Checkbox("R-99 SMG", &R99);
						ImGui::SameLine();
						ImGui::Checkbox("R-301 Carbine", &R301);

						ImGui::Checkbox("M600 Spitfire", &Spitfire);
						ImGui::SameLine();
						ImGui::Checkbox("G7 Scout", &G7);
					}
					
					if (ImGui::CollapsingHeader("Heavy Weapons", nullptr)) {
						ImGui::Checkbox("VK-47 Flatline", &Flatline);
						ImGui::SameLine();
						ImGui::Checkbox("Hemlock Burst AR", &Hemlock);
						ImGui::SameLine();
						ImGui::Checkbox("30-30 Repeater", &Repeater);
						ImGui::SameLine();
						ImGui::Checkbox("Rampage LMG", &Rampage);
						
						ImGui::Checkbox("C.A.R SMG", &CARSMG);
					}
					
					if (ImGui::CollapsingHeader("Energy Weapons", nullptr)) {
						ImGui::Checkbox("Havoc Rifle", &Havoc);
						ImGui::SameLine();
						ImGui::Checkbox("Devotion LMG", &Devotion);
						ImGui::SameLine();
						ImGui::Checkbox("L-Star EMG", &LSTAR);
						ImGui::SameLine();
						ImGui::Checkbox("Triple-Take", &TripleTake);
						ImGui::SameLine();
						ImGui::Checkbox("Volt", &Volt);

						ImGui::Checkbox("Nemesis Burst AR", &Nemesis);
					}

					if (ImGui::CollapsingHeader("Shotguns", nullptr)) {
						ImGui::Checkbox("Mozambique", &Mozambique);
						ImGui::SameLine();
						ImGui::Checkbox("EVA-8 Auto", &EVA8);
						ImGui::SameLine();
						ImGui::Checkbox("Peacekeeper", &Peacekeeper);
						ImGui::SameLine();
						ImGui::Checkbox("Mastiff", &Mastiff);
					}

					if (ImGui::CollapsingHeader("Snipers", nullptr)) {
						ImGui::Checkbox("Longbow DMR", &Longbow);
						ImGui::SameLine();
						ImGui::Checkbox("Charge Rifle", &ChargeRifle);
						ImGui::SameLine();
						ImGui::Checkbox("Sentinel", &Sentinel);
					}
					
					if (ImGui::CollapsingHeader("Legendary Weapons", nullptr)) {
						ImGui::Checkbox("Wingman", &Wingman);
						ImGui::SameLine();
						ImGui::Checkbox("Prowler Burst SMG", &Prowler);
						ImGui::SameLine();
						ImGui::Checkbox("Kraber .50-CAL Sniper", &Kraber);
					}
				}
				ImGui::EndChild();
			}
			
			ImGui::Text("Advanced RCS");
			if (ImGui::BeginChild("RCS Advanced", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 285), true)) {
				ImGui::Text("Advanced RCS Tab");
				ImGui::Checkbox("Enabled Advanced RCS", &AdvancedRCS);
					if (AdvancedRCS) {
						ImGui::Separator();
						ImGui::Text("Weapon Intensity Settings");
						if (ImGui::CollapsingHeader("Light", nullptr)) {
							if (P2020) {
								ImGui::Text("P2020");
								ImGui::SliderFloat("Pitch##AdvancedP2020", &P2020Pitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the P2020.");
								ImGui::SliderFloat("Yaw##AdvancedP2020", &P2020Yaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the P2020.");
							}
							
							if (RE45) {
								ImGui::Text("RE-45 Auto");
								ImGui::SliderFloat("Pitch##AdvancedRE45", &RE45Pitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the RE-45 Auto.");
								ImGui::SliderFloat("Yaw##AdvancedRE45", &RE45Yaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the RE-45 Auto.");
							}
							
							if (Alternator) {
								ImGui::Text("Alternator SMG");
								ImGui::SliderFloat("Pitch##AdvancedAlternator", &AlternatorPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Alternator SMG.");
								ImGui::SliderFloat("Yaw##AdvancedAlternator", &AlternatorYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Alternator SMG.");
							}
							
							if (R99) {
								ImGui::Text("R-99 SMG");
								ImGui::SliderFloat("Pitch##AdvancedR99", &R99Pitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the R-99.");
								ImGui::SliderFloat("Yaw##AdvancedR99", &R99Yaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the R-99.");
							}
							
							if (R301) {
								ImGui::Text("R-301 Carbine");
								ImGui::SliderFloat("Pitch##AdvancedR301", &R301Pitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the R-301 Carbine.");
								ImGui::SliderFloat("Yaw##AdvancedR301", &R301Yaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the R-301 Carbine.");
							}
							
							if (Spitfire) {
								ImGui::Text("M600 Spitfire");
								ImGui::SliderFloat("Pitch##AdvancedSpitfire", &SpitfirePitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the M600 Spitfire.");
								ImGui::SliderFloat("Yaw##AdvancedSpitfire", &SpitfireYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the M600 Spitfire.");
							}
							
							if (G7) {
								ImGui::Text("G7 Scout");
								ImGui::SliderFloat("Pitch##AdvancedG7", &G7Pitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the G7 Scout.");
								ImGui::SliderFloat("Yaw##AdvancedG7", &G7Yaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the G7 Scout.");
							}
						}
						
						if (ImGui::CollapsingHeader("Heavy", nullptr)) {
							if (Flatline) {
								ImGui::Text("VK-47 Flatline");
								ImGui::SliderFloat("Pitch##AdvancedFlatline", &FlatlinePitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the VK-47 Flatline.");
								ImGui::SliderFloat("Yaw##AdvancedFlatline", &FlatlineYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the VK-47 Flatline.");
							}

							
							
							if (Hemlock) {
								ImGui::Text("Hemlock Burst AR");
								ImGui::SliderFloat("Pitch##AdvancedHemlock", &HemlockPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Hemlock Burst AR.");
								ImGui::SliderFloat("Yaw##AdvancedHemlock", &HemlockYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Hemlock Burst AR.");
							}
							
							if (Repeater) {
								ImGui::Text("30-30 Repeater");
								ImGui::SliderFloat("Pitch##AdvancedRepeater", &RepeaterPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the 30-30 Repeater.");
								ImGui::SliderFloat("Yaw##AdvancedRepeater", &RepeaterYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the 30-30 Repeater.");
							}
							
							if (Rampage) {
								ImGui::Text("Rampage LMG");
								ImGui::SliderFloat("Pitch##AdvancedRampage", &RampagePitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Rampage LMG.");
								ImGui::SliderFloat("Yaw##AdvancedRampage", &RampageYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Rampage LMG.");
							}
							
							if (CARSMG) {
								ImGui::Text("C.A.R SMG");
								ImGui::SliderFloat("Pitch##AdvancedCARSMG", &CARSMGPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the C.A.R SMG.");
								ImGui::SliderFloat("Yaw##AdvancedCARSMG", &CARSMGYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the C.A.R SMG.");
							}
						}
						
					if (ImGui::CollapsingHeader("Energy", nullptr)) {
							if (Havoc) {
								ImGui::Text("Havoc");
								ImGui::SliderFloat("Pitch##AdvancedHavoc", &HavocPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Havoc Rifle.");
								ImGui::SliderFloat("Yaw##AdvancedHavoc", &HavocYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Havoc Rifle.");
							}
							
							if (Devotion) {
								ImGui::Text("Devotion LMG");
								ImGui::SliderFloat("Pitch##AdvancedDevotion", &DevotionPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Devotion LMG.");
								ImGui::SliderFloat("Yaw##AdvancedDevotion", &DevotionYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Devotion LMG.");
							}
							
							if (LSTAR) {
								ImGui::Text("L-Star EMG");
								ImGui::SliderFloat("Pitch##AdvancedLSTAR", &LSTARPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the L-Star EMG.");
								ImGui::SliderFloat("Yaw##AdvancedLSTAR", &LSTARYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the L-Star EMG.");
							}
							
							if (TripleTake) {
								ImGui::Text("Triple-Take");
								ImGui::SliderFloat("Pitch##AdvancedTripleTake", &TripleTakePitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Triple-Take.");
								ImGui::SliderFloat("Yaw##AdvancedTripleTake", &TripleTakeYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Triple-Take.");
							}
							
							if (Volt) {
								ImGui::Text("Volt");
								ImGui::SliderFloat("Pitch##AdvancedVolt", &VoltPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Volt.");
								ImGui::SliderFloat("Yaw##AdvancedVolt", &VoltYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Volt.");
							}
							
							if (Nemesis) {
								ImGui::Text("Nemesis Burst AR");
								ImGui::SliderFloat("Pitch##AdvancedNemesis", &NemesisPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Nemesis Burst AR.");
								ImGui::SliderFloat("Yaw##AdvancedNemesis", &NemesisYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Nemesis Burst AR.");
							}
					}
					
					if (ImGui::CollapsingHeader("Shotguns", nullptr)) {
							if (Mozambique) {
								ImGui::Text("Mozambique");
								ImGui::SliderFloat("Pitch##AdvancedMozambique", &MozambiquePitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Mozambique.");
								ImGui::SliderFloat("Yaw##AdvancedMozambique", &MozambiqueYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Mozambique.");
							}
							
							if (Peacekeeper) {
								ImGui::Text("Peacekeeper");
								ImGui::SliderFloat("Pitch##AdvancedPeacekeeper", &PeacekeeperPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Peacekeeper.");
								ImGui::SliderFloat("Yaw##AdvancedPeacekeeper", &PeacekeeperYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Peacekeeper.");
							}
							
							if (Mastiff) {
								ImGui::Text("Mastiff");
								ImGui::SliderFloat("Pitch##AdvancedMastiff", &MastiffPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Mastiff.");
								ImGui::SliderFloat("Yaw##AdvancedMastiff", &MastiffYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Mastiff.");
							}
					}
					
					if (ImGui::CollapsingHeader("Snipers", nullptr)) {
							if (Longbow) {
								ImGui::Text("Longbow DMR");
								ImGui::SliderFloat("Pitch##AdvancedLongbow", &LongbowPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Longbow DMR.");
								ImGui::SliderFloat("Yaw##AdvancedLongbow", &LongbowYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Longbow DMR.");
							}
							
							if (ChargeRifle) {
								ImGui::Text("Charge Rifle");
								ImGui::SliderFloat("Pitch##AdvancedChargeRifle", &ChargeRiflePitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Charge Rifle.");
								ImGui::SliderFloat("Yaw##AdvancedChargeRifle", &ChargeRifleYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Charge Rifle.");
							}
							
							if (Sentinel) {
								ImGui::Text("Sentinel");
								ImGui::SliderFloat("Pitch##AdvancedSentinel", &SentinelPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Sentinel.");
								ImGui::SliderFloat("Yaw##AdvancedSentinel", &SentinelYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Sentinel.");
							}
					}
					
					if (ImGui::CollapsingHeader("Legendary", nullptr)) {
							if (Wingman) {
								ImGui::Text("Wingman");
								ImGui::SliderFloat("Pitch##AdvancedWingman", &WingmanPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Wingman.");
								ImGui::SliderFloat("Yaw##AdvancedWingman", &WingmanYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Wingman.");
							}

							if (EVA8) {
								ImGui::Text("EVA-8 Auto");
								ImGui::SliderFloat("Pitch##AdvancedEVA8", &EVA8Pitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the EVA-8 Auto.");
								ImGui::SliderFloat("Yaw##AdvancedEVA8", &EVA8Yaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the EVA-8 Auto.");
							}
							
							if (Kraber) {
								ImGui::Text("Kraber .50-CAL Sniper");
								ImGui::SliderFloat("Pitch##AdvancedKraber", &KraberPitch, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power for the Kraber .50-CAL Sniper.");
								ImGui::SliderFloat("Yaw##AdvancedKraber", &KraberYaw, 1, 50, "%.1f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power for the Kraber .50-CAL Sniper.");
							}
					}
				}
			ImGui::EndChild();
			}

		    ImGui::EndTabItem();
		    UpdateRCSList();
	    	}
		} //End of render UI

    bool Save() {
        try {
            Config::RCS::RCSEnabled = RCSEnabled;
            Config::RCS::OnADS = OnADS;
            Config::RCS::PitchPower = PitchPower;
            Config::RCS::YawPower = YawPower;
            
            //Weapons
            //Light
            Config::RCS::P2020 = P2020;
            Config::RCS::RE45 = RE45;
            Config::RCS::Alternator = Alternator;
            Config::RCS::R99 = R99;
            Config::RCS::R301 = R301;
            Config::RCS::Spitfire = Spitfire;
            Config::RCS::G7 = G7;
            //Heavy
            Config::RCS::Flatline = Flatline;
            Config::RCS::Hemlock = Hemlock;
            Config::RCS::Repeater = Repeater;
            Config::RCS::Rampage = Rampage;
            Config::RCS::CARSMG = CARSMG;
            //Energy
            Config::RCS::Havoc = Havoc;
            Config::RCS::Devotion = Devotion;
            Config::RCS::LSTAR = LSTAR;
            Config::RCS::TripleTake = TripleTake;
            Config::RCS::Volt = Volt;
            Config::RCS::Nemesis = Nemesis;
            //Shotguns
            Config::RCS::Mozambique = Mozambique;
            Config::RCS::EVA8 = EVA8;
            Config::RCS::Peacekeeper = Peacekeeper;
            Config::RCS::Mastiff = Mastiff;
            //Snipers
            Config::RCS::Longbow = Longbow;
            Config::RCS::ChargeRifle = ChargeRifle;
            Config::RCS::Sentinel = Sentinel;
            //Legendary
            Config::RCS::Wingman = Wingman;
            Config::RCS::Prowler = Prowler;
            Config::RCS::Kraber = Kraber;
            
            //----------Advanced Settings----------//
            Config::RCS::AdvancedRCS = AdvancedRCS;
            //Advanced Weapons
            //Light
            Config::RCS::P2020Pitch = P2020Pitch;
            Config::RCS::P2020Yaw = P2020Yaw;
            Config::RCS::RE45Pitch = RE45Pitch;
            Config::RCS::RE45Yaw = RE45Yaw;
            Config::RCS::AlternatorPitch = AlternatorPitch;
            Config::RCS::AlternatorYaw = AlternatorYaw;
            Config::RCS::R99Pitch = R99Pitch;
            Config::RCS::R99Yaw = R99Yaw;
            Config::RCS::R301Pitch = R301Pitch;
            Config::RCS::R301Yaw = R301Yaw;
            Config::RCS::SpitfirePitch = SpitfirePitch;
            Config::RCS::SpitfireYaw = SpitfireYaw;
            Config::RCS::G7Pitch = G7Pitch;
            Config::RCS::G7Yaw = G7Yaw;
            //Heavy
            Config::RCS::FlatlinePitch = FlatlinePitch;
            Config::RCS::FlatlineYaw = FlatlineYaw;
            Config::RCS::HemlockPitch = HemlockPitch;
            Config::RCS::HemlockYaw = HemlockYaw;
            Config::RCS::RepeaterPitch = RepeaterPitch;
            Config::RCS::RepeaterYaw = RepeaterYaw;
            Config::RCS::RampagePitch = RampagePitch;
            Config::RCS::RampageYaw = RampageYaw;
            Config::RCS::CARSMGPitch = CARSMGPitch;
            Config::RCS::CARSMGYaw = CARSMGYaw;
            //Energy
            Config::RCS::HavocPitch = HavocPitch;
            Config::RCS::HavocYaw = HavocYaw;
            Config::RCS::DevotionPitch = DevotionPitch;
            Config::RCS::DevotionYaw = DevotionYaw;
            Config::RCS::LSTARPitch = LSTARPitch;
            Config::RCS::LSTARYaw = LSTARYaw;
            Config::RCS::TripleTakePitch = TripleTakePitch;
            Config::RCS::TripleTakeYaw = TripleTakeYaw;
            Config::RCS::VoltPitch = VoltPitch;
            Config::RCS::VoltYaw = VoltYaw;
            Config::RCS::NemesisPitch = NemesisPitch;
            Config::RCS::NemesisYaw = NemesisYaw;
            //Shotguns
            Config::RCS::MozambiquePitch = MozambiquePitch;
            Config::RCS::MozambiqueYaw = MozambiqueYaw;
            Config::RCS::EVA8Pitch = EVA8Pitch;
            Config::RCS::EVA8Yaw = EVA8Yaw;
            Config::RCS::PeacekeeperPitch = PeacekeeperPitch;
            Config::RCS::PeacekeeperYaw = PeacekeeperYaw;
            Config::RCS::MastiffPitch = MastiffPitch;
            Config::RCS::MastiffYaw = MastiffYaw;
            //Snipers
            Config::RCS::LongbowPitch = LongbowPitch;
            Config::RCS::LongbowYaw = LongbowYaw;
            Config::RCS::ChargeRiflePitch = ChargeRiflePitch;
            Config::RCS::ChargeRifleYaw = ChargeRifleYaw;
            Config::RCS::SentinelPitch = SentinelPitch;
            Config::RCS::SentinelYaw = SentinelYaw;
            //Legendary
            Config::RCS::WingmanPitch = WingmanPitch;
            Config::RCS::WingmanYaw = WingmanYaw;
            Config::RCS::ProwlerPitch = ProwlerPitch;
            Config::RCS::ProwlerYaw = ProwlerYaw;
            Config::RCS::KraberPitch = KraberPitch;
            Config::RCS::KraberYaw = KraberYaw;
            return true;
        } catch (...) {
            return false;
        }
    }
    
    void UpdateRCSList() {
        RCSList.clear();
        //Light
        if (P2020)
            RCSList.insert(RCSId::WEAPON_P2020);
        if (RE45)
            RCSList.insert(RCSId::WEAPON_RE45);
        if (Alternator)
            RCSList.insert(RCSId::WEAPON_ALTERNATOR);
        if (R99)
            RCSList.insert(RCSId::WEAPON_R99);
        if (R301)
            RCSList.insert(RCSId::WEAPON_R301);
        if (Spitfire)
            RCSList.insert(RCSId::WEAPON_SPITFIRE);
        if (G7)
            RCSList.insert(RCSId::WEAPON_G7);
        //Heavy
        if (Flatline)
            RCSList.insert(RCSId::WEAPON_FLATLINE);
        if (Hemlock)
            RCSList.insert(RCSId::WEAPON_HEMLOCK);
        if (Repeater)
            RCSList.insert(RCSId::WEAPON_REPEATER);
        if (Rampage)
            RCSList.insert(RCSId::WEAPON_RAMPAGE);
        if (CARSMG)
            RCSList.insert(RCSId::WEAPON_CAR);
        //Energy
        if (Havoc)
            RCSList.insert(RCSId::WEAPON_HAVOC);
        if (Devotion)
            RCSList.insert(RCSId::WEAPON_DEVOTION);
        if (LSTAR)
            RCSList.insert(RCSId::WEAPON_LSTAR);
        if (TripleTake)
            RCSList.insert(RCSId::WEAPON_TRIPLETAKE);
        if (Volt)
            RCSList.insert(RCSId::WEAPON_VOLT);
        if (Nemesis)
            RCSList.insert(RCSId::WEAPON_NEMESIS);
        //Shotguns
        if (Mozambique)
            RCSList.insert(RCSId::WEAPON_MOZAMBIQUE);
        if (EVA8)
            RCSList.insert(RCSId::WEAPON_EVA8);
        if (Peacekeeper)
            RCSList.insert(RCSId::WEAPON_PEACEKEEPER);
        if (Mastiff)
            RCSList.insert(RCSId::WEAPON_MASTIFF);
        //Snipers
        if (Longbow)
            RCSList.insert(RCSId::WEAPON_LONGBOW);
        if (ChargeRifle)
            RCSList.insert(RCSId::WEAPON_CHARGE_RIFLE);
        if (Sentinel)
            RCSList.insert(RCSId::WEAPON_SENTINEL);
	//Legendary
	if (Wingman)
            RCSList.insert(RCSId::WEAPON_WINGMAN);
        if (Prowler)
            RCSList.insert(RCSId::WEAPON_PROWLER);
        if (Kraber)
            RCSList.insert(RCSId::WEAPON_KRABER);
    }
    
    void Update() {
    	if(!Map->IsPlayable) return;
        //Advanced Settings
    	if (AdvancedRCS) { //IDs from Utils/Weapons.hpp, may need updating after game update
    		int weaponHeld = Myself->WeaponIndex;
    		//Light Weapons
    		if (weaponHeld == 106) { //P2020
    			RCS::AdvancedPitchPower = RCS::P2020Pitch;
    			RCS::AdvancedYawPower = RCS::P2020Yaw;
    		}
    		if (weaponHeld == 81) { //RE-45
    			RCS::AdvancedPitchPower = RCS::RE45Pitch;
    			RCS::AdvancedYawPower = RCS::RE45Yaw;
    		}
    		if (weaponHeld == 80) { //Alternator
    			RCS::AdvancedPitchPower = RCS::AlternatorPitch;
    			RCS::AdvancedYawPower = RCS::AlternatorYaw;
    		}
    		if (weaponHeld == 105) { //R-99
    			RCS::AdvancedPitchPower = RCS::R99Pitch;
    			RCS::AdvancedYawPower = RCS::R99Yaw;
    		}
    		if (weaponHeld == 0) { //R-301
    			RCS::AdvancedPitchPower = RCS::R301Pitch;
    			RCS::AdvancedYawPower = RCS::R301Yaw;
    		}
    		if (weaponHeld == 107) { //Spitfire
    			RCS::AdvancedPitchPower = RCS::SpitfirePitch;
    			RCS::AdvancedYawPower = RCS::SpitfireYaw;
    		}
    		if (weaponHeld == 90) { //G7
    			RCS::AdvancedPitchPower = RCS::G7Pitch;
    			RCS::AdvancedYawPower = RCS::G7Yaw;
    		}
    		//Heavy Weapons
    		if (weaponHeld == 113) { //CARSMG
    			RCS::AdvancedPitchPower = RCS::CARSMGPitch;
    			RCS::AdvancedYawPower = RCS::CARSMGYaw;
    		}
    		if (weaponHeld == 21) { //Rampage
    			RCS::AdvancedPitchPower = RCS::RampagePitch;
    			RCS::AdvancedYawPower = RCS::RampageYaw;
    		}
    		if (weaponHeld == 112) { //Repeater
    			RCS::AdvancedPitchPower = RCS::RepeaterPitch;
    			RCS::AdvancedYawPower = RCS::RepeaterYaw;
    		}
    		if (weaponHeld == 91) { //Hemlock
    			RCS::AdvancedPitchPower = RCS::HemlockPitch;
    			RCS::AdvancedYawPower = RCS::HemlockYaw;
    		}
    		if (weaponHeld == 89) { //Flatline
    			RCS::AdvancedPitchPower = RCS::FlatlinePitch;
    			RCS::AdvancedYawPower = RCS::FlatlineYaw;
    		}
    		//Energy Weapons
    		if (weaponHeld == 114) { //Nemesis
    			RCS::AdvancedPitchPower = RCS::NemesisPitch;
    			RCS::AdvancedYawPower = RCS::NemesisYaw;
    		}
    		if (weaponHeld == 111) { //Volt
    			RCS::AdvancedPitchPower = RCS::VoltPitch;
    			RCS::AdvancedYawPower = RCS::VoltYaw;
    		}
    		if (weaponHeld == 108) { //TripleTake
    			RCS::AdvancedPitchPower = RCS::TripleTakePitch;
    			RCS::AdvancedYawPower = RCS::TripleTakeYaw;
    		}
    		if (weaponHeld == 94) { //LSTAR
    			RCS::AdvancedPitchPower = RCS::LSTARPitch;
    			RCS::AdvancedYawPower = RCS::LSTARYaw;
    		}
    		if (weaponHeld == 84) { //Devotion
    			RCS::AdvancedPitchPower = RCS::DevotionPitch;
    			RCS::AdvancedYawPower = RCS::DevotionYaw;
    		}
    		if (weaponHeld == 86) { //Havoc
    			RCS::AdvancedPitchPower = RCS::HavocPitch;
    			RCS::AdvancedYawPower = RCS::HavocYaw;
    		}
    		//Shotguns
    		if (weaponHeld == 97) { //Mozambique
    			RCS::AdvancedPitchPower = RCS::MozambiquePitch;
    			RCS::AdvancedYawPower = RCS::MozambiqueYaw;
    		}
    		if (weaponHeld == 88) { //EVA8
    			RCS::AdvancedPitchPower = RCS::EVA8Pitch;
    			RCS::AdvancedYawPower = RCS::EVA8Yaw;
    		}
    		if (weaponHeld == 104) { //Peacekeeper
    			RCS::AdvancedPitchPower = RCS::PeacekeeperPitch;
    			RCS::AdvancedYawPower = RCS::PeacekeeperYaw;
    		}
    		if (weaponHeld == 96) { //Mastiff
    			RCS::AdvancedPitchPower = RCS::MastiffPitch;
    			RCS::AdvancedYawPower = RCS::MastiffYaw;
    		}
    		//Snipers
    		if (weaponHeld == 1) { //Sentinel
    			RCS::AdvancedPitchPower = RCS::SentinelPitch;
    			RCS::AdvancedYawPower = RCS::SentinelYaw;
    		}
    		if (weaponHeld == 83) { //ChargeRifle
    			RCS::AdvancedPitchPower = RCS::ChargeRiflePitch;
    			RCS::AdvancedYawPower = RCS::ChargeRifleYaw;
    		}
    		if (weaponHeld == 85) { //Longbow
    			RCS::AdvancedPitchPower = RCS::LongbowPitch;
    			RCS::AdvancedYawPower = RCS::LongbowYaw;
    		}
    		//Legendary Weapons
    		if (weaponHeld == 109) { //Wingman
    			RCS::AdvancedPitchPower = RCS::WingmanPitch;
    			RCS::AdvancedYawPower = RCS::WingmanYaw;
    		}
    		if (weaponHeld == 102) { //Prowler
    			RCS::AdvancedPitchPower = RCS::ProwlerPitch;
    			RCS::AdvancedYawPower = RCS::ProwlerYaw;
    		}
    		if (weaponHeld == 93) { //Kraber
    			RCS::AdvancedPitchPower = RCS::KraberPitch;
    			RCS::AdvancedYawPower = RCS::KraberYaw;
    		}
    	}
    	
    	if (AdvancedRCS) {
	    	if (OnADS) {
			if (!RCS::RCSEnabled)return;
			if (!Myself->IsCombatReady()) return;
			if (!Myself->IsZooming) return;
			if (!Myself->IsInAttack) return;
			if (RCSList.find(Myself->WeaponIndex) == RCSList.end()) return;
			Vector2D punchAnglesDiff = Myself->PunchAnglesDifferent;
			if (punchAnglesDiff.IsZeroVector()) return;
			int pitch = (punchAnglesDiff.x > 0)
			    ? roundHalfEven(punchAnglesDiff.x * RCS::AdvancedPitchPower)
			    : 0;
			int yaw = roundHalfEven(-punchAnglesDiff.y * RCS::AdvancedYawPower);
			X11Display->MoveMouse(pitch, yaw);
		}
		
	    	if (!OnADS) {
			if (!RCS::RCSEnabled)return;
			if (!Myself->IsCombatReady()) return;
			if (!Myself->IsInAttack) return;
			if (RCSList.find(Myself->WeaponIndex) == RCSList.end()) return;
			Vector2D punchAnglesDiff = Myself->PunchAnglesDifferent;
			if (punchAnglesDiff.IsZeroVector()) return;
			int pitch = (punchAnglesDiff.x > 0)
			    ? roundHalfEven(punchAnglesDiff.x * RCS::AdvancedPitchPower)
			    : 0;
			int yaw = roundHalfEven(-punchAnglesDiff.y * RCS::AdvancedYawPower);
			X11Display->MoveMouse(pitch, yaw);
		}
	}
	
    	if (!AdvancedRCS) {
	    	if (OnADS) {
			if (!RCS::RCSEnabled)return;
			if (!Myself->IsCombatReady()) return;
			if (!Myself->IsZooming) return;
			if (!Myself->IsInAttack) return;
			if (RCSList.find(Myself->WeaponIndex) == RCSList.end()) return;
			Vector2D punchAnglesDiff = Myself->PunchAnglesDifferent;
			if (punchAnglesDiff.IsZeroVector()) return;
			int pitch = (punchAnglesDiff.x > 0)
			    ? roundHalfEven(punchAnglesDiff.x * RCS::PitchPower)
			    : 0;
			int yaw = roundHalfEven(-punchAnglesDiff.y * RCS::YawPower);
			X11Display->MoveMouse(pitch, yaw);
		}
		
	    	if (!OnADS) {
			if (!RCS::RCSEnabled)return;
			if (!Myself->IsCombatReady()) return;
			if (!Myself->IsInAttack) return;
			if (RCSList.find(Myself->WeaponIndex) == RCSList.end()) return;
			Vector2D punchAnglesDiff = Myself->PunchAnglesDifferent;
			if (punchAnglesDiff.IsZeroVector()) return;
			int pitch = (punchAnglesDiff.x > 0)
			    ? roundHalfEven(punchAnglesDiff.x * RCS::PitchPower)
			    : 0;
			int yaw = roundHalfEven(-punchAnglesDiff.y * RCS::YawPower);
			X11Display->MoveMouse(pitch, yaw);
		}
	}
    } //Update()

    int roundHalfEven(float x) {
        return (x >= 0.0)
            ? static_cast<int>(std::round(x))
            : static_cast<int>(std::round(-x)) * -1;
    }

};
