#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Utils/Memory.hpp"
#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Modules.hpp"
#include "../Utils/Weapons.hpp"
#include "../Core/Level.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

struct Triggerbot {
    //Toggles
    bool TriggerbotEnabled = true;
    bool OnADS = true;
    bool HipfireShotguns = false;
    float TriggerbotRange = 200;
    
    //Weapon Toggles
    //Light
    bool P2020 = false;
    bool RE45 = false;
    bool Alternator = false;
    bool R99 = false;
    bool R301 = false;
    bool Spitfire = false;
    bool G7 = false;
    
    //Heavy
    bool Flatline = false;
    bool Hemlock = false;
    bool Repeater = false;
    bool Rampage = false;
    bool CARSMG = false;
    
    //Energy
    bool Havoc = false;
    bool Devotion = false;
    bool LSTAR = false;
    bool TripleTake = false;
    bool Volt = false;
    bool Nemesis = false;
    
    //Shotgun
    bool Mozambique = false;
    bool EVA8 = false;
    bool Peacekeeper = false;
    bool Mastiff = false;
    
    //Snipers
    bool Longbow = false;
    bool ChargeRifle = false;
    bool Sentinel = false; 
    
    //Legendary
    bool Wingman = false;
    bool Prowler = false;
    bool Bocek = false;
    bool Kraber = false;
    bool Knife = false;
    
    std::set<int> WeaponList = {};
       

    XDisplay* X11Display;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;
    Level* Map;

    Triggerbot(XDisplay* X11Display, Level* Map, LocalPlayer* Myself, std::vector<Player*>* GamePlayers) {
        this->X11Display = X11Display;
        this->Map = Map;
        this->Myself = Myself;
        this->Players = GamePlayers;
    }

    void RenderUI() {
		if (ImGui::BeginTabItem("Triggerbot", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		    ImVec2 TabSize;
            TabSize = ImGui::GetWindowSize();
            //Triggerbot
            ImGui::Text("Triggerbot");
            if (ImGui::BeginChild("Triggerbot Tab", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 580), true)) {
                ImGui::Text("Triggerbot");
                ImGui::Checkbox("Enabled", &TriggerbotEnabled);
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                    ImGui::SetTooltip("Will automatically shoot the target\nWill only activate when your crosshair is at target whilst holding down Triggerbot key");
                
                if (TriggerbotEnabled) {
                    ImGui::Separator();  
                    
                    ImGui::Text("Triggerbot Conditions");
                    if (ImGui::CollapsingHeader("Conditions", nullptr)) {
                        ImGui::Checkbox("On ADS Only?", &Modules::Triggerbot::OnADS);
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                            ImGui::SetTooltip("Fire only when ADS");
                        if (Modules::Triggerbot::OnADS) {
                            ImGui::SameLine();
                            ImGui::Checkbox("Always On For Shotguns", &Modules::Triggerbot::HipfireShotguns);
                                if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                                    ImGui::SetTooltip("Overrides The Triggerbot Condition (OnADS?) For Shotguns Only.\nSimple Terms: Other Guns Require ADS, Shotguns Will Not.");
                        }
                    }
                    
                    ImGui::Separator();  
                    
                    ImGui::Text("Triggerbot Settings");
                    if (ImGui::CollapsingHeader("Settings", nullptr)) {
                    ImGui::SliderFloat("Triggerbot Range", &TriggerbotRange, 0, 1000, "%.0f");
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                        ImGui::SetTooltip("Triggerbot's activation range.");
                    }
                        
                    ImGui::Separator();    
                        
                    //Select Weapons
                    ImGui::Text("Weapons");
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
                            ImGui::SameLine();
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
                            ImGui::SameLine();
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
                            ImGui::SameLine();
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
                            ImGui::Checkbox("Bocek Compound Bow", &Bocek);
                            ImGui::SameLine();
                            ImGui::Checkbox("Kraber .50-CAL Sniper", &Kraber);
                            ImGui::SameLine();
                            ImGui::Checkbox("Throwing Knife", &Knife);
                    }
                }

                ImGui::EndChild();
            }
		    ImGui::EndTabItem();
		    UpdateWeaponList();
		}
    }

    bool Save() {
        try {
            Config::Triggerbot::Enabled = TriggerbotEnabled;
            Config::Triggerbot::Range = TriggerbotRange;
            Config::Triggerbot::OnADS = Modules::Triggerbot::OnADS;
            Config::Triggerbot::HipfireShotguns = Modules::Triggerbot::HipfireShotguns;
            
            //Weapons
            //Light
            Config::Triggerbot::P2020 = P2020;
            Config::Triggerbot::RE45 = RE45;
            Config::Triggerbot::Alternator = Alternator;
            Config::Triggerbot::R99 = R99;
            Config::Triggerbot::R301 = R301;
            Config::Triggerbot::Spitfire = Spitfire;
            Config::Triggerbot::G7 = G7;
            //Heavy
            Config::Triggerbot::Flatline = Flatline;
            Config::Triggerbot::Hemlock = Hemlock;
            Config::Triggerbot::Repeater = Repeater;
            Config::Triggerbot::Rampage = Rampage;
            Config::Triggerbot::CARSMG = CARSMG;
            //Energy
            Config::Triggerbot::Havoc = Havoc;
            Config::Triggerbot::Devotion = Devotion;
            Config::Triggerbot::LSTAR = LSTAR;
            Config::Triggerbot::TripleTake = TripleTake;
            Config::Triggerbot::Volt = Volt;
            Config::Triggerbot::Nemesis = Nemesis;
            //Shotguns
            Config::Triggerbot::Mozambique = Mozambique;
            Config::Triggerbot::EVA8 = EVA8;
            Config::Triggerbot::Peacekeeper = Peacekeeper;
            Config::Triggerbot::Mastiff = Mastiff;
            //Snipers
            Config::Triggerbot::Longbow = Longbow;
            Config::Triggerbot::ChargeRifle = ChargeRifle;
            Config::Triggerbot::Sentinel = Sentinel;
            //Legendary
            Config::Triggerbot::Wingman = Wingman;
            Config::Triggerbot::Prowler = Prowler;
            Config::Triggerbot::Bocek = Bocek;
            Config::Triggerbot::Kraber = Kraber;
            Config::Triggerbot::Knife = Knife;
            return true;
        } catch (...) {
            return false;
        }
    }

    void UpdateWeaponList() {
        WeaponList.clear();
        //Light
        if (P2020)
            WeaponList.insert(TriggerbotId::WEAPON_P2020);
        if (RE45)
            WeaponList.insert(TriggerbotId::WEAPON_RE45);
        if (Alternator)
            WeaponList.insert(TriggerbotId::WEAPON_ALTERNATOR);
        if (R99)
            WeaponList.insert(TriggerbotId::WEAPON_R99);
        if (R301)
            WeaponList.insert(TriggerbotId::WEAPON_R301);
        if (Spitfire)
            WeaponList.insert(TriggerbotId::WEAPON_SPITFIRE);
        if (G7)
            WeaponList.insert(TriggerbotId::WEAPON_G7);
        //Heavy
        if (Flatline)
            WeaponList.insert(TriggerbotId::WEAPON_FLATLINE);
        if (Hemlock)
            WeaponList.insert(TriggerbotId::WEAPON_HEMLOCK);
        if (Repeater)
            WeaponList.insert(TriggerbotId::WEAPON_REPEATER);
        if (Rampage)
            WeaponList.insert(TriggerbotId::WEAPON_RAMPAGE);
        if (CARSMG)
            WeaponList.insert(TriggerbotId::WEAPON_CAR);
        //Energy
        if (Havoc)
            WeaponList.insert(TriggerbotId::WEAPON_HAVOC);
        if (Devotion)
            WeaponList.insert(TriggerbotId::WEAPON_DEVOTION);
        if (LSTAR)
            WeaponList.insert(TriggerbotId::WEAPON_LSTAR);
        if (TripleTake)
            WeaponList.insert(TriggerbotId::WEAPON_TRIPLETAKE);
        if (Volt)
            WeaponList.insert(TriggerbotId::WEAPON_VOLT);
        if (Nemesis)
            WeaponList.insert(TriggerbotId::WEAPON_NEMESIS);
        //Shotguns
        if (Mozambique)
            WeaponList.insert(TriggerbotId::WEAPON_MOZAMBIQUE);
        if (EVA8)
            WeaponList.insert(TriggerbotId::WEAPON_EVA8);
        if (Peacekeeper)
            WeaponList.insert(TriggerbotId::WEAPON_PEACEKEEPER);
        if (Mastiff)
            WeaponList.insert(TriggerbotId::WEAPON_MASTIFF);
        //Snipers
        if (Longbow)
            WeaponList.insert(TriggerbotId::WEAPON_LONGBOW);
        if (ChargeRifle)
            WeaponList.insert(TriggerbotId::WEAPON_CHARGE_RIFLE);
        if (Sentinel)
            WeaponList.insert(TriggerbotId::WEAPON_SENTINEL);
	//Legendary
	if (Wingman)
            WeaponList.insert(TriggerbotId::WEAPON_WINGMAN);
        if (Prowler)
            WeaponList.insert(TriggerbotId::WEAPON_PROWLER);
        if (Bocek)
            WeaponList.insert(TriggerbotId::WEAPON_BOCEK);
        if (Kraber)
            WeaponList.insert(TriggerbotId::WEAPON_KRABER);
        if (Knife)
            WeaponList.insert(TriggerbotId::WEAPON_KNIFE);
    }

    void Update() {
    	if(!Map->IsPlayable) return;
        //Triggerbot Start
        //Always on - Will always shoot, ignores keybind
    	if (!Modules::Triggerbot::OnADS) {
        	if (!TriggerbotEnabled) return;
        	if (!Myself->IsCombatReady()) return;

        	if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end()) return;
			for (int i = 0; i < Players->size(); i++) {
		    		Player* player = Players->at(i);
		    		if (!player->IsCombatReady()) continue;
		    		if (!player->IsHostile) continue;
		    		if (!player->IsAimedAt) continue;
		    		if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(TriggerbotRange)) {
		       	        	X11Display->MouseClickLeft();
		       	        	break;
                 		}	
        		}
        }
        
        //Requires ADS
        if (Modules::Triggerbot::OnADS) {
        	if (!TriggerbotEnabled) return;
        	if (!Myself->IsCombatReady()) return;

        	if (WeaponList.find(Myself->WeaponIndex) == WeaponList.end()) return;
        	
        	if (!HipfireShotguns) {
                if (Myself->IsZooming) {
                    for (int i = 0; i < Players->size(); i++) {
                            Player* player = Players->at(i);
                            if (!player->IsCombatReady()) continue;
                            if (!player->IsHostile) continue;
                            if (!player->IsAimedAt) continue;
                            
                            if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(TriggerbotRange)) {
                                    X11Display->MouseClickLeft();
                                    break;
                            }		
                    }
                }
	        }

        	if (Modules::Triggerbot::HipfireShotguns) {
                if (Myself->IsZooming) {
                        for (int i = 0; i < Players->size(); i++) {
                                Player* player = Players->at(i);
                                if (!player->IsCombatReady()) continue;
                                if (!player->IsHostile) continue;
                                if (!player->IsAimedAt) continue;
                                if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(TriggerbotRange)) {
                                        X11Display->MouseClickLeft();
                                        break;
                            }	
                        }
                }

			    if (!Myself->IsZooming) {
				    if (Myself->WeaponIndex == 97 or Myself->WeaponIndex == 88 or Myself->WeaponIndex == 104 or Myself->WeaponIndex == 96) { //Shotgun IDs

					    for (int i = 0; i < Players->size(); i++) {
					    	Player* player = Players->at(i);
					    	if (!player->IsCombatReady()) continue;
					    	if (!player->IsHostile) continue;
					    	if (!player->IsAimedAt) continue;
					    	if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(TriggerbotRange)) {
					       	        X11Display->MouseClickLeft();
					       	        break;
						    }
					    }
				    }
			    }
	       }
        }
     }
};
