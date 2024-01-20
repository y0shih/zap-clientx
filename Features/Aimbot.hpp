#pragma once
#include <iostream>
#include <vector>
#include "../Core/Player.hpp"
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

struct Aimbot {
    bool AimbotEnabled = true;
    
    bool OnFire = true;
    bool OnADS = true;
    
    bool PredictMovement = true;
    bool PredictBulletDrop = true;
    float FinalDistance = 0;
    float Speed = 20;
    float Smooth = 0.9;
    int Delay = 10;
    float FOV = 10;
    float ZoomScale = 3.0;
    float MinDistance = 1;
    float HipfireDistance = 60;
    float ZoomDistance = 160;
    
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
    bool Bocek = true;
    bool Kraber = true;
    bool Knife = true;

    XDisplay* X11Display;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;

    Player* CurrentTarget = nullptr;
    bool TargetSelected = true;
    QAngle RCSLastPunch;
    std::chrono::milliseconds LastAimTime;
    
    std::set<int> AimList = {};

    Aimbot(XDisplay* X11Display, LocalPlayer* Myself, std::vector<Player*>* GamePlayers) {
        this->X11Display = X11Display;
        this->Myself = Myself;
        this->Players = GamePlayers;
    }

    void RenderUI() {
    	if (Config::Menu::Layout == 0) {
		if (ImGui::BeginTabItem("Aim", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		    ImGui::Text("Aimbot");
		    ImGui::Checkbox("Enabled", &AimbotEnabled);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Toggle the Aimbot");
		        
		    ImGui::Separator();
		    
		    //Select Hitbox
		    ImGui::Text("Hitbox");
		    	const char* HitboxTypes[] = {"Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip"};
		    	int HitboxTypeIndex = static_cast<int>(Modules::Aimbot::Hitbox);
		    	ImGui::Combo("Hitbox Type", &HitboxTypeIndex, HitboxTypes, IM_ARRAYSIZE(HitboxTypes));
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Which bone the aimbot will aim at.");
		    	Modules::Aimbot::Hitbox = static_cast<HitboxType>(HitboxTypeIndex);
		    
		    ImGui::Separator();
	   	    
	   	    ImGui::Text("Aim Conditions");
	   	    ImGui::Checkbox("On Fire?", &OnFire);
	   	    ImGui::SameLine();
	   	    ImGui::Checkbox("On ADS?", &OnADS);
	   	    
		    ImGui::Separator();
		    
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
			ImGui::Checkbox("Bocek Compound Bow", &Bocek);
			ImGui::Checkbox("Kraber .50-CAL Sniper", &Kraber);
			ImGui::SameLine();
			ImGui::Checkbox("Throwing Knife", &Knife);
		    
		    ImGui::Separator();
		    
		    //Smoothness Settings
		    ImGui::Text("Smoothness");
		    	ImGui::SliderFloat("Speed", &Speed, 1, 100, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Speed of the Aim-Assist\nHigher = Faster");

		    	ImGui::SliderFloat("Smooth", &Smooth, 0, 0.99, "%.3f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Smoothness for the Aim-Assist\nHigher = Smoother");
		        	
		    	ImGui::SliderInt("Delay", &Delay, 1, 50, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Delay time for the aimbot smoothing.\n");
		    
		    ImGui::Separator();

		    //Prediction Settings
		    ImGui::Text("Prediction");
		    	ImGui::Checkbox("Predict Movement", &PredictMovement);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Predict target's movement");
		    	ImGui::SameLine();
		    	ImGui::Checkbox("Predict Bullet Drop", &PredictBulletDrop);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Predict weapon's bullet drop");
		    
		    ImGui::Separator();

		    //FOV Settings
		    ImGui::Text("FOV");
		    	ImGui::SliderFloat("FOV", &FOV, 1, 90, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Field of View");
		    	ImGui::SliderFloat("Zoom Scale", &ZoomScale, 0, 5, "%.1f");
		    
		    ImGui::Separator();

		    //Distance Settings
		    ImGui::Text("Distance");
		    	ImGui::SliderFloat("Hip-fire Distance", &HipfireDistance, 1, 500, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Minimum distance for Aim-Assist to work");
		    	ImGui::SliderFloat("Zoom Distance", &ZoomDistance, 1, 500, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Maximum distance for Aim-Assist to work");
		    
		    ImGui::EndTabItem();
		    UpdateAimList();
	    }
	}
    
    	if (Config::Menu::Layout == 1) {
		if (ImGui::BeginTabItem("Aim", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		    ImGui::Text("Aimbot");
		    ImGui::Checkbox("Enabled", &AimbotEnabled);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Toggle the Aimbot");
		        
		    ImGui::Separator();
		    
		    //Select Hitbox
		    ImGui::Text("Hitbox");
		    	const char* HitboxTypes[] = {"Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip"};
		    	int HitboxTypeIndex = static_cast<int>(Modules::Aimbot::Hitbox);
		    	ImGui::Combo("Hitbox Type", &HitboxTypeIndex, HitboxTypes, IM_ARRAYSIZE(HitboxTypes));
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Which bone the aimbot will aim at.");
		    	Modules::Aimbot::Hitbox = static_cast<HitboxType>(HitboxTypeIndex);
		    
		    ImGui::Separator();
	   	    
	   	    ImGui::Text("Aim Conditions");
	   	    ImGui::Checkbox("On Fire?", &OnFire);
	   	    ImGui::SameLine();
	   	    ImGui::Checkbox("On ADS?", &OnADS);
	   	    
		    ImGui::Separator();
		    
		    //Select Weapons
		    ImGui::Text("Weapons");
		    if (ImGui::CollapsingHeader("Selected Weapons", nullptr)) {
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
			ImGui::Checkbox("Bocek Compound Bow", &Bocek);
			ImGui::Checkbox("Kraber .50-CAL Sniper", &Kraber);
			ImGui::SameLine();
			ImGui::Checkbox("Throwing Knife", &Knife);
		    }
		    
		    ImGui::Separator();
		    
		    //Smoothness Settings
		    ImGui::Text("Smoothness");
		    if (ImGui::CollapsingHeader("Smoothness Settings", nullptr)) {
		    	ImGui::SliderFloat("Speed", &Speed, 1, 100, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Speed of the Aim-Assist\nHigher = Faster");

		    	ImGui::SliderFloat("Smooth", &Smooth, 0, 0.99, "%.3f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Smoothness for the Aim-Assist\nHigher = Smoother");
		        	
		    	ImGui::SliderInt("Delay", &Delay, 1, 50);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Delay time for the aimbot smoothing.\n");
		    }
		    
		    ImGui::Separator();

		    //Prediction Settings
		    ImGui::Text("Prediction");
		    if (ImGui::CollapsingHeader("Prediction Settings", nullptr)) {
		    	ImGui::Checkbox("Predict Movement", &PredictMovement);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Predict target's movement");
		    	ImGui::SameLine();
		    	ImGui::Checkbox("Predict Bullet Drop", &PredictBulletDrop);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Predict weapon's bullet drop");
		    }
		    
		    ImGui::Separator();

		    //FOV Settings
		    ImGui::Text("FOV");
		    if (ImGui::CollapsingHeader("FOV Settings", nullptr)) {
		    	ImGui::SliderFloat("FOV", &FOV, 1, 90, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Field of View");
		    	ImGui::SliderFloat("Zoom Scale", &ZoomScale, 0, 5, "%.1f");
		    }
		    
		    ImGui::Separator();

		    //Distance Settings
		    ImGui::Text("Distance");
		    if (ImGui::CollapsingHeader("Distance Settings", nullptr)) {
		    	ImGui::SliderFloat("Hip-fire Distance", &HipfireDistance, 1, 500, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Minimum distance for Aim-Assist to work");
		    	ImGui::SliderFloat("Zoom Distance", &ZoomDistance, 1, 500, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Maximum distance for Aim-Assist to work");
		    }
		    
		    ImGui::EndTabItem();
		    UpdateAimList();
	    	}
    	}
    }

    bool Save() {
        try {
            Config::Aimbot::Enabled = AimbotEnabled;
            Config::Aimbot::HitBox = static_cast<int>(Modules::Aimbot::Hitbox);
            
            Config::Aimbot::OnFire = OnFire;
            Config::Aimbot::OnADS = OnADS;
            
            Config::Aimbot::PredictMovement = PredictMovement;
            Config::Aimbot::PredictBulletDrop = PredictBulletDrop;
            Config::Aimbot::Speed = Speed;
            Config::Aimbot::Smooth = Smooth;
            Config::Aimbot::Delay = Delay;
            Config::Aimbot::FOV = FOV;
            Config::Aimbot::ZoomScale = ZoomScale;
            Config::Aimbot::MinDistance = MinDistance;
            Config::Aimbot::HipfireDistance = HipfireDistance;
            Config::Aimbot::ZoomDistance = ZoomDistance;
            
            //Weapons
            //Light
            Config::Aimbot::P2020 = P2020;
            Config::Aimbot::RE45 = RE45;
            Config::Aimbot::Alternator = Alternator;
            Config::Aimbot::R99 = R99;
            Config::Aimbot::R301 = R301;
            Config::Aimbot::Spitfire = Spitfire;
            Config::Aimbot::G7 = G7;
            //Heavy
            Config::Aimbot::Flatline = Flatline;
            Config::Aimbot::Hemlock = Hemlock;
            Config::Aimbot::Repeater = Repeater;
            Config::Aimbot::Rampage = Rampage;
            Config::Aimbot::CARSMG = CARSMG;
            //Energy
            Config::Aimbot::Havoc = Havoc;
            Config::Aimbot::Devotion = Devotion;
            Config::Aimbot::LSTAR = LSTAR;
            Config::Aimbot::TripleTake = TripleTake;
            Config::Aimbot::Volt = Volt;
            Config::Aimbot::Nemesis = Nemesis;
            //Shotguns
            Config::Aimbot::Mozambique = Mozambique;
            Config::Aimbot::EVA8 = EVA8;
            Config::Aimbot::Peacekeeper = Peacekeeper;
            Config::Aimbot::Mastiff = Mastiff;
            //Snipers
            Config::Aimbot::Longbow = Longbow;
            Config::Aimbot::ChargeRifle = ChargeRifle;
            Config::Aimbot::Sentinel = Sentinel;
            //Legendary
            Config::Aimbot::Wingman = Wingman;
            Config::Aimbot::Prowler = Prowler;
            Config::Aimbot::Bocek = Bocek;
            Config::Aimbot::Kraber = Kraber;
            Config::Aimbot::Knife = Knife;
            return true;
        } catch (...) {
            return false;
        }
    }
    
    void UpdateAimList() {
        AimList.clear();
        //Light
        if (P2020)
            AimList.insert(AimbotId::WEAPON_P2020);
        if (RE45)
            AimList.insert(AimbotId::WEAPON_RE45);
        if (Alternator)
            AimList.insert(AimbotId::WEAPON_ALTERNATOR);
        if (R99)
            AimList.insert(AimbotId::WEAPON_R99);
        if (R301)
            AimList.insert(AimbotId::WEAPON_R301);
        if (Spitfire)
            AimList.insert(AimbotId::WEAPON_SPITFIRE);
        if (G7)
            AimList.insert(AimbotId::WEAPON_G7);
        //Heavy
        if (Flatline)
            AimList.insert(AimbotId::WEAPON_FLATLINE);
        if (Hemlock)
            AimList.insert(AimbotId::WEAPON_HEMLOCK);
        if (Repeater)
            AimList.insert(AimbotId::WEAPON_REPEATER);
        if (Rampage)
            AimList.insert(AimbotId::WEAPON_RAMPAGE);
        if (CARSMG)
            AimList.insert(AimbotId::WEAPON_CAR);
        //Energy
        if (Havoc)
            AimList.insert(AimbotId::WEAPON_HAVOC);
        if (Devotion)
            AimList.insert(AimbotId::WEAPON_DEVOTION);
        if (LSTAR)
            AimList.insert(AimbotId::WEAPON_LSTAR);
        if (TripleTake)
            AimList.insert(AimbotId::WEAPON_TRIPLETAKE);
        if (Volt)
            AimList.insert(AimbotId::WEAPON_VOLT);
        if (Nemesis)
            AimList.insert(AimbotId::WEAPON_NEMESIS);
        //Shotguns
        if (Mozambique)
            AimList.insert(AimbotId::WEAPON_MOZAMBIQUE);
        if (EVA8)
            AimList.insert(AimbotId::WEAPON_EVA8);
        if (Peacekeeper)
            AimList.insert(AimbotId::WEAPON_PEACEKEEPER);
        if (Mastiff)
            AimList.insert(AimbotId::WEAPON_MASTIFF);
        //Snipers
        if (Longbow)
            AimList.insert(AimbotId::WEAPON_LONGBOW);
        if (ChargeRifle)
            AimList.insert(AimbotId::WEAPON_CHARGE_RIFLE);
        if (Sentinel)
            AimList.insert(AimbotId::WEAPON_SENTINEL);
	//Legendary
	if (Wingman)
            AimList.insert(AimbotId::WEAPON_WINGMAN);
        if (Prowler)
            AimList.insert(AimbotId::WEAPON_PROWLER);
        if (Bocek)
            AimList.insert(AimbotId::WEAPON_BOCEK);
        if (Kraber)
            AimList.insert(AimbotId::WEAPON_KRABER);
        if (Knife)
            AimList.insert(AimbotId::WEAPON_KNIFE);
    }

    void Update() {
    	if (OnFire && OnADS) {
		if (!AimbotEnabled) { ReleaseTarget(); return; }

		if (Myself->IsZooming)
		    FinalDistance = ZoomDistance;
		else FinalDistance = HipfireDistance;

		if (Myself->IsHoldingGrenade) { ReleaseTarget(); return; }
		
		if (!Myself->IsInAttack) {
			if (!Myself->IsZooming) {
			ReleaseTarget(); 
			TargetSelected = false; 
			CurrentTarget = nullptr; 
			return; 
			}
		}
		if (!Myself->IsZooming) {
			if (!Myself->IsInAttack) {
			ReleaseTarget(); 
			TargetSelected = false; 
			CurrentTarget = nullptr; 
			return; 
			}
		}

		Player* Target = CurrentTarget;
		if (!IsValidTarget(Target)) {
		    if (TargetSelected)
		        return;

		    Target = FindBestTarget();
		    if (!IsValidTarget(Target)) {
		        ReleaseTarget();
		        return;
		    }
		    
		    CurrentTarget = Target;
		    CurrentTarget->IsLockedOn = true;
		    TargetSelected = true;
		} 
		
		if (TargetSelected && CurrentTarget) {
		    std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		    if (Now >= LastAimTime + std::chrono::milliseconds(Delay)) {
		        StartAiming();
		        LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
		    }
		    return;
		}
	    }
    	if (OnFire) {
		if (!AimbotEnabled) { ReleaseTarget(); return; }

		if (Myself->IsZooming)
		    FinalDistance = ZoomDistance;
		else FinalDistance = HipfireDistance;
		
		if (!Myself->IsInAttack) { ReleaseTarget(); return; }

		if (Myself->IsHoldingGrenade) { ReleaseTarget(); return; }

		Player* Target = CurrentTarget;
		if (!IsValidTarget(Target)) {
		    if (TargetSelected)
		        return;

		    Target = FindBestTarget();
		    if (!IsValidTarget(Target)) {
		        ReleaseTarget();
		        return;
		    }
		    
		    CurrentTarget = Target;
		    CurrentTarget->IsLockedOn = true;
		    TargetSelected = true;
		} 
		
		if (TargetSelected && CurrentTarget) {
		    std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		    if (Now >= LastAimTime + std::chrono::milliseconds(Delay)) {
		        StartAiming();
		        LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
		    }
		    return;
		}
	    }
	    
    	if (OnADS) {
		if (!AimbotEnabled) { ReleaseTarget(); return; }

		if (Myself->IsZooming)
		    FinalDistance = ZoomDistance;
		else FinalDistance = HipfireDistance;
		
		if (!Myself->IsZooming) { ReleaseTarget(); return; }

		if (Myself->IsHoldingGrenade) { ReleaseTarget(); return; }

		Player* Target = CurrentTarget;
		if (!IsValidTarget(Target)) {
		    if (TargetSelected)
		        return;

		    Target = FindBestTarget();
		    if (!IsValidTarget(Target)) {
		        ReleaseTarget();
		        return;
		    }
		    
		    CurrentTarget = Target;
		    CurrentTarget->IsLockedOn = true;
		    TargetSelected = true;
		} 
		
		if (TargetSelected && CurrentTarget) {
		    std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		    if (Now >= LastAimTime + std::chrono::milliseconds(10)) {
		        StartAiming();
		        LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
		    }
		    return;
		}
	    }
	}

    void StartAiming() {
        // Get Target Angle
        QAngle DesiredAngles = QAngle(0, 0);
        if (!GetAngle(CurrentTarget, DesiredAngles))
            return;

        // Smoothing
        SmoothAngle(DesiredAngles);

        // Aim angles
        Vector2D aimbotDelta = Vector2D(CalculatePitchIncrement(DesiredAngles), CalculateYawIncrement(DesiredAngles)).Multiply(Speed);
        int totalYawIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.x));
        int totalPitchIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.y * -1));

        // Move Mouse
        if (totalPitchIncrementInt == 0 && totalYawIncrementInt == 0) return;
        X11Display->MoveMouse(totalYawIncrementInt, totalPitchIncrementInt);
    }

    void SmoothAngle(QAngle& Angle) {
        QAngle ViewAngles = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
        QAngle Delta = Angle - ViewAngles;
        Delta.NormalizeAngles();
        
        float SmoothValue = powf(this->Smooth, 0.4f);
        SmoothValue = std::min(0.99f, SmoothValue);

        QAngle ToChange = QAngle();
	    ToChange = Delta - Delta * Smooth;

        Angle = ViewAngles + ToChange;
    }

    bool GetAngle(Player* Target, QAngle& Angle) {
        const QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
        if (!CurrentAngle.isValid())
            return false;

        if (!GetAngleToTarget(Target, Angle))
            return false;

        return true;
    }

    bool GetAngleToTarget(Player* Target, QAngle& Angle) {
    	Vector3D TargetPosition = Target->GetBonePosition(Modules::Aimbot::Hitbox);
        Vector3D TargetVelocity = Target->AbsoluteVelocity;
        Vector3D CameraPosition = Myself->CameraPosition;
        QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
        
        if (Myself->WeaponProjectileSpeed > 1.0f) {
            if (PredictBulletDrop && PredictMovement) {
                return Resolver::CalculateAimRotationNew(CameraPosition, TargetPosition, TargetVelocity, Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, 255, Angle);
            }
            else if (PredictBulletDrop) {
                return Resolver::CalculateAimRotationNew(CameraPosition, TargetPosition, Vector3D(0, 0, 0), Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, 255, Angle);
            }
            else if (PredictMovement) {
                return Resolver::CalculateAimRotation(CameraPosition, TargetPosition, TargetVelocity, Myself->WeaponProjectileSpeed, Angle);
            }
        }

        Angle = Resolver::CalculateAngle(CameraPosition, TargetPosition);
        return true;   
    }

    bool IsValidTarget(Player* target) {
        if (target == nullptr ||
            !target->IsValid() || 
            !target->IsCombatReady() || 
            !target->IsVisible || 
            !target->IsHostile || 
            target->Distance2DToLocalPlayer < Conversion::ToGameUnits(MinDistance) || 
            target->Distance2DToLocalPlayer > Conversion::ToGameUnits(FinalDistance))
            return false;
        return true;
    }


    float CalculatePitchIncrement(QAngle AimbotDesiredAngles) {
        float wayA = AimbotDesiredAngles.x - Myself->ViewAngles.x;
        float wayB = 180 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float CalculateYawIncrement(QAngle AimbotDesiredAngles) {
        float wayA = AimbotDesiredAngles.y - Myself->ViewAngles.y;
        float wayB = 360 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    double CalculateDistanceFromCrosshair(Vector3D TargetPosition) {
        Vector3D CameraPosition = Myself->CameraPosition;
        QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();

        if (CameraPosition.Distance(TargetPosition) <= 0.0001f)
            return -1;

        QAngle TargetAngle = Resolver::CalculateAngle(CameraPosition, TargetPosition);
        if (!TargetAngle.isValid())
            return -1;
        
        return CurrentAngle.distanceTo(TargetAngle);
    }

    void ReleaseTarget() {
        if (CurrentTarget != nullptr && CurrentTarget->IsValid())
            CurrentTarget->IsLockedOn = false;
        
        TargetSelected = false;
        CurrentTarget = nullptr;
    }

    int RoundHalfEven(float x) {
        return (x >= 0.0)
            ? static_cast<int>(std::round(x))
            : static_cast<int>(std::round(-x)) * -1;
    }

    float AL1AF0(float num) {
        if (num > 0) return std::max(num, 1.0f);
        return std::min(num, -1.0f);
    }

    float GetFOVScale() {
        if (Myself->IsValid()) {
            if (Myself->IsZooming) {
                if (Myself->TargetZoomFOV > 1.0 && Myself->TargetZoomFOV < 90.0) {
                    return tanf(DEG2RAD(Myself->TargetZoomFOV) * (0.64285714285));
                }
            }
        }
        return 1.0;
    }

    int GetBestBone(Player* Target) {
        float NearestDistance = 999;
        int NearestBone = 2;
        for (int i = 0; i < 6; i++) {
            HitboxType Bone = static_cast<HitboxType>(i);
            double DistanceFromCrosshair = CalculateDistanceFromCrosshair(Target->GetBonePosition(Bone));
            if (DistanceFromCrosshair < NearestDistance) {
                NearestBone = i;
                NearestDistance = DistanceFromCrosshair;
            }
        }
        return NearestBone;
    }

    Player* FindBestTarget() {
        Player* NearestTarget = nullptr;
        float BestDistance = 9999;
        float BestFOV = std::min(FOV, FOV * (GetFOVScale() * ZoomScale));
        Vector3D CameraPosition = Myself->CameraPosition;
        for (int i = 0; i < Players->size(); i++) {
            Player* p = Players->at(i);
            if (!IsValidTarget(p)) continue;
            if (p->DistanceToLocalPlayer < Conversion::ToGameUnits(ZoomDistance)) {
                HitboxType BestBone = static_cast<HitboxType>(GetBestBone(p));
                Vector3D TargetPosition = p->GetBonePosition(BestBone);

                float Distance = CameraPosition.Distance(TargetPosition);
                float FOV = CalculateDistanceFromCrosshair(TargetPosition);

                if (FOV > BestFOV) continue;
                if (Distance > BestDistance) continue;

                NearestTarget = p;
                BestDistance = Distance;
            }
        }
        return NearestTarget;
    }
};
