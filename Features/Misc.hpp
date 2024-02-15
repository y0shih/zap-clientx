#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <atomic>
#include <vector>
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/Level.hpp"

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

struct Misc {
    bool TeamGamemode = true;
    bool SkinChanger = false;
    bool AutoGrapple = false;
    bool QuickTurn = false;
    InputKeyType QuickTurnKey = InputKeyType::KEYBOARD_K;
    int QuickTurnHotkey = static_cast<int>(QuickTurnKey);
    int QuickTurnAngle = 180;
	bool SuperGlide = true;

    //Weapon IDs
    //Light
    int SkinP2020 = 1;
    int SkinRE45 = 1;
    int SkinALTERNATOR = 1;
    int SkinR99 = 1;
    int SkinR301 = 1;
    int SkinSPITFIRE = 1;
    int SkinG7 = 1;
    
    //Heavy
    int SkinFLATLINE = 1;
    int SkinHEMLOCK = 1;
    int SkinREPEATER = 1;
    int SkinRAMPAGE = 1;
    int SkinCAR = 1;
    
    //Energy
    int SkinHAVOC = 1;
    int SkinDEVOTION = 1;
    int SkinLSTAR = 1;
    int SkinTRIPLETAKE = 1;
    int SkinVOLT = 1;
    int SkinNEMESIS = 1;
    
    //Shotgun
    int SkinMOZAMBIQUE = 1;
    int SkinEVA8 = 1;
    int SkinPEACEKEEPER = 1;
    int SkinMASTIFF = 1;
    
    //Snipers
    int SkinLONGBOW = 1;
    int SkinCHARGE_RIFLE = 1;
    int SkinSENTINEL = 1; 
    
    //Legendary
    int SkinWINGMAN = 1;
    int SkinPROWLER = 1;
    int SkinBOCEK = 1;
    int SkinKRABER = 1;

    XDisplay* X11Display;
    Level* Map;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;

    Misc(XDisplay* X11Display, Level* Map, LocalPlayer* Myself, std::vector<Player*>* GamePlayers) {
        this->X11Display = X11Display;
        this->Map = Map;
        this->Myself = Myself;
        this->Players = GamePlayers;
    }

    void RenderUI() {
        if (ImGui::BeginTabItem("Misc", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
			ImVec2 TabSize;
			TabSize = ImGui::GetWindowSize();

			ImGui::Text("Movement");
			if (ImGui::BeginChild("Movement", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 270), true, ImGuiWindowFlags_NoScrollbar)) {
				ImGui::Text("Movement Tab");
				ImGui::Checkbox("SuperGlide", &SuperGlide);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Hold spacebar whilst climbing over a wall/object to gain extra speed.");
				ImGui::EndChild();
			}

			ImGui::Text("Skin Changer");
			if (ImGui::BeginChild("Skin Changer", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 285), true)) {
				ImGui::Text("Skin Changer Tab");
				ImGui::Checkbox("Skin Changer", &SkinChanger);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Change's weapon skins ONLY.\nMay be glitchy at first.\nNot all skins are avaliable.");

				//Select Weapons
				ImGui::Text("Weapons");
				if (ImGui::CollapsingHeader("Light", nullptr)) {
					ImGui::SliderInt("P2020", &SkinP2020, 0, 10);
					ImGui::SliderInt("RE-45 Auto", &SkinRE45, 0, 16);
					ImGui::SliderInt("Alternator SMG", &SkinALTERNATOR, 0, 16);
					ImGui::SliderInt("R-99 SMG", &SkinR99, 0, 16);
					ImGui::SliderInt("R-301 Carbine", &SkinR301, 0, 18);
					ImGui::SliderInt("M600 Spitfire", &SkinSPITFIRE, 0, 16);
					ImGui::SliderInt("G7 Scout", &SkinG7, 0, 21);
				}
				
				if (ImGui::CollapsingHeader("Heavy", nullptr)) {
					ImGui::SliderInt("VK-47 Flatline", &SkinFLATLINE, 0, 20);
					ImGui::SliderInt("Hemlock Burst AR", &SkinHEMLOCK, 0, 18);
					ImGui::SliderInt("30-30 Repeater", &SkinREPEATER, 0, 11);
					ImGui::SliderInt("Rampage LMG", &SkinRAMPAGE, 0, 11);
					ImGui::SliderInt("C.A.R SMG", &SkinCAR, 0, 11);
				}
				
				if (ImGui::CollapsingHeader("Energy", nullptr)) {
					ImGui::SliderInt("Havoc Rifle", &SkinHAVOC, 0, 14);
					ImGui::SliderInt("Devotion LMG", &SkinDEVOTION, 0, 11);
					ImGui::SliderInt("L-Star EMG", &SkinLSTAR, 0, 11);
					ImGui::SliderInt("Triple-Take", &SkinTRIPLETAKE, 0, 11);
					ImGui::SliderInt("Volt", &SkinVOLT, 0, 14);
					ImGui::SliderInt("Nemesis Burst AR", &SkinNEMESIS, 0, 9);
				}
				
				if (ImGui::CollapsingHeader("Shotguns", nullptr)) {
					ImGui::SliderInt("Mozambique", &SkinMOZAMBIQUE, 0, 11);
					ImGui::SliderInt("EVA-8 Auto", &SkinEVA8, 0, 11);
					ImGui::SliderInt("Peacekeeper", &SkinPEACEKEEPER, 0, 16);
					ImGui::SliderInt("Mastiff", &SkinMASTIFF, 0, 11);
				}
				
				if (ImGui::CollapsingHeader("Snipers", nullptr)) {
					ImGui::SliderInt("Longbow DMR", &SkinLONGBOW, 0, 11);
					ImGui::SliderInt("Charge Rifle", &SkinCHARGE_RIFLE, 0, 11);
					ImGui::SliderInt("Sentinel", &SkinSENTINEL, 0, 10);
				}
				
				if (ImGui::CollapsingHeader("Legendary", nullptr)) {
					ImGui::SliderInt("Wingman", &SkinWINGMAN, 0, 11);
					ImGui::SliderInt("Prowler Burst SMG", &SkinPROWLER, 0, 11);
					ImGui::SliderInt("Bocek Compound Bow", &SkinBOCEK, 0, 11);
					ImGui::SliderInt("Kraber .50-CAL Sniper", &SkinKRABER, 0, 11);
				}
				ImGui::EndChild();
			}
            
            ImGui::EndTabItem();
        }
    }

    bool Save() {
        try {
        Config::Misc::SkinChanger = SkinChanger;
	    //Weapon IDs
	    //Light
	     Config::Misc::SkinP2020 = SkinP2020;
	     Config::Misc::SkinRE45 = SkinRE45;
	     Config::Misc::SkinALTERNATOR = SkinALTERNATOR;
	     Config::Misc::SkinR99 = SkinR99;
	     Config::Misc::SkinR301 = SkinR301;
	     Config::Misc::SkinSPITFIRE = SkinSPITFIRE;
	     Config::Misc::SkinG7 = SkinG7;
	    
	    //Heavy
	     Config::Misc::SkinFLATLINE = SkinFLATLINE;
	     Config::Misc::SkinHEMLOCK = SkinHEMLOCK;
	     Config::Misc::SkinREPEATER = SkinREPEATER;
	     Config::Misc::SkinRAMPAGE = SkinRAMPAGE;
	     Config::Misc::SkinCAR = SkinCAR;
	    
	    //Energy
	     Config::Misc::SkinHAVOC = SkinHAVOC;
	     Config::Misc::SkinDEVOTION = SkinDEVOTION;
	     Config::Misc::SkinLSTAR = SkinLSTAR;
	     Config::Misc::SkinTRIPLETAKE = SkinTRIPLETAKE;
	     Config::Misc::SkinVOLT = SkinVOLT;
	     Config::Misc::SkinNEMESIS = SkinNEMESIS;
	    
	    //Shotgun
	     Config::Misc::SkinMOZAMBIQUE = SkinMOZAMBIQUE;
	     Config::Misc::SkinEVA8 = SkinEVA8;
	     Config::Misc::SkinPEACEKEEPER = SkinPEACEKEEPER;
	     Config::Misc::SkinMASTIFF = SkinMASTIFF;
	    
	    //Snipers
	     Config::Misc::SkinLONGBOW = SkinLONGBOW;
	     Config::Misc::SkinCHARGE_RIFLE = SkinCHARGE_RIFLE;
	     Config::Misc::SkinSENTINEL = SkinSENTINEL; 
	    
	    //Legendary
	     Config::Misc::SkinWINGMAN = SkinWINGMAN;
	     Config::Misc::SkinPROWLER = SkinPROWLER;
	     Config::Misc::SkinBOCEK = SkinBOCEK;
	     Config::Misc::SkinKRABER = SkinKRABER;
            return true;
        } catch (...) {
            return false;
        }
    }

    void Update() {
    	if (SkinChanger) {
		if(!Map->IsPlayable) return;
		if(Myself->IsDead) return;
		long wephandle = Memory::Read<long>(Myself->BasePointer + OFF_WEAPON_HANDLE);
		wephandle &= 0xffff;
		long wep_entity = Myself->WeaponEntity;
		std::map<int, std::vector<int>> weaponSkinMap;
		//Light ammo weapons
		weaponSkinMap[SkinChangerID::WEAPON_P2020] = { SkinP2020 };
		weaponSkinMap[SkinChangerID::WEAPON_RE45] = { SkinRE45 };
		weaponSkinMap[SkinChangerID::WEAPON_ALTERNATOR] = { SkinALTERNATOR };
		weaponSkinMap[SkinChangerID::WEAPON_R99] = { SkinR99 }; 
		weaponSkinMap[SkinChangerID::WEAPON_R301] = { SkinR301 };    
		weaponSkinMap[SkinChangerID::WEAPON_SPITFIRE] = { SkinSPITFIRE }; 
		weaponSkinMap[SkinChangerID::WEAPON_G7] = { SkinG7 };
		//Heavy ammo weapons
		weaponSkinMap[SkinChangerID::WEAPON_CAR] = { SkinCAR }; 
		weaponSkinMap[SkinChangerID::WEAPON_RAMPAGE] = { SkinRAMPAGE };  
		weaponSkinMap[SkinChangerID::WEAPON_REPEATER] = { SkinREPEATER };
		weaponSkinMap[SkinChangerID::WEAPON_HEMLOCK] = { SkinHEMLOCK }; 
		weaponSkinMap[SkinChangerID::WEAPON_FLATLINE] = { SkinFLATLINE }; 
		//Energy ammo weapons
		weaponSkinMap[SkinChangerID::WEAPON_NEMESIS] = { SkinNEMESIS };  
		weaponSkinMap[SkinChangerID::WEAPON_VOLT] = { SkinVOLT }; 
		weaponSkinMap[SkinChangerID::WEAPON_TRIPLETAKE] = { SkinTRIPLETAKE }; 
		weaponSkinMap[SkinChangerID::WEAPON_LSTAR] = { SkinLSTAR }; 
		weaponSkinMap[SkinChangerID::WEAPON_DEVOTION] = { SkinDEVOTION }; 
		weaponSkinMap[SkinChangerID::WEAPON_HAVOC] = { SkinHAVOC }; 
		//Sniper ammo weapons
		weaponSkinMap[SkinChangerID::WEAPON_SENTINEL] = { SkinSENTINEL };
		weaponSkinMap[SkinChangerID::WEAPON_CHARGE_RIFLE] = { SkinCHARGE_RIFLE };
		weaponSkinMap[SkinChangerID::WEAPON_LONGBOW] = { SkinLONGBOW };    
		//Shotgun ammo weapons
		weaponSkinMap[SkinChangerID::WEAPON_MOZAMBIQUE] = { SkinMOZAMBIQUE }; 
		weaponSkinMap[SkinChangerID::WEAPON_EVA8] = { SkinEVA8 }; 
		weaponSkinMap[SkinChangerID::WEAPON_PEACEKEEPER] = { SkinPEACEKEEPER }; 
		weaponSkinMap[SkinChangerID::WEAPON_MASTIFF] = { SkinMASTIFF }; 
		//Legendary ammo weapons
		weaponSkinMap[SkinChangerID::WEAPON_WINGMAN] = { SkinWINGMAN }; 
		weaponSkinMap[SkinChangerID::WEAPON_PROWLER] = { SkinPROWLER };
		weaponSkinMap[SkinChangerID::WEAPON_BOCEK] = { SkinBOCEK };
		weaponSkinMap[SkinChangerID::WEAPON_KRABER] = { SkinKRABER };

		if (SkinChanger){
		    int waponIndex = Memory::Read<int>(wep_entity + OFF_WEAPON_INDEX);
		    if (weaponSkinMap.count(waponIndex) == 0) return;
		    int skinID = weaponSkinMap[waponIndex][0];
		    //printf("Weapon: %s Activated Skin ID: %d \n", WeaponName(waponIndex).c_str(), skinID);  
		    Memory::Write<int>(wep_entity + OFF_SKIN, skinID);
		}
    	    }
    	
    	if (AutoGrapple) {
		/*Memory::Write<int>(Myself->BasePointer + OFF_IN_JUMP + 0x8, 4);
 
		auto Gn = Memory::Read<int>(Myself->BasePointer + OFF_GRAPPLE + OFF_GRAPPLE_ATTACHED);
		if (Gn == 1) {
			Memory::Write<int>(Myself->BasePointer + OFF_IN_JUMP + 0x8, 5);
		}*/
		bool isGrppleActived = Memory::Read<bool>(Myself->BasePointer + OFF_GRAPPLE_ACTIVE);
		if (isGrppleActived) {
			int n = Memory::Read<int>(Myself->BasePointer + OFF_GRAPPLE + OFF_GRAPPLE_ATTACHED);
 
			std::cout << n << std::endl;
 
			if (n == 1) {
				Memory::Write<int>(Myself->BasePointer + OFF_IN_JUMP + 0x08, 5);
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				Memory::Write<int>(Myself->BasePointer + OFF_IN_JUMP + 0x08, 4);
			}
		}
    	}
    } //End of update
    	
    	/*if (QuickTurn) {
  		FloatVector2D localYawtoClamp = Myself->viewAngles;
		localYawtoClamp.clamp();
		float localYaw = localYawtoClamp.y;
		// quickTurn
		if(InputManager::isKeyDown(static_cast<InputKeyType>(21))) {
		        Myself->setYaw((localYaw + QuickTurnAngle));
		        std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
    	}*/
};
