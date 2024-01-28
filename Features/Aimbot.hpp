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
    bool TeamCheck = true;
    
    bool PredictMovement = true;
    bool PredictBulletDrop = true;
    float FinalDistance = 0;
    float Speed = 20;
    float Smooth = 0.9;
    float HipfireSmooth = 0.9;
    float ADSSmooth = 0.99;
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
    float AdvancedHipfireSmooth = 0.99;
    float AdvancedADSSmooth = 0.99;
    bool AdvancedFire = true;
    bool AdvancedADS = false;
            
    float P2020Speed = 10;
    float P2020HipfireSmooth = 0.99;
    float P2020ADSSmooth = 0.99;
    bool P2020Fire = true;
    bool P2020ADS = false;
    float RE45Speed = 0.99;
    float RE45HipfireSmooth = 10;
    float RE45ADSSmooth = 0.99;
    bool RE45Fire = true;
    bool RE45ADS = false;
    float AlternatorSpeed = 10;
    float AlternatorHipfireSmooth = 0.99;
    float AlternatorADSSmooth = 0.99;
    bool AlternatorFire = true;
    bool AlternatorADS = false;
    float R99Speed = 10;
    float R99HipfireSmooth = 0.99;
    float R99ADSSmooth = 0.99;
    bool R99Fire = true;
    bool R99ADS = false;
    float R301Speed = 10;
    float R301HipfireSmooth = 0.99;
    float R301ADSSmooth = 0.99;
    bool R301Fire = true;
    bool R301ADS = false;
    float SpitfireSpeed = 10;
    float SpitfireHipfireSmooth = 0.99;
    float SpitfireADSSmooth = 0.99;
    bool SpitfireFire = true;
    bool SpitfireADS = false;
    float G7Speed = 10;
    float G7HipfireSmooth = 0.99;
    float G7ADSSmooth = 0.99;
    bool G7Fire = true;
    bool G7ADS = false;
    //Heavy
    float FlatlineSpeed = 10;
    float FlatlineHipfireSmooth = 0.99;
    float FlatlineADSSmooth = 0.99;
    bool FlatlineFire = true;
    bool FlatlineADS = false;
    float HemlockSpeed = 10;
    float HemlockHipfireSmooth = 0.99;
    float HemlockADSSmooth = 0.99;
    bool HemlockFire = true;
    bool HemlockADS = false;
    float RepeaterSpeed = 10;
    float RepeaterHipfireSmooth = 0.99;
    float RepeaterADSSmooth = 0.99;
    bool RepeaterFire = true;
    bool RepeaterADS = false;
    float RampageSpeed = 10;
    float RampageHipfireSmooth = 0.99;
    float RampageADSSmooth = 0.99;
    bool RampageFire = true;
    bool RampageADS = false;
    float CARSMGSpeed = 10;
    float CARSMGHipfireSmooth = 0.99;
    float CARSMGADSSmooth = 0.99;
    bool CARSMGFire = true;
    bool CARSMGADS = false;
    //Energy
    float HavocSpeed = 10;
    float HavocHipfireSmooth = 0.99;
    float HavocADSSmooth = 0.99;
    bool HavocFire = true;
    bool HavocADS = false;
    float DevotionSpeed = 10;
    float DevotionHipfireSmooth = 0.99;
    float DevotionADSSmooth = 0.99;
    bool DevotionFire = true;
    bool DevotionADS = false;
    float LSTARSpeed = 10;
    float LSTARHipfireSmooth = 0.99;
    float LSTARADSSmooth = 0.99;
    bool LSTARFire = true;
    bool LSTARADS = false;
    float TripleTakeSpeed = 10;
    float TripleTakeHipfireSmooth = 0.99;
    float TripleTakeADSSmooth = 0.99;
    bool TripleTakeFire = true;
    bool TripleTakeADS = false;
    float VoltSpeed = 10;
    float VoltHipfireSmooth = 0.99;
    float VoltADSSmooth = 0.99;
    bool VoltFire = true;
    bool VoltADS = false;
    float NemesisSpeed = 10;
    float NemesisHipfireSmooth = 0.99;
    float NemesisADSSmooth = 0.99;
    bool NemesisFire = true;
    bool NemesisADS = false;
    //Shotguns
    float MozambiqueSpeed = 10;
    float MozambiqueHipfireSmooth = 0.99;
    float MozambiqueADSSmooth = 0.99;
    bool MozambiqueFire = true;
    bool MozambiqueADS = false;
    float EVA8Speed = 10;
    float EVA8HipfireSmooth = 0.99;
    float EVA8ADSSmooth = 0.99;
    bool EVA8Fire = true;
    bool EVA8ADS = false;
    float PeacekeeperSpeed = 10;
    float PeacekeeperHipfireSmooth = 0.99;
    float PeacekeeperADSSmooth = 0.99;
    bool PeacekeeperFire = true;
    bool PeacekeeperADS = false;
    float MastiffSpeed = 10;
    float MastiffHipfireSmooth = 0.99;
    float MastiffADSSmooth = 0.99;
    bool MastiffFire = true;
    bool MastiffADS = false;
    //Snipers
    float LongbowSpeed = 10;
    float LongbowHipfireSmooth = 0.99;
    float LongbowADSSmooth = 0.99;
    bool LongbowFire = true;
    bool LongbowADS = false;
    float ChargeRifleSpeed = 10;
    float ChargeRifleHipfireSmooth = 0.99;
    float ChargeRifleADSSmooth = 0.99;
    bool ChargeRifleFire = true;
    bool ChargeRifleADS = false;
    float SentinelSpeed = 10;
    float SentinelHipfireSmooth = 0.99;
    float SentinelADSSmooth = 0.99;
    bool SentinelFire = true;
    bool SentinelADS = false;
    //Legendary
    float WingmanSpeed = 10;
    float WingmanHipfireSmooth = 0.99;
    float WingmanADSSmooth = 0.99;
    bool WingmanFire = true;
    bool WingmanADS = false;
    float ProwlerSpeed = 10;
    float ProwlerHipfireSmooth = 0.99;
    float ProwlerADSSmooth = 0.99;
    bool ProwlerFire = true;
    bool ProwlerADS = false;
    float KraberSpeed = 10;
    float KraberHipfireSmooth = 0.99;
    float KraberADSSmooth = 0.99;
    bool KraberFire = true;
    bool KraberADS = false;
    float BocekSpeed = 10;
    float BocekHipfireSmooth = 0.99;
    float BocekADSSmooth = 0.99;
    bool BocekFire = true;
    bool BocekADS = false;
    float ThrowingKnifeSpeed = 10;
    float ThrowingKnifeHipfireSmooth = 0.99;
    float ThrowingKnifeADSSmooth = 0.99;
    bool ThrowingKnifeFire = true;
    bool ThrowingKnifeADS = false;

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
		    ImGui::SameLine();
		    ImGui::Checkbox("Team Check##Aimbot", &TeamCheck);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Disable this if doing 1v1s in the firing range.");
	   	    
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

		    	/*ImGui::SliderFloat("Smoothing", &Smooth, 0, 0.99, "%.3f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Smoothing for the Aim-Assist\nHigher = Smoother");*/
		        	
		    	ImGui::SliderFloat("Hipefire Smoothing", &HipfireSmooth, 0, 0.99, "%.3f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Smoothing for the Aim-Assist whilst hipfiring.\nHigher = Smoother");
		        	
		    	ImGui::SliderFloat("ADS Smoothing", &ADSSmooth, 0, 0.99, "%.3f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Smoothing for the Aim-Assist whilst ADS.\nHigher = Smoother");
		        	
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
		    	ImGui::SliderFloat("Hipfire Max Distance", &HipfireDistance, 1, 500, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Maximum Hipfire distance for Aim-Assist to work");
		    	ImGui::SliderFloat("Zoom Max Distance", &ZoomDistance, 1, 500, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Maximum ADS Distance for Aim-Assist to work");
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
			    		ImGui::Checkbox("On Fire?##AdvancedP2020", &P2020Fire);
			    		ImGui::SameLine();
			    		ImGui::Checkbox("On ADS?##AdvancedP2020", &P2020ADS);
			    		ImGui::SliderFloat("Speed##AdvancedP2020", &P2020Speed, 1, 100, "%.0f");
			    		if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			    			ImGui::SetTooltip("Speed Of The Aim-Assist For The P2020\nHigher = Faster");
			    		ImGui::SliderFloat("Hipfire Smoothing##AdvancedP2020", &P2020HipfireSmooth, 0, 0.99, "%.3f");
			    		if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			    			ImGui::SetTooltip("Smoothing Of The Aim-Assist For The P2020 Whilst Hipfiring.\nHigher = Smoother");
			    		ImGui::SliderFloat("ADS Smoothing##AdvancedP2020", &P2020ADSSmooth, 0, 0.99, "%.3f");
			    		if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			    			ImGui::SetTooltip("Smoothing Of The Aim-Assist For The P2020 Whilst ADS.\nHigher = Smoother");
			    	}
			    	if (RE45) {
			    			ImGui::Text("RE-45 Auto");
			    			ImGui::Checkbox("On Fire?##AdvancedP2020", &RE45Fire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedP2020", &RE45ADS);
					    	ImGui::SliderFloat("Speed##AdvancedRE45", &RE45Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The RE-45 Auto\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedRE45", &RE45HipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The RE-45 Auto Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedRE45", &RE45ADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The RE-45 Auto Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Alternator) {
			    			ImGui::Text("Alternator SMG");
			    			ImGui::Checkbox("On Fire?##AdvancedP2020", &AlternatorFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedP2020", &AlternatorADS);
					    	ImGui::SliderFloat("Speed##AdvancedAlternator", &AlternatorSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Alternator SMG\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedAlternator", &AlternatorHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Alternator SMG Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedAlternator", &AlternatorADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Alternator SMG Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (R99) {
			    			ImGui::Text("R-99 SMG");
			    			ImGui::Checkbox("On Fire?##AdvancedR99", &R99Fire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedR99", &R99ADS);
					    	ImGui::SliderFloat("Speed##AdvancedR99", &R99Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The R-99 SMG\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedR99", &R99HipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R-99 SMG Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedR99", &R99ADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R-99 SMG Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (R301) {
			    			ImGui::Text("R-301 Carbine");
			    			ImGui::Checkbox("On Fire?##AdvancedR301", &R301Fire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedR301", &R301ADS);
					    	ImGui::SliderFloat("Speed##AdvancedR301", &R301Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The R-301 Carbine\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedR301", &R301HipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R-301 Carbine Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedR301", &R301ADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R-301 Carbine Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Spitfire) {
			    			ImGui::Text("M600 Spitfire");
			    			ImGui::Checkbox("On Fire?##AdvancedSpitfire", &SpitfireFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedSpitfire", &SpitfireADS);
					    	ImGui::SliderFloat("Speed##AdvancedSpitfire", &SpitfireSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The M600 Spitfire\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedSpitfire", &SpitfireHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The M600 Spitfire Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedSpitfire", &SpitfireADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The M600 Spitfire Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (G7) {
			    			ImGui::Text("G7 Scout");
			    			ImGui::Checkbox("On Fire?##AdvancedG7", &G7Fire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedG7", &G7ADS);
					    	ImGui::SliderFloat("Speed##AdvancedG7", &G7Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The G7 Scout\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedG7", &G7HipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The G7 Scout Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedG7", &G7ADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The G7 Scout Whilst ADS.\nHigher = Smoother");
			    	}
		    	}
			    	
		    	if (ImGui::CollapsingHeader("Heavy", nullptr)) {
			    	if (Flatline) {
			    		ImGui::Text("VK-47 Flatline");
			    			ImGui::Checkbox("On Fire?##AdvancedFlatline", &FlatlineFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedFlatline", &FlatlineADS);
					    	ImGui::SliderFloat("Speed##AdvancedFlatline", &FlatlineSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The VK-47 Flatline\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedFlatline", &FlatlineHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The VK-47 Flatline Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedFlatline", &FlatlineADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The VK-47 Flatline Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Hemlock) {
			    			ImGui::Text("Hemlock Burst AR");
			    			ImGui::Checkbox("On Fire?##AdvancedHemlock", &HemlockFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedHemlock", &HemlockADS);
					    	ImGui::SliderFloat("Speed##AdvancedHemlock", &HemlockSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Hemlock Burst AR\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedHemlock", &HemlockHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Hemlock Burst AR Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedHemlock", &HemlockADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Hemlock Burst AR Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Repeater) {
			    			ImGui::Text("30-30 Repeater");
			    			ImGui::Checkbox("On Fire?##AdvancedRepeater", &RepeaterFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedRepeater", &RepeaterADS);
					    	ImGui::SliderFloat("Speed##AdvancedRepeater", &RepeaterSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The 30-30 Repeater\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedRepeater", &RepeaterHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The 30-30 Repeater Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedRepeater", &RepeaterADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The 30-30 Repeater Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Rampage) {
			    			ImGui::Text("Rampage LMG");
			    			ImGui::Checkbox("On Fire?##AdvancedRampage", &RampageFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedRampage", &RampageADS);
					    	ImGui::SliderFloat("Speed##AdvancedRampage", &RampageSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Rampage LMG\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedRampage", &RampageHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Rampage LMG Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedRampage", &RampageADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Rampage LMG Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (CARSMG) {
			    			ImGui::Text("C.A.R SMG");
			    			ImGui::Checkbox("On Fire?##AdvancedCARSMG", &CARSMGFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedCARSMG", &CARSMGADS);
					    	ImGui::SliderFloat("Speed##AdvancedCARSMG", &CARSMGSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The C.A.R SMG\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedCARSMG", &CARSMGHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The C.A.R SMG Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedCARSMG", &CARSMGADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The C.A.R SMG Whilst ADS.\nHigher = Smoother");
			    	}
		    	}
			    	
		    	if (ImGui::CollapsingHeader("Energy", nullptr)) {
			    	if (Havoc) {
			    			ImGui::Text("Havoc");
			    			ImGui::Checkbox("On Fire?##AdvancedHavoc", &HavocFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedHavoc", &HavocADS);
					    	ImGui::SliderFloat("Speed##AdvancedHavoc", &HavocSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Havoc\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedHavoc", &HavocHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Havoc Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedHavoc", &HavocADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Havoc Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Devotion) {
			    			ImGui::Text("Devotion LMG");
			    			ImGui::Checkbox("On Fire?##AdvancedDevotion", &DevotionFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedDevotion", &DevotionADS);
					    	ImGui::SliderFloat("Speed##AdvancedDevotion", &DevotionSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Devotion LMG\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedDevotion", &DevotionHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Devotion LMG Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedDevotion", &DevotionADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Devotion LMG Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (LSTAR) {
			    			ImGui::Text("L-Star EMG");
			    			ImGui::Checkbox("On Fire?##AdvancedLSTAR", &LSTARFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedLSTAR", &LSTARADS);
					    	ImGui::SliderFloat("Speed##AdvancedLSTAR", &LSTARSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The L-Star EMG\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedLSTAR", &LSTARHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The L-Star EMG Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedLSTAR", &LSTARADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The L-Star EMG Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (TripleTake) {
			    			ImGui::Text("Triple-Take");
			    			ImGui::Checkbox("On Fire?##AdvancedTripleTake", &TripleTakeFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedTripleTake", &TripleTakeADS);
					    	ImGui::SliderFloat("Speed##AdvancedTripleTake", &TripleTakeSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Triple-Take\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedTripleTake", &TripleTakeHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Triple-Take Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedTripleTake", &TripleTakeADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Triple-Take Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Volt) {
			    			ImGui::Text("Volt");
			    			ImGui::Checkbox("On Fire?##AdvancedVolt", &VoltFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedVolt", &VoltADS);
					    	ImGui::SliderFloat("Speed##AdvancedVolt", &VoltSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Volt\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedVolt", &VoltHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Volt Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedVolt", &VoltADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Volt Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Nemesis) {
			    			ImGui::Text("Nemesis Burst AR");
			    			ImGui::Checkbox("On Fire?##AdvancedNemesis", &NemesisFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedNemesis", &NemesisADS);
					    	ImGui::SliderFloat("Speed##AdvancedNemesis", &NemesisSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Nemesis Burst AR\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedNemesis", &NemesisHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Nemesis Burst AR Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedNemesis", &NemesisADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Nemesis Burst AR Whilst ADS.\nHigher = Smoother");
			    	}
		    	}
				
		    	if (ImGui::CollapsingHeader("Shotguns", nullptr)) {
			    	if (Mozambique) {
			    			ImGui::Text("Mozambique");
			    			ImGui::Checkbox("On Fire?##AdvancedMozambique", &MozambiqueFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedMozambique", &MozambiqueADS);
					    	ImGui::SliderFloat("Speed##AdvancedMozambique", &MozambiqueSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Mozambique\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedMozambique", &MozambiqueHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mozambique Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedMozambique", &MozambiqueADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mozambique Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (EVA8) {
			    			ImGui::Text("EVA-8 Auto");
			    			ImGui::Checkbox("On Fire?##AdvancedEVA8", &EVA8Fire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedEVA8", &EVA8ADS);
					    	ImGui::SliderFloat("Speed##AdvancedEVA8", &EVA8Speed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The EVA-8 Auto\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedEVA8", &EVA8HipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The EVA-8 Auto Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedEVA8", &EVA8ADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The EVA-8 Auto Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Peacekeeper) {
			    			ImGui::Text("Peacekeeper");
			    			ImGui::Checkbox("On Fire?##AdvancedPeacekeeper", &PeacekeeperFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedPeacekeeper", &PeacekeeperADS);
					    	ImGui::SliderFloat("Speed##AdvancedPeacekeeper", &PeacekeeperSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Peacekeeper\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedPeacekeeper", &PeacekeeperHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Peacekeeper Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedPeacekeeper", &PeacekeeperADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Peacekeeper Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Mastiff) {
			    			ImGui::Text("Mastiff");
			    			ImGui::Checkbox("On Fire?##AdvancedMastiff", &MastiffFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedMastiff", &MastiffADS);
					    	ImGui::SliderFloat("Speed##AdvancedMastiff", &MastiffSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Mastiff\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedMastiff", &MastiffHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mastiff Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedMastiff", &MastiffADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mastiff Whilst ADS.\nHigher = Smoother");
			    	}
		    	}
				
		    	if (ImGui::CollapsingHeader("Snipers", nullptr)) {
			    	if (Longbow) {
			    			ImGui::Text("Longbow DMR");
			    			ImGui::Checkbox("On Fire?##AdvancedLongbow", &LongbowFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedLongbow", &LongbowADS);
					    	ImGui::SliderFloat("Speed##AdvancedLongbow", &LongbowSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Longbow DMR\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedLongbow", &LongbowHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Longbow DMR Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedLongbow", &LongbowADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Longbow DMR Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (ChargeRifle) {
			    			ImGui::Text("Charge Rifle");
			    			ImGui::Checkbox("On Fire?##AdvancedChargeRifle", &ChargeRifleFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedChargeRifle", &ChargeRifleADS);
					    	ImGui::SliderFloat("Speed##AdvancedChargeRifle", &ChargeRifleSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Charge Rifle\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedChargeRifle", &ChargeRifleHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Charge Rifle Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedChargeRifle", &ChargeRifleADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Charge Rifle Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Sentinel) {
			    			ImGui::Text("Sentinel");
			    			ImGui::Checkbox("On Fire?##AdvancedSentinel", &SentinelFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedSentinel", &SentinelADS);
					    	ImGui::SliderFloat("Speed##AdvancedSentinel", &SentinelSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Sentinel\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedSentinel", &SentinelHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Sentinel Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedSentinel", &SentinelADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Sentinel Whilst ADS.\nHigher = Smoother");
			    	}
		    	}
				
		    	if (ImGui::CollapsingHeader("Legendary", nullptr)) {
			    	if (Wingman) {
			    			ImGui::Text("Wingman");
			    			ImGui::Checkbox("On Fire?##AdvancedWingman", &WingmanFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedWingman", &WingmanADS);
					    	ImGui::SliderFloat("Speed##AdvancedWingman", &WingmanSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Wingman\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedWingman", &WingmanHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Wingman Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedWingman", &WingmanADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Wingman Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Prowler) {
			    			ImGui::Text("Prowler Burst SMG");
			    			ImGui::Checkbox("On Fire?##AdvancedProwler", &ProwlerFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedProwler", &ProwlerADS);
					    	ImGui::SliderFloat("Speed##AdvancedProwler", &ProwlerSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Prowler Burst SMG\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedProwler", &ProwlerHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Prowler Burst SMG Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedProwler", &ProwlerADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Prowler Burst SMG Whilst ADS.\nHigher = Smoother");
			    	}
			    	
			    	if (Bocek) {
			    			ImGui::Text("Bocek Compound Bow");
			    			ImGui::Checkbox("On Fire?##AdvancedBocek", &BocekFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedBocek", &BocekADS);
					    	ImGui::SliderFloat("Speed##AdvancedBocek", &BocekSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Bocek Compound Bow\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedBocek", &BocekHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Bocek Compound Bow Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedBocek", &BocekADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Bocek Compound Bow Whilst ADS.\nHigher = Smoother");
			    	}
			    		
			    	if (Kraber) {
			    			ImGui::Text("Kraber .50-CAL Sniper");;
			    			ImGui::Checkbox("On Fire?##AdvancedKraber", &KraberFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedKraber", &KraberADS);
					    	ImGui::SliderFloat("Speed##AdvancedKraber", &KraberSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Kraber .50-CAL Sniper\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedKraber", &KraberHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Kraber .50-CAL Sniper Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedKraber", &KraberADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Kraber .50-CAL Sniper Whilst ADS.\nHigher = Smoother");
			    	}
			    	
			    	if (Knife) {
			    			ImGui::Text("Throwing Knife");
			    			ImGui::Checkbox("On Fire?##AdvancedKnife", &ThrowingKnifeFire);
			    			ImGui::SameLine();
			    			ImGui::Checkbox("On ADS?##AdvancedKnife", &ThrowingKnifeADS);
					    	ImGui::SliderFloat("Speed##AdvancedKnife", &ThrowingKnifeSpeed, 1, 100, "%.0f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Speed Of The Aim-Assist For The Throwing Knife\nHigher = Faster");
					    	ImGui::SliderFloat("Hipfire Smoothing##AdvancedKnife", &ThrowingKnifeHipfireSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Throwing Knife Whilst Hipfiring.\nHigher = Smoother");
					    	ImGui::SliderFloat("ADS Smoothing##AdvancedKnife", &ThrowingKnifeADSSmooth, 0, 0.99, "%.3f");
					    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Throwing Knife Whilst ADS.\nHigher = Smoother");
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
            Config::Aimbot::VisCheck = VisCheck;
            Config::Aimbot::TeamCheck = TeamCheck;
            
            Config::Aimbot::PredictMovement = PredictMovement;
            Config::Aimbot::PredictBulletDrop = PredictBulletDrop;
            Config::Aimbot::Speed = Speed;
            Config::Aimbot::Smooth = Smooth;
            Config::Aimbot::HipfireSmooth = HipfireSmooth;
            Config::Aimbot::ADSSmooth = ADSSmooth;
            Config::Aimbot::SmoothDistance = SmoothDistance;
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
            Config::Aimbot::AdvancedSpeed = AdvancedSpeed;
            Config::Aimbot::AdvancedSmooth = AdvancedSmooth;
            Config::Aimbot::AdvancedHipfireSmooth = AdvancedHipfireSmooth;
            Config::Aimbot::AdvancedADSSmooth = AdvancedADSSmooth;
            
            //Advanced Weapons
            //Light
            Config::Aimbot::P2020Fire = P2020Fire;
            Config::Aimbot::P2020ADS = P2020ADS;
            Config::Aimbot::P2020Speed = P2020Speed;
            Config::Aimbot::P2020HipfireSmooth = P2020HipfireSmooth;
            Config::Aimbot::P2020ADSSmooth = P2020ADSSmooth;
            Config::Aimbot::RE45Fire = RE45Fire;
            Config::Aimbot::RE45ADS = RE45ADS;
            Config::Aimbot::RE45Speed = RE45Speed;
            Config::Aimbot::RE45HipfireSmooth = RE45HipfireSmooth;
            Config::Aimbot::RE45ADSSmooth = RE45ADSSmooth;
            Config::Aimbot::AlternatorFire = AlternatorFire;
            Config::Aimbot::AlternatorADS = AlternatorADS;
            Config::Aimbot::AlternatorSpeed = AlternatorSpeed;
            Config::Aimbot::AlternatorHipfireSmooth = AlternatorHipfireSmooth;
            Config::Aimbot::AlternatorADSSmooth = AlternatorADSSmooth;
            Config::Aimbot::R99Fire = R99Fire;
            Config::Aimbot::R99ADS = R99ADS;
            Config::Aimbot::R99Speed = R99Speed;
            Config::Aimbot::R99HipfireSmooth = R99HipfireSmooth;
            Config::Aimbot::R99ADSSmooth = R99ADSSmooth;
            Config::Aimbot::R301Fire = R301Fire;
            Config::Aimbot::R301ADS = R301ADS;
            Config::Aimbot::R301Speed = R301Speed;
            Config::Aimbot::R301HipfireSmooth = R301HipfireSmooth;
            Config::Aimbot::R301ADSSmooth = R301ADSSmooth;
            Config::Aimbot::SpitfireFire = SpitfireFire;
            Config::Aimbot::SpitfireADS = SpitfireADS;
            Config::Aimbot::SpitfireSpeed = SpitfireSpeed;
            Config::Aimbot::SpitfireHipfireSmooth = SpitfireHipfireSmooth;
            Config::Aimbot::SpitfireADSSmooth = SpitfireADSSmooth;
            Config::Aimbot::G7Fire = G7Fire;
            Config::Aimbot::G7ADS = G7ADS;
            Config::Aimbot::G7Speed = G7Speed;
            Config::Aimbot::G7HipfireSmooth = G7HipfireSmooth;
            Config::Aimbot::G7ADSSmooth = G7ADSSmooth;
            //Heavy
            Config::Aimbot::FlatlineSpeed = FlatlineSpeed;
            Config::Aimbot::FlatlineHipfireSmooth = FlatlineHipfireSmooth;
            Config::Aimbot::FlatlineADSSmooth = FlatlineADSSmooth;
            Config::Aimbot::SpitfireFire = SpitfireFire;
            Config::Aimbot::SpitfireADS = SpitfireADS;
            Config::Aimbot::HemlockSpeed = HemlockSpeed;
            Config::Aimbot::HemlockHipfireSmooth = HemlockHipfireSmooth;
            Config::Aimbot::HemlockADSSmooth = HemlockADSSmooth;
            Config::Aimbot::SpitfireFire = SpitfireFire;
            Config::Aimbot::SpitfireADS = SpitfireADS;
            Config::Aimbot::RepeaterSpeed = RepeaterSpeed;
            Config::Aimbot::RepeaterHipfireSmooth = RepeaterHipfireSmooth;
            Config::Aimbot::RepeaterADSSmooth = RepeaterADSSmooth;
            Config::Aimbot::SpitfireFire = SpitfireFire;
            Config::Aimbot::SpitfireADS = SpitfireADS;
            Config::Aimbot::RampageSpeed = RampageSpeed;
            Config::Aimbot::RampageHipfireSmooth = RampageHipfireSmooth;
            Config::Aimbot::RampageADSSmooth = RampageADSSmooth;
            Config::Aimbot::SpitfireFire = SpitfireFire;
            Config::Aimbot::SpitfireADS = SpitfireADS;
            Config::Aimbot::CARSMGSpeed = CARSMGSpeed;
            Config::Aimbot::CARSMGHipfireSmooth = CARSMGHipfireSmooth;
            Config::Aimbot::CARSMGADSSmooth = CARSMGADSSmooth;
            Config::Aimbot::SpitfireFire = SpitfireFire;
            Config::Aimbot::SpitfireADS = SpitfireADS;
            //Energy
            Config::Aimbot::HavocSpeed = HavocSpeed;
            Config::Aimbot::HavocHipfireSmooth = HavocHipfireSmooth;
            Config::Aimbot::HavocADSSmooth = HavocADSSmooth;
            Config::Aimbot::HavocFire = HavocFire;
            Config::Aimbot::HavocADS = HavocADS;
            Config::Aimbot::DevotionSpeed = DevotionSpeed;
            Config::Aimbot::DevotionHipfireSmooth = DevotionHipfireSmooth;
            Config::Aimbot::DevotionADSSmooth = DevotionADSSmooth;
            Config::Aimbot::DevotionFire = DevotionFire;
            Config::Aimbot::DevotionADS = DevotionADS;
            Config::Aimbot::LSTARSpeed = LSTARSpeed;
            Config::Aimbot::LSTARHipfireSmooth = LSTARHipfireSmooth;
            Config::Aimbot::LSTARADSSmooth = LSTARADSSmooth;
            Config::Aimbot::LSTARFire = LSTARFire;
            Config::Aimbot::LSTARADS = LSTARADS;
            Config::Aimbot::TripleTakeSpeed = TripleTakeSpeed;
            Config::Aimbot::TripleTakeHipfireSmooth = TripleTakeHipfireSmooth;
            Config::Aimbot::TripleTakeADSSmooth = TripleTakeADSSmooth;
            Config::Aimbot::TripleTakeFire = TripleTakeFire;
            Config::Aimbot::TripleTakeADS = TripleTakeADS;
            Config::Aimbot::VoltSpeed = VoltSpeed;
            Config::Aimbot::VoltHipfireSmooth = VoltHipfireSmooth;
            Config::Aimbot::VoltADSSmooth = VoltADSSmooth;
            Config::Aimbot::VoltFire = VoltFire;
            Config::Aimbot::VoltADS = VoltADS;
            Config::Aimbot::NemesisSpeed = NemesisSpeed;
            Config::Aimbot::NemesisHipfireSmooth = NemesisHipfireSmooth;
            Config::Aimbot::NemesisADSSmooth = NemesisADSSmooth;
            Config::Aimbot::NemesisFire = NemesisFire;
            Config::Aimbot::NemesisADS = NemesisADS;
            //Shotguns
            Config::Aimbot::MozambiqueSpeed = MozambiqueSpeed;
            Config::Aimbot::MozambiqueHipfireSmooth = MozambiqueHipfireSmooth;
            Config::Aimbot::MozambiqueADSSmooth = MozambiqueADSSmooth;
            Config::Aimbot::MozambiqueFire = MozambiqueFire;
            Config::Aimbot::MozambiqueADS = MozambiqueADS;
            Config::Aimbot::EVA8Speed = EVA8Speed;
            Config::Aimbot::EVA8HipfireSmooth = EVA8HipfireSmooth;
            Config::Aimbot::EVA8ADSSmooth = EVA8ADSSmooth;
            Config::Aimbot::EVA8Fire = EVA8Fire;
            Config::Aimbot::EVA8ADS = EVA8ADS;
            Config::Aimbot::PeacekeeperSpeed = PeacekeeperSpeed;
            Config::Aimbot::PeacekeeperHipfireSmooth = PeacekeeperHipfireSmooth;
            Config::Aimbot::PeacekeeperADSSmooth = PeacekeeperADSSmooth;
            Config::Aimbot::PeacekeeperFire = PeacekeeperFire;
            Config::Aimbot::PeacekeeperADS = PeacekeeperADS;
            Config::Aimbot::MastiffSpeed = MastiffSpeed;
            Config::Aimbot::MastiffHipfireSmooth = MastiffHipfireSmooth;
            Config::Aimbot::MastiffADSSmooth = MastiffADSSmooth;
            Config::Aimbot::MastiffFire = MastiffFire;
            Config::Aimbot::MastiffADS = MastiffADS;
            //Snipers
            Config::Aimbot::LongbowSpeed = LongbowSpeed;
            Config::Aimbot::LongbowHipfireSmooth = LongbowHipfireSmooth;
            Config::Aimbot::LongbowADSSmooth = LongbowADSSmooth;
            Config::Aimbot::LongbowFire = LongbowFire;
            Config::Aimbot::LongbowADS = LongbowADS;
            Config::Aimbot::ChargeRifleSpeed = ChargeRifleSpeed;
            Config::Aimbot::ChargeRifleHipfireSmooth = ChargeRifleHipfireSmooth;
            Config::Aimbot::ChargeRifleADSSmooth = ChargeRifleADSSmooth;
            Config::Aimbot::ChargeRifleFire = ChargeRifleFire;
            Config::Aimbot::ChargeRifleADS = ChargeRifleADS;
            Config::Aimbot::SentinelSpeed = SentinelSpeed;
            Config::Aimbot::SentinelHipfireSmooth = SentinelHipfireSmooth;
            Config::Aimbot::SentinelADSSmooth = SentinelADSSmooth;
            Config::Aimbot::SentinelFire = SentinelFire;
            Config::Aimbot::SentinelADS = SentinelADS;
            //Legendary
            Config::Aimbot::WingmanSpeed = WingmanSpeed;
            Config::Aimbot::WingmanHipfireSmooth = WingmanHipfireSmooth;
            Config::Aimbot::WingmanADSSmooth = WingmanADSSmooth;
            Config::Aimbot::WingmanFire = WingmanFire;
            Config::Aimbot::WingmanADS = WingmanADS;
            Config::Aimbot::ProwlerSpeed = ProwlerSpeed;
            Config::Aimbot::ProwlerHipfireSmooth = ProwlerHipfireSmooth;
            Config::Aimbot::ProwlerADSSmooth = ProwlerADSSmooth;
            Config::Aimbot::ProwlerFire = ProwlerFire;
            Config::Aimbot::ProwlerADS = ProwlerADS;
            Config::Aimbot::BocekSpeed = BocekSpeed;
            Config::Aimbot::BocekHipfireSmooth = BocekHipfireSmooth;
            Config::Aimbot::BocekADSSmooth = BocekADSSmooth;
            Config::Aimbot::BocekFire = BocekFire;
            Config::Aimbot::BocekADS = BocekADS;
            Config::Aimbot::KraberSpeed = KraberSpeed;
            Config::Aimbot::KraberHipfireSmooth = KraberHipfireSmooth;
            Config::Aimbot::KraberADSSmooth = KraberADSSmooth;
            Config::Aimbot::KraberFire = KraberFire;
            Config::Aimbot::KraberADS = KraberADS;
            Config::Aimbot::ThrowingKnifeSpeed = ThrowingKnifeSpeed;
            Config::Aimbot::ThrowingKnifeHipfireSmooth = ThrowingKnifeHipfireSmooth;
            Config::Aimbot::ThrowingKnifeADSSmooth = ThrowingKnifeADSSmooth;
            Config::Aimbot::ThrowingKnifeFire = ThrowingKnifeFire;
            Config::Aimbot::ThrowingKnifeADS = ThrowingKnifeADS;
            
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
    			Aimbot::OnFire = Aimbot::P2020Fire;
    			Aimbot::OnADS = Aimbot::P2020ADS;
    			Aimbot::AdvancedSpeed = Aimbot::P2020Speed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::P2020HipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::P2020ADSSmooth;
    		}
    		if (weaponHeld == 81) { //RE45
    			Aimbot::OnFire = Aimbot::RE45Fire;
    			Aimbot::OnADS = Aimbot::RE45ADS;
    			Aimbot::AdvancedSpeed = Aimbot::RE45Speed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::RE45HipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::RE45ADSSmooth;
    		}
    		if (weaponHeld == 80) { //Alternator
    			Aimbot::OnFire = Aimbot::AlternatorFire;
    			Aimbot::OnADS = Aimbot::AlternatorADS;
    			Aimbot::AdvancedSpeed = Aimbot::AlternatorSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::AlternatorHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::AlternatorADSSmooth;
    		}
    		if (weaponHeld == 104) { //R99
    			Aimbot::OnFire = Aimbot::R99Fire;
    			Aimbot::OnADS = Aimbot::R99ADS;
    			Aimbot::AdvancedSpeed = Aimbot::R99Speed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::R99HipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::R99ADSSmooth;
    		}
    		if (weaponHeld == 0) { //R301
    			Aimbot::OnFire = Aimbot::R301Fire;
    			Aimbot::OnADS = Aimbot::R301ADS;
    			Aimbot::AdvancedSpeed = Aimbot::R301Speed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::R301HipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::R301ADSSmooth;
    		}
    		if (weaponHeld == 106) { //Spitfire
    			Aimbot::OnFire = Aimbot::SpitfireFire;
    			Aimbot::OnADS = Aimbot::SpitfireADS;
    			Aimbot::AdvancedSpeed = Aimbot::SpitfireSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::SpitfireHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::SpitfireADSSmooth;
    		}
    		if (weaponHeld == 89) { //G7
    			Aimbot::OnFire = Aimbot::G7Fire;
    			Aimbot::OnADS = Aimbot::G7ADS;
    			Aimbot::AdvancedSpeed = Aimbot::G7Speed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::G7HipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::G7ADSSmooth;
    		}
    		//Heavy Weapons
    		if (weaponHeld == 112) { //CARSMG
    			Aimbot::OnFire = Aimbot::CARSMGFire;
    			Aimbot::OnADS = Aimbot::CARSMGADS;
    			Aimbot::AdvancedSpeed = Aimbot::CARSMGSpeed;
    			Aimbot::AdvancedADSSmooth = Aimbot::CARSMGADSSmooth;
    		}
    		if (weaponHeld == 21) { //Rampage
    			Aimbot::OnFire = Aimbot::RampageFire;
    			Aimbot::OnADS = Aimbot::RampageADS;
    			Aimbot::AdvancedSpeed = Aimbot::RampageSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::RampageHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::RampageADSSmooth;
    		}
    		if (weaponHeld == 111) { //Repeater
    			Aimbot::OnFire = Aimbot::RepeaterFire;
    			Aimbot::OnADS = Aimbot::RepeaterADS;
    			Aimbot::AdvancedSpeed = Aimbot::RepeaterSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::RepeaterHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::RepeaterADSSmooth;
    		}
    		if (weaponHeld == 90) { //Hemlock
    			Aimbot::OnFire = Aimbot::HemlockFire;
    			Aimbot::OnADS = Aimbot::HemlockADS;
    			Aimbot::AdvancedSpeed = Aimbot::HemlockSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::HemlockHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::HemlockADSSmooth;
    		}
    		if (weaponHeld == 88) { //Flatline
    			Aimbot::OnFire = Aimbot::FlatlineFire;
    			Aimbot::OnADS = Aimbot::FlatlineADS;
    			Aimbot::AdvancedSpeed = Aimbot::FlatlineSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::FlatlineHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::FlatlineADSSmooth;
    		}
    		//Energy Weapons
    		if (weaponHeld == 113) { //Nemesis
    			Aimbot::OnFire = Aimbot::NemesisFire;
    			Aimbot::OnADS = Aimbot::NemesisADS;
    			Aimbot::AdvancedSpeed = Aimbot::NemesisSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::NemesisHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::NemesisADSSmooth;
    		}
    		if (weaponHeld == 110) { //Volt
    			Aimbot::OnFire = Aimbot::VoltFire;
    			Aimbot::OnADS = Aimbot::VoltADS;
    			Aimbot::AdvancedSpeed = Aimbot::VoltSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::VoltHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::VoltADSSmooth;
    		}
    		if (weaponHeld == 107) { //TripleTake
    			Aimbot::OnFire = Aimbot::TripleTakeFire;
    			Aimbot::OnADS = Aimbot::TripleTakeADS;
    			Aimbot::AdvancedSpeed = Aimbot::TripleTakeSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::TripleTakeHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::TripleTakeADSSmooth;
    		}
    		if (weaponHeld == 93) { //LSTAR
    			Aimbot::OnFire = Aimbot::LSTARFire;
    			Aimbot::OnADS = Aimbot::LSTARADS;
    			Aimbot::AdvancedSpeed = Aimbot::LSTARSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::LSTARHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::LSTARADSSmooth;
    		}
    		if (weaponHeld == 84) { //Devotion
    			Aimbot::OnFire = Aimbot::DevotionFire;
    			Aimbot::OnADS = Aimbot::DevotionADS;
    			Aimbot::AdvancedSpeed = Aimbot::DevotionSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::DevotionHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::DevotionADSSmooth;
    		}
    		if (weaponHeld == 86) { //Havoc
    			Aimbot::OnFire = Aimbot::HavocFire;
    			Aimbot::OnADS = Aimbot::HavocADS;
    			Aimbot::AdvancedSpeed = Aimbot::HavocSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::HavocHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::HavocADSSmooth;
    		}
    		//Shotguns
    		if (weaponHeld == 96) { //Mozambique
    			Aimbot::OnFire = Aimbot::MozambiqueFire;
    			Aimbot::OnADS = Aimbot::MozambiqueADS;
    			Aimbot::AdvancedSpeed = Aimbot::MozambiqueSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::MozambiqueHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::MozambiqueADSSmooth;
    		}
    		if (weaponHeld == 87) { //EVA8
    			Aimbot::OnFire = Aimbot::EVA8Fire;
    			Aimbot::OnADS = Aimbot::EVA8ADS;
    			Aimbot::AdvancedSpeed = Aimbot::EVA8Speed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::EVA8HipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::EVA8ADSSmooth;
    		}
    		if (weaponHeld == 103) { //Peacekeeper
    			Aimbot::OnFire = Aimbot::PeacekeeperFire;
    			Aimbot::OnADS = Aimbot::PeacekeeperADS;
    			Aimbot::AdvancedSpeed = Aimbot::PeacekeeperSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::PeacekeeperHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::PeacekeeperADSSmooth;
    		}
    		if (weaponHeld == 95) { //Mastiff
    			Aimbot::OnFire = Aimbot::MastiffFire;
    			Aimbot::OnADS = Aimbot::MastiffADS;
    			Aimbot::AdvancedSpeed = Aimbot::MastiffSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::MastiffHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::MastiffADSSmooth;
    		}
    		//Snipers
    		if (weaponHeld == 1) { //Sentinel
    			Aimbot::OnFire = Aimbot::SentinelFire;
    			Aimbot::OnADS = Aimbot::SentinelADS;
    			Aimbot::AdvancedSpeed = Aimbot::SentinelSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::SentinelHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::SentinelADSSmooth;
    		}
    		if (weaponHeld == 83) { //ChargeRifle
    			Aimbot::OnFire = Aimbot::ChargeRifleFire;
    			Aimbot::OnADS = Aimbot::ChargeRifleADS;
    			Aimbot::AdvancedSpeed = Aimbot::ChargeRifleSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::ChargeRifleHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::ChargeRifleADSSmooth;
    		}
    		if (weaponHeld == 85) { //Longbow
    			Aimbot::OnFire = Aimbot::LongbowFire;
    			Aimbot::OnADS = Aimbot::LongbowADS;
    			Aimbot::AdvancedSpeed = Aimbot::LongbowSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::LongbowHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::LongbowADSSmooth;
    		}
    		//Legendary Weapons
    		if (weaponHeld == 109) { //Wingman
    			Aimbot::OnFire = Aimbot::WingmanFire;
    			Aimbot::OnADS = Aimbot::WingmanADS;
    			Aimbot::AdvancedSpeed = Aimbot::WingmanSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::WingmanHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::WingmanADSSmooth;
    		}
    		if (weaponHeld == 102) { //Prowler
    			Aimbot::OnFire = Aimbot::ProwlerFire;
    			Aimbot::OnADS = Aimbot::ProwlerADS;
    			Aimbot::AdvancedSpeed = Aimbot::ProwlerSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::ProwlerHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::ProwlerADSSmooth;
    		}
    		if (weaponHeld == 2) { //Bocek
    			Aimbot::OnFire = Aimbot::BocekFire;
    			Aimbot::OnADS = Aimbot::BocekADS;
    			Aimbot::AdvancedSpeed = Aimbot::BocekSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::BocekHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::BocekADSSmooth;
    		}
    		if (weaponHeld == 92) { //Kraber
    			Aimbot::OnFire = Aimbot::KraberFire;
    			Aimbot::OnADS = Aimbot::KraberADS;
    			Aimbot::AdvancedSpeed = Aimbot::KraberSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::KraberHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::KraberADSSmooth;
    		}
    		if (weaponHeld == 163) { //ThrowingKnife
    			Aimbot::OnFire = Aimbot::ThrowingKnifeFire;
    			Aimbot::OnADS = Aimbot::ThrowingKnifeADS;
    			Aimbot::AdvancedSpeed = Aimbot::ThrowingKnifeSpeed;
    			Aimbot::AdvancedHipfireSmooth = Aimbot::ThrowingKnifeHipfireSmooth;
    			Aimbot::AdvancedADSSmooth = Aimbot::ThrowingKnifeADSSmooth;
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
        	if (Myself->IsZooming) {
			float ExtraSmooth = SmoothDistance / Target->DistanceToLocalPlayer;
			float SmoothValue = powf(this->AdvancedADSSmooth + ExtraSmooth, 0.4f);
			SmoothValue = std::min(0.99f, SmoothValue);
		}
        	if (!Myself->IsZooming) {
			float ExtraSmooth = SmoothDistance / Target->DistanceToLocalPlayer;
			float SmoothValue = powf(this->AdvancedHipfireSmooth + ExtraSmooth, 0.4f);
			SmoothValue = std::min(0.99f, SmoothValue);
		}
        }
        
        if (!AdvancedAim) {
		if (Myself->IsZooming) {
			Smooth = ADSSmooth;
			float ExtraSmooth = SmoothDistance / Target->DistanceToLocalPlayer;
			float SmoothValue = powf(this->Smooth + ExtraSmooth, 0.4f);
			SmoothValue = std::min(0.99f, SmoothValue);
		}
		if (!Myself->IsZooming) {
			Smooth = HipfireSmooth;
			float ExtraSmooth = SmoothDistance / Target->DistanceToLocalPlayer;
			float SmoothValue = powf(this->Smooth + ExtraSmooth, 0.4f);
			SmoothValue = std::min(0.99f, SmoothValue);
		}
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
    	if (TeamCheck) {
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
    	if (!TeamCheck) {
	    	if (VisCheck) {
			if (target == nullptr ||
			    !target->IsValid() || 
			    !target->IsCombatReady() || 
			    !target->IsVisible || 
			    target->Distance2DToLocalPlayer < Conversion::ToGameUnits(MinDistance) || 
			    target->Distance2DToLocalPlayer > Conversion::ToGameUnits(FinalDistance))
			    return false;
			return true;
		}
	    	if (!VisCheck) {
			if (target == nullptr ||
			    !target->IsValid() || 
			    !target->IsCombatReady() || 
			    target->Distance2DToLocalPlayer < Conversion::ToGameUnits(MinDistance) || 
			    target->Distance2DToLocalPlayer > Conversion::ToGameUnits(FinalDistance))
			    return false;
			return true;
		}
	    } //Ignore The Warnings
    } //Ignore The Warnings!!!
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
