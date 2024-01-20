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
    
    XDisplay* X11Display;
    LocalPlayer* Myself;
    
    Vector2D previous_weaponPunchAngles;
    QAngle RCSLastPunch;
    
    std::set<int> RCSList = {};

    RCS(XDisplay* X11Display, LocalPlayer* Myself) {
        this->X11Display = X11Display;
        this->Myself = Myself;
    }

    void RenderUI() {
    	if (Config::Menu::Layout == 0) {
		if (ImGui::BeginTabItem("RCS", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		    ImGui::Text("RCS - Recoil Control");
		    ImGui::Checkbox("Enabled", &RCSEnabled);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Toggle the RCS (Recoil Control)\nReduce the intensity of weapon's recoil.");
		        
		    ImGui::Separator();
		    
	   	    ImGui::Text("RCS Conditions");
	   	    ImGui::Checkbox("On ADS?", &OnADS);
	   	    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Toggle when the RCS will take control\nEnabled = Only when aiming.\nDisabled = Always.");
		     
		    ImGui::Separator();
		    
	   	    ImGui::Text("RCS Intensity");  
		    ImGui::SliderFloat("Pitch", &PitchPower, 1, 50, "%.1f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Pitch Power");
		    ImGui::SliderFloat("Yaw", &YawPower, 1, 50, "%.1f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Yaw Power");
		            
		    //Select Weapons
		    ImGui::Text("Weapons");
		    	ImGui::Text("Light");
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
				    
			ImGui::Text("Heavy");
			ImGui::Checkbox("VK-47 Flatline", &Flatline);
			ImGui::SameLine();
			ImGui::Checkbox("Hemlock Burst AR", &Hemlock);
			ImGui::SameLine();
			ImGui::Checkbox("30-30 Repeater", &Repeater);
			ImGui::SameLine();
			ImGui::Checkbox("Rampage LMG", &Rampage);
			ImGui::Checkbox("C.A.R SMG", &CARSMG);
				    
			ImGui::Text("Energy");
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

			ImGui::Text("Shotguns");
			ImGui::Checkbox("Mozambique", &Mozambique);
			ImGui::SameLine();
			ImGui::Checkbox("EVA-8 Auto", &EVA8);
			ImGui::SameLine();
			ImGui::Checkbox("Peacekeeper", &Peacekeeper);
			ImGui::SameLine();
			ImGui::Checkbox("Mastiff", &Mastiff);

			ImGui::Text("Snipers");
			ImGui::Checkbox("Longbow DMR", &Longbow);
			ImGui::SameLine();
			ImGui::Checkbox("Charge Rifle", &ChargeRifle);
			ImGui::SameLine();
			ImGui::Checkbox("Sentinel", &Sentinel);
				    
			ImGui::Text("Legendary");
			ImGui::Checkbox("Wingman", &Wingman);
			ImGui::SameLine();
			ImGui::Checkbox("Prowler Burst SMG", &Prowler);
			ImGui::SameLine();
			ImGui::Checkbox("Kraber .50-CAL Sniper", &Kraber);
		    
		    ImGui::EndTabItem();
		    UpdateRCSList();
	    }
	}
    
    	if (Config::Menu::Layout == 1) {
		if (ImGui::BeginTabItem("RCS", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		    ImGui::Text("RCS - Recoil Control");
		    ImGui::Checkbox("Enabled", &RCSEnabled);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Toggle the RCS (Recoil Control)\nReduce the intensity of weapon's recoil.");
		        
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
		    
		    ImGui::EndTabItem();
		    UpdateRCSList();
	    	}
    	}
    }

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

    int roundHalfEven(float x) {
        return (x >= 0.0)
            ? static_cast<int>(std::round(x))
            : static_cast<int>(std::round(-x)) * -1;
    }

};
