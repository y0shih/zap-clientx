#pragma once
#include <iostream>
#include <vector>
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
    
    bool ClosestHitbox = false;
    bool OnFire = true;
    bool OnADS = true;
    bool VisCheck = true;
    
    bool PredictMovement = true;
    bool PredictBulletDrop = true;
    float FinalDistance = 0;
    float Speed = 20;
    float Smooth = 0.9;
    float SmoothDistance = 100;
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
    bool Wingman = true;
    bool Prowler = true;
    bool Bocek = true;
    bool Kraber = true;
    bool Knife = true;
    
    //---------------Advanced---------------//
    bool AdvancedAim = false;
    float AdvancedSpeed = 20;
    float AdvancedSmooth = 0.99;
    
    float P2020Speed = 10;
    float P2020Smooth = 10;
    float RE45Speed = 10;
    float RE45Smooth = 10;
    float AlternatorSpeed = 10;
    float AlternatorSmooth = 10;
    float R99Speed = 10;
    float R99Smooth = 10;
    float R301Speed = 10;
    float R301Smooth = 10;
    float SpitfireSpeed = 10;
    float SpitfireSmooth = 10;
    float G7Speed = 10;
    float G7Smooth = 10;
    //Heavy
    float FlatlineSpeed = 10;
    float FlatlineSmooth = 10;
    float HemlockSpeed = 10;
    float HemlockSmooth = 10;
    float RepeaterSpeed = 10;
    float RepeaterSmooth = 10;
    float RampageSpeed = 10;
    float RampageSmooth = 10;
    float CARSMGSpeed = 10;
    float CARSMGSmooth = 10;
    //Energy
    float HavocSpeed = 10;
    float HavocSmooth = 10;
    float DevotionSpeed = 10;
    float DevotionSmooth = 10;
    float LSTARSpeed = 10;
    float LSTARSmooth = 10;
    float TripleTakeSpeed = 10;
    float TripleTakeSmooth = 10;
    float VoltSpeed = 10;
    float VoltSmooth = 10;
    float NemesisSpeed = 10;
    float NemesisSmooth = 10;
    //Shotguns
    float MozambiqueSpeed = 10;
    float MozambiqueSmooth = 10;
    float EVA8Speed = 10;
    float EVA8Smooth = 10;
    float PeacekeeperSpeed = 10;
    float PeacekeeperSmooth = 10;
    float MastiffSpeed = 10;
    float MastiffSmooth = 10;
    //Snipers
    float LongbowSpeed = 10;
    float LongbowSmooth = 10;
    float ChargeRifleSpeed = 10;
    float ChargeRifleSmooth = 10;
    float SentinelSpeed = 10;
    float SentinelSmooth = 10;
    //Legendary
    float WingmanSpeed = 10;
    float WingmanSmooth = 10;
    float ProwlerSpeed = 10;
    float ProwlerSmooth = 10;
    float KraberSpeed = 10;
    float KraberSmooth = 10;
    float BocekSpeed = 10;
    float BocekSmooth = 10;
    float ThrowingKnifeSpeed = 10;
    float ThrowingKnifeSmooth = 10;

    XDisplay* X11Display;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;
    Level* Map;

    Player* CurrentTarget = nullptr;
    bool TargetSelected = true;
    QAngle RCSLastPunch;
    std::chrono::milliseconds LastAimTime;
    
    std::set<int> AimList = {};

    Aimbot(XDisplay* X11Display, Level* Map, LocalPlayer* Myself, std::vector<Player*>* GamePlayers) {
        this->X11Display = X11Display;
        this->Myself = Myself;
        this->Map = Map;
        this->Players = GamePlayers;
    }

    void RenderUI() {
    	if (Config::Home::Layout == 0 or Config::Home::Layout == 1) { //Removed the choice of having two menus. OR is for people still using old configs.
		if (ImGui::BeginTabItem("Aim", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		    ImGui::Text("Aimbot");
		    ImGui::Checkbox("Enabled", &AimbotEnabled);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Toggle the Aimbot");
		        
		    ImGui::Separator();
		    
		    //Select Hitbox
		    ImGui::Text("Hitbox");
		    ImGui::Checkbox("Closest To Crosshair", &ClosestHitbox);
		    if (!ClosestHitbox) {
		    	const char* HitboxTypes[] = {"Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip"};
		    	int HitboxTypeIndex = static_cast<int>(Modules::Aimbot::Hitbox);
		    	ImGui::Combo("Hitbox Type", &HitboxTypeIndex, HitboxTypes, IM_ARRAYSIZE(HitboxTypes));
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Which bone the aimbot will aim at.");
		    	Modules::Aimbot::Hitbox = static_cast<HitboxType>(HitboxTypeIndex);
		    }
		    
		    ImGui::Separator();
	   	    
	   	    ImGui::Text("Aim Conditions");
	   	    ImGui::Checkbox("On Fire?", &OnFire);
	   	    ImGui::SameLine();
	   	    ImGui::Checkbox("On ADS?", &OnADS);
	   	    ImGui::SameLine();
	   	    ImGui::Checkbox("Visibility Check", &VisCheck);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Aims At Only Visible Enemies.");
	   	    
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

		    	ImGui::SliderFloat("Smoothing", &Smooth, 0, 0.99, "%.3f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Smoothing for the Aim-Assist\nHigher = Smoother");
		        	
		    	ImGui::SliderFloat("Distance Smoothing", &SmoothDistance, 1, 10000, "%.0f");
		        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.\nMay not change much.");
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
		    
		    ImGui::Separator();
			    
		    ImGui::Text("Advanced Aimbot Settings");
		    ImGui::Checkbox("Enabled Advanced Aimbot", &AdvancedAim);
		    if (AdvancedAim) {
		    	ImGui::Separator();
		    	ImGui::Text("Weapon Smoothing Settings");
		    	if (ImGui::CollapsingHeader("Light", nullptr)) {
		    		if (P2020) {
			    		ImGui::Text("P2020");
			    		ImGui::SliderFloat("Speed##AdvancedP2020", &P2020Speed, 1, 100, "%.0f");
			    		if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			    			ImGui::SetTooltip("Speed Of The Aim-Assist For The P2020\nHigher = Faster");
			    		ImGui::SliderFloat("Smoothing##AdvancedP2020", &P2020Smooth, 0, 0.99, "%.3f");
			    		if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			    			ImGui::SetTooltip("Smoothing Of The Aim-Assist For The P2020\nHigher = Smoother");
			    	}
			    	if (RE45) {
			    			ImGui::Text("RE-45 Auto");
					    	ImGui::SliderFloat("Speed##AdvancedRE45", &RE45Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The RE-45 Auto\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedRE45", &RE45Smooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The RE-45 Auto\nHigher = Smoother");
			    	}
			    		
			    	if (Alternator) {
			    			ImGui::Text("Alternator SMG");
					    	ImGui::SliderFloat("Speed##AdvancedAlternator", &AlternatorSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Alternator SMG\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedAlternator", &AlternatorSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Alternator SMG\nHigher = Smoother");
			    	}
			    		
			    	if (R99) {
			    			ImGui::Text("R-99 SMG");
					    	ImGui::SliderFloat("Speed##AdvancedR99", &R99Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The R-99 SMG\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedR99", &R99Smooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R-99 SMG\nHigher = Smoother");
			    	}
			    		
			    	if (R301) {
			    			ImGui::Text("R-301 Carbine");
					    	ImGui::SliderFloat("Speed##AdvancedR301", &R301Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The R-301 Carbine\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedR301", &R301Smooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R-301 Carbine\nHigher = Smoother");
			    	}
			    		
			    	if (Spitfire) {
			    			ImGui::Text("M600 Spitfire");
					    	ImGui::SliderFloat("Speed##AdvancedSpitfire", &SpitfireSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The M600 Spitfire\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedSpitfire", &SpitfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The M600 Spitfire\nHigher = Smoother");
			    	}
			    		
			    	if (G7) {
			    			ImGui::Text("G7 Scout");
					    	ImGui::SliderFloat("Speed##AdvancedG7", &G7Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The G7 Scout\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedG7", &G7Smooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The G7 Scout\nHigher = Smoother");
			    	}
		    	}
			    	
		    	if (ImGui::CollapsingHeader("Heavy", nullptr)) {
			    	if (Flatline) {
			    		ImGui::Text("VK-47 Flatline");
					    	ImGui::SliderFloat("Speed##AdvancedFlatline", &FlatlineSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The VK-47 Flatline\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedFlatline", &FlatlineSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The VK-47 Flatline\nHigher = Smoother");
			    	}
			    		
			    	if (Hemlock) {
			    			ImGui::Text("Hemlock Burst AR");
					    	ImGui::SliderFloat("Speed##AdvancedHemlock", &HemlockSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Hemlock Burst AR\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedHemlock", &HemlockSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Hemlock Burst AR\nHigher = Smoother");
			    	}
			    		
			    	if (Repeater) {
			    			ImGui::Text("30-30 Repeater");
					    	ImGui::SliderFloat("Speed##AdvancedRepeater", &RepeaterSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The 30-30 Repeater\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedRepeater", &RepeaterSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The 30-30 Repeater\nHigher = Smoother");
			    	}
			    		
			    	if (Rampage) {
			    			ImGui::Text("Rampage LMG");
					    	ImGui::SliderFloat("Speed##AdvancedRampage", &RampageSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Rampage LMG\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedRampage", &RampageSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Rampage LMG\nHigher = Smoother");
			    	}
			    		
			    	if (CARSMG) {
			    			ImGui::Text("C.A.R SMG");
					    	ImGui::SliderFloat("Speed##AdvancedCARSMG", &CARSMGSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The C.A.R SMG\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedCARSMG", &CARSMGSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The C.A.R SMG\nHigher = Smoother");
			    	}
		    	}
			    	
		    	if (ImGui::CollapsingHeader("Energy", nullptr)) {
			    	if (Havoc) {
			    			ImGui::Text("Havoc");
					    	ImGui::SliderFloat("Speed##AdvancedHavoc", &HavocSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Havoc\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedHavoc", &HavocSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Havoc\nHigher = Smoother");
			    	}
			    		
			    	if (Devotion) {
			    			ImGui::Text("Devotion LMG");
					    	ImGui::SliderFloat("Speed##AdvancedDevotion", &DevotionSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Devotion LMG\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedDevotion", &DevotionSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Devotion LMG\nHigher = Smoother");
			    	}
			    		
			    	if (LSTAR) {
			    			ImGui::Text("L-Star EMG");
					    	ImGui::SliderFloat("Speed##AdvancedLSTAR", &LSTARSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The L-Star EMG\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedLSTAR", &LSTARSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The L-Star EMG\nHigher = Smoother");
			    	}
			    		
			    	if (TripleTake) {
			    			ImGui::Text("Triple-Take");
					    	ImGui::SliderFloat("Speed##AdvancedTripleTake", &TripleTakeSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Triple-Take\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedTripleTake", &TripleTakeSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Triple-Take\nHigher = Smoother");
			    	}
			    		
			    	if (Volt) {
			    			ImGui::Text("Volt");
					    	ImGui::SliderFloat("Speed##AdvancedVolt", &VoltSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Volt\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedVolt", &VoltSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Volt\nHigher = Smoother");
			    	}
			    		
			    	if (Nemesis) {
			    			ImGui::Text("Nemesis Burst AR");
					    	ImGui::SliderFloat("Speed##AdvancedNemesis", &NemesisSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Nemesis Burst AR\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedNemesis", &NemesisSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Nemesis Burst AR\nHigher = Smoother");
			    	}
		    	}
				
		    	if (ImGui::CollapsingHeader("Shotguns", nullptr)) {
			    	if (Mozambique) {
			    			ImGui::Text("Mozambique");
					    	ImGui::SliderFloat("Speed##AdvancedMozambique", &MozambiqueSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Mozambique\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedMozambique", &MozambiqueSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mozambique\nHigher = Smoother");
			    	}
			    		
			    	if (EVA8) {
			    			ImGui::Text("EVA-8 Auto");
					    	ImGui::SliderFloat("Speed##AdvancedEVA8", &EVA8Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The EVA-8 Auto\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedEVA8", &EVA8Smooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The EVA-8 Auto\nHigher = Smoother");
			    	}
			    		
			    	if (Peacekeeper) {
			    			ImGui::Text("Peacekeeper");
					    	ImGui::SliderFloat("Speed##AdvancedPeacekeeper", &PeacekeeperSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Peacekeeper\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedPeacekeeper", &PeacekeeperSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Peacekeeper\nHigher = Smoother");
			    	}
			    		
			    	if (Mastiff) {
			    			ImGui::Text("Mastiff");
					    	ImGui::SliderFloat("Speed##AdvancedMastiff", &MastiffSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Mastiff\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedMastiff", &MastiffSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mastiff\nHigher = Smoother");
			    	}
		    	}
				
		    	if (ImGui::CollapsingHeader("Snipers", nullptr)) {
			    	if (Longbow) {
			    			ImGui::Text("Longbow DMR");
					    	ImGui::SliderFloat("Speed##AdvancedLongbow", &LongbowSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Longbow DMR\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedLongbow", &LongbowSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Longbow DMR\nHigher = Smoother");
			    	}
			    		
			    	if (ChargeRifle) {
			    			ImGui::Text("Charge Rifle");
					    	ImGui::SliderFloat("Speed##AdvancedChargeRifle", &ChargeRifleSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Charge Rifle\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedChargeRifle", &ChargeRifleSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Charge Rifle\nHigher = Smoother");
			    	}
			    		
			    	if (Sentinel) {
			    			ImGui::Text("Sentinel");
					    	ImGui::SliderFloat("Speed##AdvancedSentinel", &SentinelSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Sentinel\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedSentinel", &SentinelSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Sentinel\nHigher = Smoother");
			    	}
		    	}
				
		    	if (ImGui::CollapsingHeader("Legendary", nullptr)) {
			    	if (Wingman) {
			    			ImGui::Text("Wingman");
					    	ImGui::SliderFloat("Speed##AdvancedWingman", &WingmanSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Wingman\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedWingman", &WingmanSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Wingman\nHigher = Smoother");
			    	}
			    		
			    	if (Prowler) {
			    			ImGui::Text("Prowler Burst SMG");
					    	ImGui::SliderFloat("Speed##AdvancedProwler", &ProwlerSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Prowler Burst SMG\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedProwler", &ProwlerSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Prowler Burst SMG\nHigher = Smoother");
			    	}
			    	
			    	if (Bocek) {
			    			ImGui::Text("Bocek Compound Bow");
					    	ImGui::SliderFloat("Speed##AdvancedBocek", &BocekSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Bocek Compound Bow\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedBocek", &BocekSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Bocek Compound Bow\nHigher = Smoother");
			    	}
			    		
			    	if (Kraber) {
			    			ImGui::Text("Kraber .50-CAL Sniper");
					    	ImGui::SliderFloat("Speed##AdvancedKraber", &KraberSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Kraber .50-CAL Sniper\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedKraber", &KraberSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Kraber .50-CAL Sniper\nHigher = Smoother");
			    	}
			    	
			    	if (Knife) {
			    			ImGui::Text("Throwing Knife");
					    	ImGui::SliderFloat("Speed##AdvancedKnife", &ThrowingKnifeSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Throwing Knife\nHigher = Faster");
					    	ImGui::SliderFloat("Smoothing##AdvancedKnife", &ThrowingKnifeSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Throwing Knife\nHigher = Smoother");
			    	}
		    	}
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
            Config::Aimbot::ClosestHitbox = ClosestHitbox;
            
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
            
            //----------Advanced Settings----------//
            Config::Aimbot::AdvancedAim = AdvancedAim;
            //Advanced Weapons
            //Light
            Config::Aimbot::P2020Speed = P2020Speed;
            Config::Aimbot::P2020Smooth = P2020Smooth;
            Config::Aimbot::RE45Speed = RE45Speed;
            Config::Aimbot::RE45Smooth = RE45Smooth;
            Config::Aimbot::AlternatorSpeed = AlternatorSpeed;
            Config::Aimbot::AlternatorSmooth = AlternatorSmooth;
            Config::Aimbot::R99Speed = R99Speed;
            Config::Aimbot::R99Smooth = R99Smooth;
            Config::Aimbot::R301Speed = R301Speed;
            Config::Aimbot::R301Smooth = R301Smooth;
            Config::Aimbot::SpitfireSpeed = SpitfireSpeed;
            Config::Aimbot::SpitfireSmooth = SpitfireSmooth;
            Config::Aimbot::G7Speed = G7Speed;
            Config::Aimbot::G7Smooth = G7Smooth;
            //Heavy
            Config::Aimbot::FlatlineSpeed = FlatlineSpeed;
            Config::Aimbot::FlatlineSmooth = FlatlineSmooth;
            Config::Aimbot::HemlockSpeed = HemlockSpeed;
            Config::Aimbot::HemlockSmooth = HemlockSmooth;
            Config::Aimbot::RepeaterSpeed = RepeaterSpeed;
            Config::Aimbot::RepeaterSmooth = RepeaterSmooth;
            Config::Aimbot::RampageSpeed = RampageSpeed;
            Config::Aimbot::RampageSmooth = RampageSmooth;
            Config::Aimbot::CARSMGSpeed = CARSMGSpeed;
            Config::Aimbot::CARSMGSmooth = CARSMGSmooth;
            //Energy
            Config::Aimbot::HavocSpeed = HavocSpeed;
            Config::Aimbot::HavocSmooth = HavocSmooth;
            Config::Aimbot::DevotionSpeed = DevotionSpeed;
            Config::Aimbot::DevotionSmooth = DevotionSmooth;
            Config::Aimbot::LSTARSpeed = LSTARSpeed;
            Config::Aimbot::LSTARSmooth = LSTARSmooth;
            Config::Aimbot::TripleTakeSpeed = TripleTakeSpeed;
            Config::Aimbot::TripleTakeSmooth = TripleTakeSmooth;
            Config::Aimbot::VoltSpeed = VoltSpeed;
            Config::Aimbot::VoltSmooth = VoltSmooth;
            Config::Aimbot::NemesisSpeed = NemesisSpeed;
            Config::Aimbot::NemesisSmooth = NemesisSmooth;
            //Shotguns
            Config::Aimbot::MozambiqueSpeed = MozambiqueSpeed;
            Config::Aimbot::MozambiqueSmooth = MozambiqueSmooth;
            Config::Aimbot::EVA8Speed = EVA8Speed;
            Config::Aimbot::EVA8Smooth = EVA8Smooth;
            Config::Aimbot::PeacekeeperSpeed = PeacekeeperSpeed;
            Config::Aimbot::PeacekeeperSmooth = PeacekeeperSmooth;
            Config::Aimbot::MastiffSpeed = MastiffSpeed;
            Config::Aimbot::MastiffSmooth = MastiffSmooth;
            //Snipers
            Config::Aimbot::LongbowSpeed = LongbowSpeed;
            Config::Aimbot::LongbowSmooth = LongbowSmooth;
            Config::Aimbot::ChargeRifleSpeed = ChargeRifleSpeed;
            Config::Aimbot::ChargeRifleSmooth = ChargeRifleSmooth;
            Config::Aimbot::SentinelSpeed = SentinelSpeed;
            Config::Aimbot::SentinelSmooth = SentinelSmooth;
            //Legendary
            Config::Aimbot::WingmanSpeed = WingmanSpeed;
            Config::Aimbot::WingmanSmooth = WingmanSmooth;
            Config::Aimbot::ProwlerSpeed = ProwlerSpeed;
            Config::Aimbot::ProwlerSmooth = ProwlerSmooth;
            Config::Aimbot::KraberSpeed = BocekSpeed;
            Config::Aimbot::KraberSmooth = BocekSmooth;
            Config::Aimbot::KraberSpeed = KraberSpeed;
            Config::Aimbot::KraberSmooth = KraberSmooth;
            Config::Aimbot::KraberSpeed = ThrowingKnifeSpeed;
            Config::Aimbot::KraberSmooth = ThrowingKnifeSmooth;
            
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
    	if(!Map->IsPlayable) return;
        //Advanced Settings
    	if (AdvancedAim) { //IDs from Utils/Weapons.hpp, may need updating after game update
    		int weaponHeld = Myself->WeaponIndex;
    		//Light Weapons
    		if (weaponHeld == 105) { //P2020
    			Aimbot::AdvancedSpeed = Aimbot::P2020Speed;
    			Aimbot::AdvancedSmooth = Aimbot::P2020Smooth;
    		}
    		if (weaponHeld == 81) { //RE-45
    			Aimbot::AdvancedSpeed = Aimbot::RE45Speed;
    			Aimbot::AdvancedSmooth = Aimbot::RE45Smooth;
    		}
    		if (weaponHeld == 80) { //Alternator
    			Aimbot::AdvancedSpeed = Aimbot::AlternatorSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::AlternatorSmooth;
    		}
    		if (weaponHeld == 104) { //R-99
    			Aimbot::AdvancedSpeed = Aimbot::R99Speed;
    			Aimbot::AdvancedSmooth = Aimbot::R99Smooth;
    		}
    		if (weaponHeld == 0) { //R-301
    			Aimbot::AdvancedSpeed = Aimbot::R301Speed;
    			Aimbot::AdvancedSmooth = Aimbot::R301Smooth;
    		}
    		if (weaponHeld == 106) { //Spitfire
    			Aimbot::AdvancedSpeed = Aimbot::SpitfireSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::SpitfireSmooth;
    		}
    		if (weaponHeld == 89) { //G7
    			Aimbot::AdvancedSpeed = Aimbot::G7Speed;
    			Aimbot::AdvancedSmooth = Aimbot::G7Smooth;
    		}
    		//Heavy Weapons
    		if (weaponHeld == 112) { //CARSMG
    			Aimbot::AdvancedSpeed = Aimbot::CARSMGSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::CARSMGSmooth;
    		}
    		if (weaponHeld == 21) { //Rampage
    			Aimbot::AdvancedSpeed = Aimbot::RampageSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::RampageSmooth;
    		}
    		if (weaponHeld == 111) { //Repeater
    			Aimbot::AdvancedSpeed = Aimbot::RepeaterSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::RepeaterSmooth;
    		}
    		if (weaponHeld == 90) { //Hemlock
    			Aimbot::AdvancedSpeed = Aimbot::HemlockSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::HemlockSmooth;
    		}
    		if (weaponHeld == 88) { //Flatline
    			Aimbot::AdvancedSpeed = Aimbot::FlatlineSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::FlatlineSmooth;
    		}
    		//Energy Weapons
    		if (weaponHeld == 113) { //Nemesis
    			Aimbot::AdvancedSpeed = Aimbot::NemesisSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::NemesisSmooth;
    		}
    		if (weaponHeld == 110) { //Volt
    			Aimbot::AdvancedSpeed = Aimbot::VoltSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::VoltSmooth;
    		}
    		if (weaponHeld == 107) { //TripleTake
    			Aimbot::AdvancedSpeed = Aimbot::TripleTakeSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::TripleTakeSmooth;
    		}
    		if (weaponHeld == 93) { //LSTAR
    			Aimbot::AdvancedSpeed = Aimbot::LSTARSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::LSTARSmooth;
    		}
    		if (weaponHeld == 84) { //Devotion
    			Aimbot::AdvancedSpeed = Aimbot::DevotionSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::DevotionSmooth;
    		}
    		if (weaponHeld == 86) { //Havoc
    			Aimbot::AdvancedSpeed = Aimbot::HavocSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::HavocSmooth;
    		}
    		//Shotguns
    		if (weaponHeld == 96) { //Mozambique
    			Aimbot::AdvancedSpeed = Aimbot::MozambiqueSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::MozambiqueSmooth;
    		}
    		if (weaponHeld == 87) { //EVA8
    			Aimbot::AdvancedSpeed = Aimbot::EVA8Speed;
    			Aimbot::AdvancedSmooth = Aimbot::EVA8Smooth;
    		}
    		if (weaponHeld == 103) { //Peacekeeper
    			Aimbot::AdvancedSpeed = Aimbot::PeacekeeperSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::PeacekeeperSmooth;
    		}
    		if (weaponHeld == 95) { //Mastiff
    			Aimbot::AdvancedSpeed = Aimbot::MastiffSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::MastiffSmooth;
    		}
    		//Snipers
    		if (weaponHeld == 1) { //Sentinel
    			Aimbot::AdvancedSpeed = Aimbot::SentinelSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::SentinelSmooth;
    		}
    		if (weaponHeld == 83) { //ChargeRifle
    			Aimbot::AdvancedSpeed = Aimbot::ChargeRifleSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::ChargeRifleSmooth;
    		}
    		if (weaponHeld == 85) { //Longbow
    			Aimbot::AdvancedSpeed = Aimbot::LongbowSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::LongbowSmooth;
    		}
    		//Legendary Weapons
    		if (weaponHeld == 109) { //Wingman
    			Aimbot::AdvancedSpeed = Aimbot::WingmanSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::WingmanSmooth;
    		}
    		if (weaponHeld == 102) { //Prowler
    			Aimbot::AdvancedSpeed = Aimbot::ProwlerSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::ProwlerSmooth;
    		}
    		if (weaponHeld == 92) { //Kraber
    			Aimbot::AdvancedSpeed = Aimbot::KraberSpeed;
    			Aimbot::AdvancedSmooth = Aimbot::KraberSmooth;
    		}
    	}

    	if (OnFire && OnADS) {
		if (!AimbotEnabled) { ReleaseTarget(); return; }

		if (Myself->IsZooming)
		    FinalDistance = ZoomDistance;
		else FinalDistance = HipfireDistance;

		if (Myself->IsHoldingGrenade) { ReleaseTarget(); return; }
		
		if (AimList.find(Myself->WeaponIndex) == AimList.end()) return;
		
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
		
		if (AimList.find(Myself->WeaponIndex) == AimList.end()) return;
		
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
        SmoothAngle(CurrentTarget, DesiredAngles);

        // Aim angles ADVANCED
        if (AdvancedAim) {
        Vector2D aimbotDelta = Vector2D(CalculatePitchIncrement(DesiredAngles), CalculateYawIncrement(DesiredAngles)).Multiply(AdvancedSpeed);
        int totalYawIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.x));
        int totalPitchIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.y * -1));

        // Move Mouse
        if (totalPitchIncrementInt == 0 && totalYawIncrementInt == 0) return;
        X11Display->MoveMouse(totalYawIncrementInt, totalPitchIncrementInt);
        }
        
        if (!AdvancedAim) {
        Vector2D aimbotDelta = Vector2D(CalculatePitchIncrement(DesiredAngles), CalculateYawIncrement(DesiredAngles)).Multiply(Speed);
        int totalYawIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.x));
        int totalPitchIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.y * -1));

        // Move Mouse
        if (totalPitchIncrementInt == 0 && totalYawIncrementInt == 0) return;
        X11Display->MoveMouse(totalYawIncrementInt, totalPitchIncrementInt);
        }
    }

    void SmoothAngle(Player* Target, QAngle& Angle) {
        QAngle ViewAngles = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
        QAngle Delta = Angle - ViewAngles;
        Delta.NormalizeAngles();
        
        if (AdvancedAim) {
        float ExtraSmooth = SmoothDistance / Target->DistanceToLocalPlayer;
        float SmoothValue = powf(this->AdvancedSmooth + ExtraSmooth, 0.4f);
        SmoothValue = std::min(0.99f, SmoothValue);
        }
        
        if (!AdvancedAim) {
        float ExtraSmooth = SmoothDistance / Target->DistanceToLocalPlayer;
        float SmoothValue = powf(this->Smooth + ExtraSmooth, 0.4f);
        SmoothValue = std::min(0.99f, SmoothValue);
        }

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
    	Vector3D TargetPosition;
    	if (!ClosestHitbox) {
    	TargetPosition = Target->GetBonePosition(Modules::Aimbot::Hitbox);
    	}
    	if (ClosestHitbox) {
    	TargetPosition = Target->GetBonePosition(static_cast<HitboxType>(GetBestBone(Target)));
    	}
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
    	if (VisCheck) {
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
    	if (!VisCheck) {
		if (target == nullptr ||
		    !target->IsValid() || 
		    !target->IsCombatReady() || 
		    !target->IsHostile || 
		    target->Distance2DToLocalPlayer < Conversion::ToGameUnits(MinDistance) || 
		    target->Distance2DToLocalPlayer > Conversion::ToGameUnits(FinalDistance))
		    return false;
		return true;
	}
    } //Ignore The Warnings

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
