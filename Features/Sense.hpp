#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/GlowMode.hpp"
#include "../Core/Camera.hpp"
#include "../Core/Level.hpp"

#include "../Features/Aimbot.hpp"

#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/Color.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/HitboxType.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Geometry
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI / 180.f) )
#define ABS(x)  ((x <0) ? (-x) : (x))

struct Sense {
    //Drawings
    bool VisibilityCheck = false;
    bool DrawBox = true;
    bool DrawFilledBox = false;
    float BoxThickness = 1.0;
    bool Skeleton = true;
    float SkeletonThickness = 1.0;
    bool HealthBar = true;
    bool ShieldBar = true;
    float BarThickness = 2.0;
    float ESPMaxDistance = 200;
    bool ShowNear = true;
    bool DrawSeer = true;
    bool DrawStatus = true;
    bool DrawWeapon = false;
    bool WeaponColorType = false;
    bool ShowLegend = false;
    bool ShowMaxStatusValues = true;
    
    bool DrawDistance = true;
    bool DrawFOVCircle = true;
    bool DrawFilledFOVCircle = false;
    float FOVThickness = 1.0;
    bool DrawNames = true;
    int TracerPosition = 0;
    int TracerBone = 0;
    bool DrawTracers = true;
    float TracerThickness = 2.0;
    bool ShowSpectators = true;
    bool DrawCrosshair = true;
    float CrosshairSize = 7.0;
    float CrosshairThickness = 1.0;
    
    //Settings
    float GameFOV = 120;
    bool ShowTeam = false;
    bool TeamNames = false;
    
    float InvisibleBoxColor[4] = { 0.99, 0, 0, 0.99 };
    float VisibleBoxColor[4] = { 0, 0.99, 0, 0.99 };
    float InvisibleFilledBoxColor[4] = { 0, 0, 0, 0.11 };
    float VisibleFilledBoxColor[4] = { 0, 0, 0, 0.11 };
    float InvisibleTracerColor[4] = { 0.99, 0, 0, 0.99 };
    float VisibleTracerColor[4] = { 0, 0.99, 0, 0.99 };
    float InvisibleSkeletonColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float VisibleSkeletonColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float InvisibleNameColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float VisibleNameColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float InvisibleDistanceColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float VisibleDistanceColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float FOVColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float FilledFOVColor[4] = { 0, 0, 0, 0.11 };
    float WeaponColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float NearColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float TeamColor[4] = { 0, 0.99, 0.99, 0.99 };
    float TeamNameColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float CrosshairColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    //WeaponESP Colors
    float LightWeaponColor[4] = { 0.990, 0.768, 0.039, 0.99 };
    float HeavyWeaponColor[4] = { 0.00990, 0.990, 0.761 };
    float EnergyWeaponColor[4] = { 0, 0.99, 0, 0.99 };
    float ShotgunWeaponColor[4] = { 0.99, 0, 0, 0.99 };
    float SniperWeaponColor[4] = { 0.00990, 0.337, 0.990, 0.99 };
    float LegendaryWeaponColor[4] = { 0.99, 0.530, 0.945 };
    float MeleeWeaponColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    float ThrowableWeaponColor[4] = { 0.990, 0.974, 0.0495, 0.99 };

    // Variables
    Camera* GameCamera;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;
    std::chrono::milliseconds LastUpdateTime;
    int TotalSpectators = 0;
    std::vector<std::string> Spectators;
    Level* Map;

    Sense(Level* Map, std::vector<Player*>* Players, Camera* GameCamera, LocalPlayer* Myself) {
        this->Players = Players;
        this->GameCamera = GameCamera;
        this->Map = Map;
        this->Myself = Myself;
    }


    void RenderUI() {
    	if (Config::Home::Layout == 1 or Config::Home::Layout == 0) { //Removed the choice of having two menus. OR is for people still using old configs.
		if (ImGui::BeginTabItem("ESP", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		    // Drawings
		    ImGui::Text("ESP");
		    
		    if (ImGui::CollapsingHeader("Checks", nullptr)) {
		    	ImGui::Checkbox("Visibility Check", &VisibilityCheck);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draw's ESP ONLY on visible players");
		        ImGui::Checkbox("Show Team", &ShowTeam);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draw's ESP on Teammates");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Color##ESPTeam", TeamColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the color of teammates\nRecomended: Blue");
		        
		        ImGui::Checkbox("Show Team Names", &TeamNames);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draw Name ESP on Teammates");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Color##ESPTeamName", TeamNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the color of teammate's names\nRecomended: White");
		    }
		    
		    ImGui::Separator();

		    if (ImGui::CollapsingHeader("Boxes", nullptr)) {
			    ImGui::Checkbox("Draw Box", &DrawBox);
			    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Drawbox on enemy");
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Visible Color##ESPBox", VisibleBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Invisible Color##ESPBox", InvisibleBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			    ImGui::Checkbox("Draw Filled Box", &DrawFilledBox);
			    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Draw a Filled box on enemy");
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Visible Color##ESPFilledBox", VisibleFilledBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Invisible Color##ESPFilledBox", InvisibleFilledBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			    ImGui::SliderFloat("Box Thickness", &BoxThickness, 1, 10, "%.0f");
			    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Changes the thickness of the boxes");
		    }
		    
		    ImGui::Separator();
		    
		    if (ImGui::CollapsingHeader("Tracers", nullptr)) {
			    ImGui::Checkbox("Draw Tracers", &DrawTracers);
			    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Draw lines to enemies");
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Visible Color##ESPTracer", VisibleTracerColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Invisible Color##ESPTracer", InvisibleTracerColor, ImGuiColorEditFlags_NoInputs);
			    const char* TracerPos[] = {"Top", "Crosshair", "Bottom"};
			    ImGui::Combo("Tracer Position", &TracerPosition, TracerPos, IM_ARRAYSIZE(TracerPos));
			    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			    	ImGui::SetTooltip("Where tracers will be drawn from.");
			    Config::Sense::TracerPos = TracerPosition;
			    const char* TracerBones[] = {"Top", "Bottom"};
			    ImGui::Combo("Tracer Bone", &TracerBone, TracerBones, IM_ARRAYSIZE(TracerBones));
			    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			    	ImGui::SetTooltip("Where tracers will be drawn to.");
			    Config::Sense::TracerBone = TracerBone;
			    ImGui::SliderFloat("Tracer Thickness", &TracerThickness, 1, 10, "%.0f");
			    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			    	ImGui::SetTooltip("Changes the thickness of the tracers");
		    }
		    
		    ImGui::Separator();
		    
		    if (ImGui::CollapsingHeader("Skeleton", nullptr)) {
		    	ImGui::Checkbox("Draw Skeleton", &Skeleton);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draw the enemies skeletons (Spooky)");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Visible Color##ESPSkeleton", VisibleSkeletonColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPSkeleton", InvisibleSkeletonColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SliderFloat("Skeleton Thickness", &SkeletonThickness, 1, 10, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the thickness of the bones");	
		    }
		    
		    ImGui::Separator();
		    
		    if (ImGui::CollapsingHeader("Player Info", nullptr)) {
		    
		        ImGui::Checkbox("Draw Seer", &DrawSeer);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draw Seer's abilitiy (Show Health & Armor) on enemies");
		        	
		        ImGui::Separator();
		        	
		    	ImGui::Checkbox("Draw Status", &DrawStatus);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    		ImGui::SetTooltip("Draw enemies current health and armor");
		    	ImGui::SameLine();
		    	ImGui::Checkbox("Show Max Values", &ShowMaxStatusValues);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    		ImGui::SetTooltip("Adds their max health and armor at the end.");
		    		
		    	ImGui::Separator();
		    		
		    	ImGui::Checkbox("Draw Health Bar", &HealthBar);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    		ImGui::SetTooltip("Draw enemies current health as a bar");
		    	ImGui::SameLine();
		    	ImGui::Checkbox("Draw Shield Bar", &ShieldBar);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    		ImGui::SetTooltip("Draw enemies current shield as a bar");
			ImGui::SliderFloat("Bar Thickness", &BarThickness, 1, 10, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    		ImGui::SetTooltip("Thickness of the health/shield bar");
		    		
		    	ImGui::Separator();
		    		
		    	ImGui::Checkbox("Draw Legend", &ShowLegend);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    		ImGui::SetTooltip("Show What Legend The Enemy Is Playing As.");
		    		
		    	ImGui::Separator();
		    		
		        ImGui::Checkbox("Draw Weapon", &DrawWeapon);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Show what weapon an enemy is currently holding.");
		        ImGui::SameLine();
		        ImGui::Checkbox("Multiple Weapon Colors", &WeaponColorType);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes The Weapon Text Color To The Ammo Type Of The Weapon.");
		        if (!WeaponColorType) {
		        	ImGui::SameLine();
		        	ImGui::ColorEdit4("Color##ESPWeapon", WeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        }
		        if(WeaponColorType) {
				ImGui::Text("Weapon ESP Colors");
				ImGui::ColorEdit4("Light##ESPWeaponColor", LightWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Heavy##ESPWeaponColor", HeavyWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Energy##ESPWeaponColor", EnergyWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Shotguns##ESPWeaponColor", ShotgunWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				//ImGui::SameLine();
				ImGui::ColorEdit4("Snipers##ESPWeaponColor", SniperWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Legendary##ESPWeaponColor", LegendaryWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Throwables##ESPWeapon", ThrowableWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Melee##ESPWeapon", MeleeWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        }
		        
		        ImGui::Separator();
		    
		        ImGui::Checkbox("Draw Names", &DrawNames);
		        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			        ImGui::SetTooltip("Show enemies names");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Visible Color##ESPNames", VisibleNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPNames", InvisibleNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        
		        ImGui::Separator();
		        
		        ImGui::Checkbox("Draw Distance", &DrawDistance);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Show how far away the enemies are");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Visible Color##ESPDistance", VisibleDistanceColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPDistance", InvisibleDistanceColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);

			ImGui::Separator();

		        ImGui::Checkbox("Show Enemy Count Near", &ShowNear);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Show how many enemies are near");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Color##ESPNear", NearColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    }
		    
		    ImGui::Separator();
		        	
		    if (ImGui::CollapsingHeader("FOV Settings", nullptr)) {
		    ImGui::Checkbox("Draw FOV Circle", &DrawFOVCircle);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Draw FOV Circle.\nDoes Not Work If Aimbot Mode == Grinder.");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Color##ESPFOV", FOVColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::Checkbox("Draw Filled FOV Circle", &DrawFilledFOVCircle);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Draw a Filled FOV Circle");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Color##ESPFilledFOV", FilledFOVColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::SliderFloat("FOV Circle Thickness", &FOVThickness, 1, 10, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Changes the FOV Circle's thickness\n Recomended: 1-2");
		    ImGui::SliderFloat("Game's FOV", &GameFOV, 70, 120, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Your current FOV in Settings");
		    }

		    ImGui::Separator();
		    
		    if (ImGui::CollapsingHeader("Crosshair Settings", nullptr)) {
		    	ImGui::Checkbox("Draw Crosshair", &DrawCrosshair);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draws a crosshair");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Color##ESPCrosshair", CrosshairColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    	ImGui::SliderFloat("Crosshair Size", &CrosshairSize, 0, 1000, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the size of the crosshair");
		        ImGui::SliderFloat("Crosshair Thickness", &CrosshairThickness, 1, 50, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the Crosshair's thickness");
		    }
		    
		    ImGui::Separator();
		    
		    ImGui::Text("Misc");
		    ImGui::Checkbox("Show Spectators", &ShowSpectators);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Show spectators\n[!] Cheat/Game will crash after going back to lobby, waiting for fix.");
		        
		    ImGui::Separator();
		        
		    //Sense Settings
		    ImGui::Text("Sense Settings");
		    ImGui::SliderFloat("ESP Max Distance", &ESPMaxDistance, 0, 1000, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Only those in range will ESP");

		    ImGui::EndTabItem();
		}
	}
    }
    
    bool Save() {
        try {
            Config::Sense::VisibilityCheck = VisibilityCheck;
            Config::Sense::DrawSeer = DrawSeer;
            Config::Sense::DrawStatus = DrawStatus;
            Config::Sense::ShowMaxStatusValues = ShowMaxStatusValues;
            Config::Sense::ShowSpectators = ShowSpectators;
            Config::Sense::DrawFOVCircle = DrawFOVCircle;
            Config::Sense::DrawFilledFOVCircle = DrawFilledFOVCircle;
            Config::Sense::GameFOV = GameFOV;
            Config::Sense::DrawBox = DrawBox;
            Config::Sense::DrawFilledBox = DrawFilledBox;
            Config::Sense::BoxThickness = BoxThickness;
            Config::Sense::Skeleton = Skeleton;
            Config::Sense::SkeletonThickness = SkeletonThickness;
            Config::Sense::ESPMaxDistance = ESPMaxDistance;
            Config::Sense::ShowNear = ShowNear;
            Config::Sense::DrawNames = DrawNames;
            Config::Sense::DrawDistance = DrawDistance;
            Config::Sense::DrawCrosshair = DrawCrosshair;
            Config::Sense::CrosshairSize = CrosshairSize;
            Config::Sense::CrosshairThickness = CrosshairThickness;
            Config::Sense::ShowTeam = ShowTeam;
            Config::Sense::ShowTeam = TeamNames;
            Config::Sense::DrawTracers = DrawTracers;
            Config::Sense::ShowLegend = ShowLegend;
            Config::Sense::DrawWeapon = DrawWeapon;
            Config::Sense::WeaponColorType = WeaponColorType;
            Config::Sense::TracerThickness = TracerThickness;
            Config::Sense::TracerPos = TracerPosition;
            Config::Sense::TracerBone = TracerBone;
            
            //Colors
	    Config::Sense::InvisibleBoxColorR = InvisibleBoxColor[0];
	    Config::Sense::InvisibleBoxColorG = InvisibleBoxColor[1];
	    Config::Sense::InvisibleBoxColorB = InvisibleBoxColor[2];
	    Config::Sense::InvisibleBoxColorA = InvisibleBoxColor[3];
	    Config::Sense::VisibleBoxColorR = VisibleBoxColor[0];
	    Config::Sense::VisibleBoxColorG = VisibleBoxColor[1];
	    Config::Sense::VisibleBoxColorB = VisibleBoxColor[2];
	    Config::Sense::VisibleBoxColorA = VisibleBoxColor[3];
	    Config::Sense::InvisibleFilledBoxColorR = InvisibleFilledBoxColor[0];
	    Config::Sense::InvisibleFilledBoxColorG = InvisibleFilledBoxColor[1];
	    Config::Sense::InvisibleFilledBoxColorB = InvisibleFilledBoxColor[2];
	    Config::Sense::InvisibleFilledBoxColorA = InvisibleFilledBoxColor[3];
	    Config::Sense::VisibleFilledBoxColorR = VisibleFilledBoxColor[0];
	    Config::Sense::VisibleFilledBoxColorG = VisibleFilledBoxColor[1];
	    Config::Sense::VisibleFilledBoxColorB = VisibleFilledBoxColor[2];
	    Config::Sense::VisibleFilledBoxColorA = VisibleFilledBoxColor[3];
	    Config::Sense::InvisibleTracerColorR = InvisibleTracerColor[0];
	    Config::Sense::InvisibleTracerColorG = InvisibleTracerColor[1];
	    Config::Sense::InvisibleTracerColorB = InvisibleTracerColor[2];
	    Config::Sense::InvisibleTracerColorA = InvisibleTracerColor[3];
	    Config::Sense::VisibleTracerColorR = VisibleTracerColor[0];
	    Config::Sense::VisibleTracerColorG = VisibleTracerColor[1];
	    Config::Sense::VisibleTracerColorB = VisibleTracerColor[2];
	    Config::Sense::VisibleTracerColorA = VisibleTracerColor[3];
	    Config::Sense::InvisibleSkeletonColorR = InvisibleSkeletonColor[0];
	    Config::Sense::InvisibleSkeletonColorG = InvisibleSkeletonColor[1];
	    Config::Sense::InvisibleSkeletonColorB = InvisibleSkeletonColor[2];
	    Config::Sense::InvisibleSkeletonColorA = InvisibleSkeletonColor[3];
	    Config::Sense::VisibleSkeletonColorR = VisibleSkeletonColor[0];
	    Config::Sense::VisibleSkeletonColorG = VisibleSkeletonColor[1];
	    Config::Sense::VisibleSkeletonColorB = VisibleSkeletonColor[2];
	    Config::Sense::VisibleSkeletonColorA = VisibleSkeletonColor[3];
	    Config::Sense::InvisibleNameColorR = InvisibleNameColor[0];
	    Config::Sense::InvisibleNameColorG = InvisibleNameColor[1];
	    Config::Sense::InvisibleNameColorB = InvisibleNameColor[2];
	    Config::Sense::InvisibleNameColorA = InvisibleNameColor[3];
	    Config::Sense::VisibleNameColorR = VisibleNameColor[0];
	    Config::Sense::VisibleNameColorG = VisibleNameColor[1];
	    Config::Sense::VisibleNameColorB = VisibleNameColor[2];
	    Config::Sense::VisibleNameColorA = VisibleNameColor[3];
	    Config::Sense::InvisibleDistanceColorR = InvisibleDistanceColor[0];
	    Config::Sense::InvisibleDistanceColorG = InvisibleDistanceColor[1];
	    Config::Sense::InvisibleDistanceColorB = InvisibleDistanceColor[2];
	    Config::Sense::InvisibleDistanceColorA = InvisibleDistanceColor[3];
	    Config::Sense::VisibleDistanceColorR = VisibleDistanceColor[0];
	    Config::Sense::VisibleDistanceColorG = VisibleDistanceColor[1];
	    Config::Sense::VisibleDistanceColorB = VisibleDistanceColor[2];
	    Config::Sense::VisibleDistanceColorA = VisibleDistanceColor[3];
	    Config::Sense::FOVColorR = FOVColor[0];
	    Config::Sense::FOVColorG = FOVColor[1];
	    Config::Sense::FOVColorB = FOVColor[2];
	    Config::Sense::FOVColorA = FOVColor[3];
	    Config::Sense::FilledFOVColorR = FilledFOVColor[0];
	    Config::Sense::FilledFOVColorG = FilledFOVColor[1];
	    Config::Sense::FilledFOVColorB = FilledFOVColor[2];
	    Config::Sense::FilledFOVColorA = FilledFOVColor[3];
	    Config::Sense::WeaponColorR = WeaponColor[0];
	    Config::Sense::WeaponColorG = WeaponColor[1];
	    Config::Sense::WeaponColorB = WeaponColor[2];
	    Config::Sense::WeaponColorA = WeaponColor[3];
	    Config::Sense::NearColorR = NearColor[0];
	    Config::Sense::NearColorG = NearColor[1];
	    Config::Sense::NearColorB = NearColor[2];
	    Config::Sense::NearColorA = NearColor[3];
	    Config::Sense::TeamColorR = TeamColor[0];
	    Config::Sense::TeamColorG = TeamColor[1];
	    Config::Sense::TeamColorB = TeamColor[2];
	    Config::Sense::TeamColorA = TeamColor[3];
	    Config::Sense::TeamNameColorR = TeamNameColor[0];
	    Config::Sense::TeamNameColorG = TeamNameColor[1];
	    Config::Sense::TeamNameColorB = TeamNameColor[2];
	    Config::Sense::TeamNameColorA = TeamNameColor[3];
	    Config::Sense::CrosshairColorR = CrosshairColor[0];
	    Config::Sense::CrosshairColorG = CrosshairColor[1];
	    Config::Sense::CrosshairColorB = CrosshairColor[2];
	    Config::Sense::CrosshairColorA = CrosshairColor[3];
	    //Weapon Colors
	    Config::Sense::LightWeaponColorR = LightWeaponColor[0];
	    Config::Sense::LightWeaponColorG = LightWeaponColor[1];
	    Config::Sense::LightWeaponColorB = LightWeaponColor[2];
	    Config::Sense::LightWeaponColorA = LightWeaponColor[3];
	    Config::Sense::HeavyWeaponColorR = HeavyWeaponColor[0];
	    Config::Sense::HeavyWeaponColorG = HeavyWeaponColor[1];
	    Config::Sense::HeavyWeaponColorB = HeavyWeaponColor[2];
	    Config::Sense::HeavyWeaponColorA = HeavyWeaponColor[3];
	    Config::Sense::EnergyWeaponColorR = EnergyWeaponColor[0];
	    Config::Sense::EnergyWeaponColorG = EnergyWeaponColor[1];
	    Config::Sense::EnergyWeaponColorB = EnergyWeaponColor[2];
	    Config::Sense::EnergyWeaponColorA = EnergyWeaponColor[3];
	    Config::Sense::ShotgunWeaponColorR = ShotgunWeaponColor[0];
	    Config::Sense::ShotgunWeaponColorG = ShotgunWeaponColor[1];
	    Config::Sense::ShotgunWeaponColorB = ShotgunWeaponColor[2];
	    Config::Sense::ShotgunWeaponColorA = ShotgunWeaponColor[3];
	    Config::Sense::SniperWeaponColorR = SniperWeaponColor[0];
	    Config::Sense::SniperWeaponColorG = SniperWeaponColor[1];
	    Config::Sense::SniperWeaponColorB = SniperWeaponColor[2];
	    Config::Sense::SniperWeaponColorA = SniperWeaponColor[3];
	    Config::Sense::LegendaryWeaponColorR = LegendaryWeaponColor[0];
	    Config::Sense::LegendaryWeaponColorG = LegendaryWeaponColor[1];
	    Config::Sense::LegendaryWeaponColorB = LegendaryWeaponColor[2];
	    Config::Sense::LegendaryWeaponColorA = LegendaryWeaponColor[3];
	    Config::Sense::MeleeWeaponColorR = MeleeWeaponColor[0];
	    Config::Sense::MeleeWeaponColorG = MeleeWeaponColor[1];
	    Config::Sense::MeleeWeaponColorB = MeleeWeaponColor[2];
	    Config::Sense::MeleeWeaponColorA = MeleeWeaponColor[3];
	    Config::Sense::ThrowableWeaponColorR = ThrowableWeaponColor[0];
	    Config::Sense::ThrowableWeaponColorG = ThrowableWeaponColor[1];
	    Config::Sense::ThrowableWeaponColorB = ThrowableWeaponColor[2];
	    Config::Sense::ThrowableWeaponColorA = ThrowableWeaponColor[3];
            
            return true;
        } catch (...) {
            return false;
        }
    }

    void RenderDrawings(ImDrawList *Canvas, Aimbot *AimAssistState, LocalPlayer *Myself, Overlay OverlayWindow)
    {
        int ScreenWidth;
        int ScreenHeight;
        OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
        
	/*bool GetWeaponID = true; //For finding weapon IDs (Local Player) DONT USE WITH SHOW SPECTATORS
	if (GetWeaponID) {
		if (!Myself->IsDead) {
				
		ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
                ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
                ImGui::SetNextWindowBgAlpha(0.3f);
		ImGui::Begin("Current Weapon ID", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
					
		std::stringstream LocalwepID;
		LocalwepID << Myself->WeaponIndex;
		std::string LocalwepInt = LocalwepID.str() + " ";
		const char* LocalwepText = (char*)LocalwepInt.c_str();
		
            	ImGui::Text("Current ID: ");
            	ImGui::SameLine();
            	ImGui::Text(LocalwepText);
            	ImGui::End();
		}
	}*/
        if(!Map->IsPlayable) return;
        if (ShowSpectators)
        {
            ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
            ImGui::SetNextWindowBgAlpha(0.3f);
            ImGui::Begin("Spectators", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
 
            std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            if (Now >= LastUpdateTime + std::chrono::milliseconds(1500))
            {
                int TempTotalSpectators = 0;
                std::vector<std::string> TempSpectators;
 
                for (int i = 0; i < Players->size(); i++)
                {
                    Player *p = Players->at(i);
                    if (p->BasePointer == Myself->BasePointer)
                        continue;
                    if (p->GetViewYaw() == Myself->ViewYaw && p->IsDead)
                    {
                        TempTotalSpectators++;
                        TempSpectators.push_back(p->GetPlayerName());
                    }
                }
 
                TotalSpectators = TempTotalSpectators;
                Spectators = TempSpectators;
                LastUpdateTime = Now;
            }
            ImGui::Text("Spectators: ");
            ImGui::SameLine();
            ImGui::TextColored(TotalSpectators > 0 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1), "%d", TotalSpectators);
            if (static_cast<int>(Spectators.size()) > 0)
            {
                ImGui::Separator();
                for (int i = 0; i < static_cast<int>(Spectators.size()); i++)
                {
                    ImGui::TextColored(ImVec4(1, 0.343, 0.475, 1), "> %s", Spectators.at(i).c_str());
                }
            }
            ImGui::End();
        }
        
        // Draw Crosshair
        if (DrawCrosshair) {
        	int x = (int)(ScreenWidth * 0.5f);
        	int y = (int)(ScreenHeight * 0.5f);
        	Renderer::DrawLine(Canvas, Vector2D(x - CrosshairSize, y), Vector2D(x + CrosshairSize, y), CrosshairThickness, ImColor(CrosshairColor[0], CrosshairColor[1], CrosshairColor[2], CrosshairColor[3])); //Left - right
        	Renderer::DrawLine(Canvas, Vector2D(x, y - CrosshairSize), Vector2D(x, y + CrosshairSize), CrosshairThickness, ImColor(CrosshairColor[0], CrosshairColor[1], CrosshairColor[2], CrosshairColor[3])); //Top - bottom
        }
 
        // Draw FOV Circle
        if (DrawFOVCircle && !AimAssistState->AimbotMode == 1 && Myself->IsCombatReady())
        {
            float FOV = std::min(AimAssistState->FOV, AimAssistState->FOV * (AimAssistState->GetFOVScale() * AimAssistState->ZoomScale));
            float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(GameFOV) / 2) * ScreenWidth;
            Renderer::DrawCircle(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(FOVColor[0], FOVColor[1], FOVColor[2] ,FOVColor[3]), FOVThickness);
        }
        
        // Draw Filled FOV Circle
        if (DrawFilledFOVCircle && !AimAssistState->AimbotMode == 1 && Myself->IsCombatReady())
        {
            float FOV = std::min(AimAssistState->FOV, AimAssistState->FOV * (AimAssistState->GetFOVScale() * AimAssistState->ZoomScale));
            float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(GameFOV) / 2) * ScreenWidth;
            Renderer::DrawCircleFilled(Canvas, Vector2D(ScreenWidth /2, ScreenHeight / 2), Radius, 40, ImColor(FilledFOVColor[0], FilledFOVColor[1], FilledFOVColor[2], FilledFOVColor[3]));
        }
 
        // Draw lot of things
        int PlayersNear = 0;
        for (int i = 0; i < Players->size(); i++)
        {
            Player *p = Players->at(i);
            
	    if (!p->IsLocal && p->IsCombatReady() && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(ESPMaxDistance))) {
 	    	if (!VisibilityCheck) { //Always shows esp
 	    		PlayersNear++;
		    	if (DrawTracers) {
				//Tracers
				Vector2D chestScreenPosition;
				if (Config::Sense::TracerBone == 0) {
				    GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 66)), chestScreenPosition);
				}
				else if (Config::Sense::TracerBone == 1) {
				    GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), chestScreenPosition);
				}
				
				if (DrawTracers && Config::Sense::TracerPos == 0) //top to head
				{
				    if (!chestScreenPosition.IsZeroVector())
				    {
				        int x = (int)(ScreenWidth * 0.5f);
				        
				        if (!ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
						}
				        	if (p->IsHostile & !p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor[0], InvisibleTracerColor[1], InvisibleTracerColor[2], InvisibleTracerColor[3]));
						}
					}
					
					if (ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
						}
				        	if (p->IsHostile & !p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor[0], InvisibleTracerColor[1], InvisibleTracerColor[2], InvisibleTracerColor[3]));
						}
						
						if (p->IsAlly) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						}
					}
				    }
				}
				
				else if (DrawTracers && Config::Sense::TracerPos == 1) //middle to bottom
				{
				    if (!chestScreenPosition.IsZeroVector())
				    {
				        int x = (int)(ScreenWidth * 0.5f);
				        
				        if (!ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
				        	}
				        	if (p->IsHostile & !p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor[0], InvisibleTracerColor[1], InvisibleTracerColor[2], InvisibleTracerColor[3]));
				        	}
				        }
				        
				        if (ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
				        	}
				        	if (p->IsHostile & !p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor[0], InvisibleTracerColor[1], InvisibleTracerColor[2], InvisibleTracerColor[3]));
				        	}
				    		
				    		if (p->IsAlly) {
				    			Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
				    		}
				    	}
				    }
				}
				
				else if (DrawTracers && Config::Sense::TracerPos == 2) //bottom to bottom
				{
				    if (!chestScreenPosition.IsZeroVector())
				    {
				        int x = (int)(ScreenWidth * 0.5f);
				        
				        if (!ShowTeam) {
						if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
				    		}
						if (p->IsHostile & !p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor[0], InvisibleTracerColor[1], InvisibleTracerColor[2], InvisibleTracerColor[3]));
				    		}
					}
					
					if (ShowTeam) {
						if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
				    		}
						if (p->IsHostile & !p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor[0], InvisibleTracerColor[1], InvisibleTracerColor[2], InvisibleTracerColor[3]));
				    		}
				    		
				    		if (p->IsAlly) {
				    			Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
			    			}
			    		}
			    	    }
			    	}
			}
			    
			//Show Legend
			if (ShowLegend) {
				if (p->IsHostile && !p->IsDummy()) {
					Vector2D Head;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head).Add(Vector3D(0, 0, 33)), Head);
					
					Renderer::DrawText(Canvas, Head.Subtract(Vector2D(0,8)), p->getPlayerModelName().c_str(), ImColor(255, 255, 255), true, true, false);
				
				}
			}

			// Distance
			if (DrawDistance) {
				Vector2D distanceScreenPosition;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head).Add(Vector3D(0, 0, 80)), distanceScreenPosition);
				
				if (ShowTeam) {
					if (!distanceScreenPosition.IsZeroVector()) {
						if (p->IsAlly) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(255, 255, 255), true, true, false);
						}
						if (p->IsHostile && p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor[0], VisibleDistanceColor[1], VisibleDistanceColor[2], VisibleDistanceColor[3]), true, true, false);
						}
						if (p->IsHostile && !p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(InvisibleDistanceColor[0], InvisibleDistanceColor[1], InvisibleDistanceColor[2], InvisibleDistanceColor[3]), true, true, false);
						}
					}
				}
				if (!ShowTeam) {
					if (!distanceScreenPosition.IsZeroVector()) {
						if (p->IsHostile && p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor[0], VisibleDistanceColor[1], VisibleDistanceColor[2], VisibleDistanceColor[3]), true, true, false);
						}
						if (p->IsHostile && !p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(InvisibleDistanceColor[0], InvisibleDistanceColor[1], InvisibleDistanceColor[2], InvisibleDistanceColor[3]), true, true, false);
						}
					}
				}
			}
			
			// Draw Names
			if (DrawNames) {
				Vector2D nameScreenPosition;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head).Add(Vector3D(0, 0, 60)), nameScreenPosition);
				if (p->IsHostile && p->IsVisible && !p->IsDummy()) {
					Renderer::DrawText(Canvas, nameScreenPosition.Subtract(Vector2D(0, 0)), p->GetPlayerName().c_str(), ImColor(VisibleNameColor[0], VisibleNameColor[1], VisibleNameColor[2], VisibleNameColor[3]), true, true, false);
				}
				if (p->IsHostile && !p->IsVisible && !p->IsDummy()) {
					Renderer::DrawText(Canvas, nameScreenPosition.Subtract(Vector2D(0, 0)), p->GetPlayerName().c_str(), ImColor(InvisibleNameColor[0], InvisibleNameColor[1], InvisibleNameColor[2], InvisibleNameColor[3]), true, true, false);
				}
				    
				// Draw Team Names
				if (ShowTeam && TeamNames && p->IsAlly && !p->IsDummy()) {
					Renderer::DrawText(Canvas, nameScreenPosition.Add(Vector2D(0, 0)), p->GetPlayerName().c_str(), ImColor(TeamNameColor[0], TeamNameColor[1], TeamNameColor[2], TeamNameColor[3]), true, true, false);
				}
			}
			
			// Draw Weapon
			if (DrawWeapon) {
				if (p->IsHostile) {
					Vector2D wepScreenPosition;
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), wepScreenPosition);
					
					int weaponHeldID;
					weaponHeldID = p->WeaponIndex;
					const char* weaponHeldText;

					ImColor weaponHeldColor;
					weaponHeldColor = ImColor(255, 255, 255);
					
					if (DrawWeapon) {
				    		//Light Weapons
				    		if (weaponHeldID == 105) { //P2020
				    			weaponHeldText = "P2020";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 81) { //RE-45
				    			weaponHeldText = "RE-45";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 80) { //Alternator
				    			weaponHeldText = "Alternator";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 104) { //R-99
				    			weaponHeldText = "R-99";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 0) { //R-301
				    			weaponHeldText = "R-301";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 106) { //Spitfire
				    			weaponHeldText = "Spitfire";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 89) { //G7
				    			weaponHeldText = "G7 Scout";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		//Heavy Weapons
				    		if (weaponHeldID == 112) { //CARSMG
				    			weaponHeldText = "CAR SMG";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 21) { //Rampage
				    			weaponHeldText = "Rampage";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 111) { //Repeater
				    			weaponHeldText = "Repeater";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 90) { //Hemlock
				    			weaponHeldText = "Hemlock";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 88) { //Flatline
				    			weaponHeldText = "Flatline";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		//Energy Weapons
				    		if (weaponHeldID == 113) { //Nemesis
				    			weaponHeldText = "Nemesis";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 110) { //Volt
				    			weaponHeldText = "Volt";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 107) { //TripleTake
				    			weaponHeldText = "Triple Take";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 93) { //LSTAR
				    			weaponHeldText = "L-STAR";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 84) { //Devotion
				    			weaponHeldText = "Devotion";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 86) { //Havoc
				    			weaponHeldText = "Havoc";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		//Shotguns
				    		if (weaponHeldID == 96) { //Mozambique
				    			weaponHeldText = "Mozambique";
				    			weaponHeldColor = ImColor(ShotgunWeaponColor[0], ShotgunWeaponColor[1], ShotgunWeaponColor[2], ShotgunWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 87) { //EVA8
				    			weaponHeldText = "EVA-8 Auto";
				    			weaponHeldColor = ImColor(ShotgunWeaponColor[0], ShotgunWeaponColor[1], ShotgunWeaponColor[2], ShotgunWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 103) { //Peacekeeper
				    			weaponHeldText = "Peacekeeper";
				    			weaponHeldColor = ImColor(ShotgunWeaponColor[0], ShotgunWeaponColor[1], ShotgunWeaponColor[2], ShotgunWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 95) { //Mastiff
				    			weaponHeldText = "Mastiff";
				    			weaponHeldColor = ImColor(ShotgunWeaponColor[0], ShotgunWeaponColor[1], ShotgunWeaponColor[2], ShotgunWeaponColor[3]);
				    		}
				    		//Snipers
				    		if (weaponHeldID == 1) { //Sentinel
				    			weaponHeldText = "Sentinel";
				    			weaponHeldColor = ImColor(SniperWeaponColor[0], SniperWeaponColor[1], SniperWeaponColor[2], SniperWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 83) { //ChargeRifle
				    			weaponHeldText = "Charge Rifle";
				    			weaponHeldColor = ImColor(SniperWeaponColor[0], SniperWeaponColor[1], SniperWeaponColor[2], SniperWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 85) { //Longbow
				    			weaponHeldText = "Longbow";
				    			weaponHeldColor = ImColor(SniperWeaponColor[0], SniperWeaponColor[1], SniperWeaponColor[2], SniperWeaponColor[3]);
				    		}
				    		//Legendary Weapons
				    		if (weaponHeldID == 109) { //Wingman
				    			weaponHeldText = "Wingman";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 102) { //Prowler
				    			weaponHeldText = "Prowler";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 2) { //Bocek
				    			weaponHeldText = "Bocek";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 92) { //Kraber
				    			weaponHeldText = "Kraber";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 163) { //Knife
				    			weaponHeldText = "Throwing Knife";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 3) { //BusterSword
				    			weaponHeldText = "Buster Sword";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		//Melee & Grenade
				    		/*if (weaponHeldID == 213) { //Thermite Grenade
				    			weaponHeldText = "Thermite Grenade";
				    			weaponHeldColor = ThrowableWeaponColor;
				    		}*/
				    		if (p->IsHoldingGrenade) {
				    			weaponHeldText = "Throwable";
				    			weaponHeldColor = ImColor(ThrowableWeaponColor[0], ThrowableWeaponColor[1], ThrowableWeaponColor[2], ThrowableWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 114) { //Melee
				    			weaponHeldText = "Melee";
				    			weaponHeldColor = ImColor(MeleeWeaponColor[0], MeleeWeaponColor[1], MeleeWeaponColor[2], MeleeWeaponColor[3]);
				    		}
				    	}
					
					if (WeaponColorType) { //Changes color to ammo type
						if (DrawWeapon && DrawStatus) {
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 20)), weaponHeldText, ImColor(weaponHeldColor), true, true, false);
						}
						
						if (DrawWeapon && !DrawStatus) {
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 0)), weaponHeldText, ImColor(weaponHeldColor), true, true, false);
						}
					}
					if (!WeaponColorType) {
						if (DrawWeapon && DrawStatus) {
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 20)), weaponHeldText, ImColor(WeaponColor[0], WeaponColor[1], WeaponColor[2] ,WeaponColor[3]), true, true, false);
						}
						
						if (DrawWeapon && !DrawStatus) {
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 0)), weaponHeldText, ImColor(WeaponColor[0], WeaponColor[1], WeaponColor[2] ,WeaponColor[3]), true, true, false);
						}
					}
				}
			}
			
			/*bool TestWeaponID = false; //For finding weapon IDs (Used for finding melee ID)
			if (TestWeaponID) {
				if (p->IsHostile) {
					Vector2D testWScreenPosition;
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), testWScreenPosition);
					
					std::stringstream wepID;
					wepID << p->WeaponIndex;
					std::string wepInt = wepID.str() + " ";
					const char* wepText = (char*)wepInt.c_str();

					ImColor weaponWHeldColor;
					weaponWHeldColor = ImColor(255, 255, 255);
					
					Renderer::DrawText(Canvas, testWScreenPosition.Add(Vector2D(0, 0)), wepText, ImColor(weaponWHeldColor), true, true, false);
				}
			}*/
				
			// DrawBox
			if (DrawBox && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(ESPMaxDistance))) {
				Vector2D Head, Foot;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
				    
				if (!ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(VisibleBoxColor[0], VisibleBoxColor[1], VisibleBoxColor[2], VisibleBoxColor[3]), BoxThickness);
					}
					if (p->IsHostile && !p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(InvisibleBoxColor[0], InvisibleBoxColor[1], InvisibleBoxColor[2], InvisibleBoxColor[3]), BoxThickness);
					}
				}
				    
				if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(VisibleBoxColor[0], VisibleBoxColor[1], VisibleBoxColor[2], VisibleBoxColor[3]), BoxThickness);
					}
					if (p->IsHostile && !p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(InvisibleBoxColor[0], InvisibleBoxColor[1], InvisibleBoxColor[2], InvisibleBoxColor[3]), BoxThickness);
					}
					if (p->IsAlly) {
						Renderer::DrawBox(Canvas, Foot, Head, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]), BoxThickness);
					}
				}
			}
			
			// Draw Filled Box
			if (DrawFilledBox && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(ESPMaxDistance))) {
				Vector2D Head, Foot;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
				    
				if (!ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(VisibleFilledBoxColor[0], VisibleFilledBoxColor[1], VisibleFilledBoxColor[2], VisibleFilledBoxColor[3]));
					}
					if (p->IsHostile && !p->IsVisible) {
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(InvisibleFilledBoxColor[0], InvisibleFilledBoxColor[1], InvisibleFilledBoxColor[2], InvisibleFilledBoxColor[3]));
					}
				}
				    
				if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(VisibleFilledBoxColor[0], VisibleFilledBoxColor[1], VisibleFilledBoxColor[2], VisibleFilledBoxColor[3]));
					}
					if (p->IsHostile && !p->IsVisible) {
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(InvisibleFilledBoxColor[0], InvisibleFilledBoxColor[1], InvisibleFilledBoxColor[2], InvisibleFilledBoxColor[3]));
					}
					if (p->IsAlly) {
						Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
					}
				}
			}
			
			// Draw Health + Shield
			if (DrawStatus) {
				Vector2D StatusPos;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), StatusPos);
				
				std::stringstream healthValue, shieldValue, maxHealthValue, maxShieldValue;
				healthValue << p->Health;
				shieldValue << p->Shield;
				maxHealthValue << p->MaxHealth;
				maxShieldValue << p->MaxShield;
				std::string healthInt = healthValue.str() + " HP";
				std::string shieldInt = shieldValue.str() + " AP";
				const char* healthText = (char*)healthInt.c_str();
				const char* shieldText = (char*)shieldInt.c_str();
				std::string combinedHealth = healthValue.str() + " / " + maxHealthValue.str() + " HP";
				const char* combinedHealthText = combinedHealth.c_str();
				std::string combinedShield = shieldValue.str() + " / " + maxShieldValue.str() + " AP";
				const char* combinedShieldText = combinedShield.c_str();
					
				ImColor ShieldColor;
				if (p->MaxShield == 50) { //white
					ShieldColor = ImColor(247, 247, 247);
				}
				else if (p->MaxShield == 75) { //blue
					ShieldColor = ImColor(39, 178, 255);
				}
				else if (p->MaxShield == 100) { //purple
					ShieldColor = ImColor(206, 59, 255);
				}
				else if (p->MaxShield == 125) { //red
					ShieldColor = ImColor(219, 2, 2);
				}
				else {
					ShieldColor = ImColor(247, 247, 247);
				}
				
				//Render Text
				if (ShowTeam) {
					if (!ShowMaxStatusValues) {
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), healthText, ImColor(0, 255, 0), true, true, false);
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0 + 10)), shieldText, ShieldColor, true, true, false);
					}
					if (ShowMaxStatusValues) {
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), combinedHealthText, ImColor(0, 255, 0), true, true, false);
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0 + 10)), combinedShieldText, ShieldColor, true, true, false);
					}
				}
				if (!ShowTeam) {
					if (!ShowMaxStatusValues && p->IsHostile) {
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), healthText, ImColor(0, 255, 0), true, true, false);
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0 + 10)), shieldText, ShieldColor, true, true, false);
					}
					if (ShowMaxStatusValues && p->IsHostile) {
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), combinedHealthText, ImColor(0, 255, 0), true, true, false);
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0 + 10)), combinedShieldText, ShieldColor, true, true, false);
					}
				}
			}
			
			//Draw Health Bar
			if (ShowTeam) {
				if (HealthBar) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int health = p->Health;
					
					Renderer::DrawHealthBar(Canvas, Foot, Head, health, BarThickness);
				}
			}
			if (!ShowTeam) {
				if (HealthBar && p->IsHostile) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int health = p->Health;
					
					Renderer::DrawHealthBar(Canvas, Foot, Head, health, BarThickness);
				}
			}
			
			//Draw Shield Bar
			if (ShowTeam) {
				if (ShieldBar) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int shield = p->Shield;
					
					ImColor shieldBarColor;
					if (p->MaxShield == 50) { //white
						shieldBarColor = ImColor(247, 247, 247);
					}
					else if (p->MaxShield == 75) { //blue
						shieldBarColor = ImColor(39, 178, 255);
					}
					else if (p->MaxShield == 100) { //purple
						shieldBarColor = ImColor(206, 59, 255);
					}
					else if (p->MaxShield == 125) { //red
						shieldBarColor = ImColor(219, 2, 2);
					}
					else {
						shieldBarColor = ImColor(247, 247, 247);
					}
					
					
					Renderer::DrawShieldBar(Canvas, Foot, Head, shield, shieldBarColor, BarThickness);
				}
			}
			
			if (!ShowTeam) {
				if (ShieldBar && p->IsHostile) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int shield = p->Shield;
					
					ImColor shieldBarColor;
					if (p->MaxShield == 50) { //white
						shieldBarColor = ImColor(247, 247, 247);
					}
					else if (p->MaxShield == 75) { //blue
						shieldBarColor = ImColor(39, 178, 255);
					}
					else if (p->MaxShield == 100) { //purple
						shieldBarColor = ImColor(206, 59, 255);
					}
					else if (p->MaxShield == 125) { //red
						shieldBarColor = ImColor(219, 2, 2);
					}
					else {
						shieldBarColor = ImColor(247, 247, 247);
					}
					
					
					Renderer::DrawShieldBar(Canvas, Foot, Head, shield, shieldBarColor, BarThickness);
				}
			}
				
			//Draw Skeleton
			if (Skeleton) {
		 
				Vector2D Head, Neck, UpperChest, LowerChest, Stomach, Leftshoulder, Leftelbow, LeftHand, Rightshoulder, RightelbowBone, RightHand, LeftThighs, Leftknees, Leftleg, RightThighs, Rightknees, Rightleg;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Neck), Neck);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::UpperChest), UpperChest);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LowerChest), LowerChest);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Stomach), Stomach);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftshoulder), Leftshoulder);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftelbow), Leftelbow);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftHand), LeftHand);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightshoulder), Rightshoulder);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightelbowBone), RightelbowBone);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightHand), RightHand);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftThighs), LeftThighs);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftknees), Leftknees);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftleg), Leftleg);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightThighs), RightThighs);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightknees), Rightknees);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightleg), Rightleg);
		 
				if (!ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
				    	}
					if (p->IsHostile && !p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
				    	}
				}
				    
		 		if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
				    	}
					if (p->IsHostile && !p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, ImColor(InvisibleSkeletonColor[0], InvisibleSkeletonColor[1], InvisibleSkeletonColor[2], InvisibleSkeletonColor[3]));
				    	}
			    		
			    		if (p->IsAlly) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));;
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
				        }
				}
			}
			
			// Seer
			if (DrawSeer && p->IsHostile) {
				Vector2D headScreenPosition;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), headScreenPosition);
				if (!headScreenPosition.IsZeroVector())
				    Renderer::DrawSeer(Canvas, headScreenPosition.x, headScreenPosition.y - 20, p->Shield, p->MaxShield, p->Health);
			    }
			    
			//Show Near
			if (ShowNear)
			{
			    // Gui DrawText Version
			    Renderer::DrawText(Canvas, Vector2D(ScreenWidth * 0.5, ScreenHeight * 0.6), ("NEAR : " + std::to_string(PlayersNear)).c_str(), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), true, true, false);
			    // Gui Version
			    /*
			   ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
			   ImGui::SetNextWindowPos(ImVec2(Center.x, Center.y * 1.2), ImGuiCond_Once, ImVec2(0.50f, 0.5f));
			   ImGui::SetNextWindowBgAlpha(0.3f);
			   ImGui::Begin("Near", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
			   ImGui::Text("Near: ");
			   ImGui::SameLine();
			   ImGui::TextColored(PlayersNear > 0 ? ImVec4(0.4, 1, 0.343, 1) : ImVec4(1, 1, 1, 1), "%d", PlayersNear);
			   ImGui::End();
			   */
			}
			PlayersNear = 0;
			
	//		// Draw Seer on locked target
	//		if (AimAssistState->TargetSelected && AimAssistState->CurrentTarget) {
	//		    Vector2D headScreenPosition;
	//		    GameCamera->WorldToScreen(AimAssistState->CurrentTarget->GetBonePosition(HitboxType::Head), headScreenPosition);
	//		    if (headScreenPosition.IsZeroVector())
	//		        return;
	//	 
	//		    Renderer::DrawSeer(Canvas, headScreenPosition.x, headScreenPosition.y - 20, AimAssistState->CurrentTarget->Shield, AimAssistState->CurrentTarget->MaxShield, AimAssistState->CurrentTarget->Health);
	//		    return;
	//		}
		    }
 	    	if (VisibilityCheck) { //Always shows esp
 	    		PlayersNear++;
		    	if (DrawTracers) {
				//Tracers
				Vector2D chestScreenPosition;
				if (Config::Sense::TracerBone == 0) {
				    GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 66)), chestScreenPosition);
				}
				else if (Config::Sense::TracerBone == 1) {
				    GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), chestScreenPosition);
				}
				
				if (DrawTracers && Config::Sense::TracerPos == 0) //top to head
				{
				    if (!chestScreenPosition.IsZeroVector())
				    {
				        int x = (int)(ScreenWidth * 0.5f);
				        
				        if (!ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
						}
					}
					
					if (ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
						}
						
						if (p->IsAlly & p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						}
					}
				    }
				}
				
				else if (DrawTracers && Config::Sense::TracerPos == 1) //middle to bottom
				{
				    if (!chestScreenPosition.IsZeroVector())
				    {
				        int x = (int)(ScreenWidth * 0.5f);
				        
				        if (!ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
				        	}
				        }
				        
				        if (ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
				        	}
				    		
				    		if (p->IsAlly & p->IsVisible) {
				    			Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
				    		}
				    	}
				    }
				}
				
				else if (DrawTracers && Config::Sense::TracerPos == 2) //bottom to bottom
				{
				    if (!chestScreenPosition.IsZeroVector())
				    {
				        int x = (int)(ScreenWidth * 0.5f);
				        
				        if (!ShowTeam) {
						if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
				    		}
					}
					
					if (ShowTeam) {
						if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor[0], VisibleTracerColor[1], VisibleTracerColor[2], VisibleTracerColor[3]));
				    		}
				    		
				    		if (p->IsAlly & p->IsVisible) {
				    			Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
			    			}
			    		}
			    	    }
			    	}
			}
			    
			//Show Legend
			if (ShowLegend) {
				if (p->IsHostile && p->IsVisible && !p->IsDummy()) {
					Vector2D Head;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head).Add(Vector3D(0, 0, 33)), Head);
					
					Renderer::DrawText(Canvas, Head.Subtract(Vector2D(0,8)), p->getPlayerModelName().c_str(), ImColor(255, 255, 255), true, true, false);
				
				}
			}

			// Distance
			if (DrawDistance) {
				Vector2D distanceScreenPosition;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head).Add(Vector3D(0, 0, 80)), distanceScreenPosition);
				
				if (ShowTeam) {
					if (!distanceScreenPosition.IsZeroVector()) {
						if (p->IsAlly && p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(255, 255, 255), true, true, false);
						}
						if (p->IsHostile && p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor[0], VisibleDistanceColor[1], VisibleDistanceColor[2],VisibleDistanceColor[3]), true, true, false);
						}
					}
				}
				if (!ShowTeam) {
					if (!distanceScreenPosition.IsZeroVector()) {
						if (p->IsHostile && p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor[0], VisibleDistanceColor[1], VisibleDistanceColor[2],VisibleDistanceColor[3]), true, true, false);
						}
					}
				}
			}
			
			// Draw Names
			if (DrawNames) {
				Vector2D nameScreenPosition;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head).Add(Vector3D(0, 0, 60)), nameScreenPosition);
				if (p->IsHostile && p->IsVisible && !p->IsDummy()) {
					Renderer::DrawText(Canvas, nameScreenPosition.Subtract(Vector2D(0, 0)), p->GetPlayerName().c_str(), ImColor(VisibleNameColor[0], VisibleNameColor[1], VisibleNameColor[2], VisibleNameColor[3]), true, true, false);
				}
				    
				// Draw Team Names
				if (ShowTeam && TeamNames && p->IsAlly && p->IsVisible && !p->IsDummy()) {
					Renderer::DrawText(Canvas, nameScreenPosition.Add(Vector2D(0, 0)), p->GetPlayerName().c_str(), ImColor(TeamNameColor[0], TeamNameColor[1], TeamNameColor[2], TeamNameColor[3]), true, true, false);
				}
			}
			
			// Draw Weapon
			if (DrawWeapon) {
				if (p->IsHostile && p->IsVisible) {
					Vector2D wepScreenPosition;
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), wepScreenPosition);
					
					int weaponHeldID;
					weaponHeldID = p->WeaponIndex;
					const char* weaponHeldText;

					ImColor weaponHeldColor;
					weaponHeldColor = ImColor(255, 255, 255);
					
					if (DrawWeapon) {
				    		//Light Weapons
				    		if (weaponHeldID == 105) { //P2020
				    			weaponHeldText = "P2020";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 81) { //RE-45
				    			weaponHeldText = "RE-45";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 80) { //Alternator
				    			weaponHeldText = "Alternator";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 104) { //R-99
				    			weaponHeldText = "R-99";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 0) { //R-301
				    			weaponHeldText = "R-301";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 106) { //Spitfire
				    			weaponHeldText = "Spitfire";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 89) { //G7
				    			weaponHeldText = "G7 Scout";
				    			weaponHeldColor = ImColor(LightWeaponColor[0], LightWeaponColor[1], LightWeaponColor[2], LightWeaponColor[3]);
				    		}
				    		//Heavy Weapons
				    		if (weaponHeldID == 112) { //CARSMG
				    			weaponHeldText = "CAR SMG";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 21) { //Rampage
				    			weaponHeldText = "Rampage";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 111) { //Repeater
				    			weaponHeldText = "Repeater";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 90) { //Hemlock
				    			weaponHeldText = "Hemlock";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 88) { //Flatline
				    			weaponHeldText = "Flatline";
				    			weaponHeldColor = ImColor(HeavyWeaponColor[0], HeavyWeaponColor[1], HeavyWeaponColor[2], HeavyWeaponColor[3]);
				    		}
				    		//Energy Weapons
				    		if (weaponHeldID == 113) { //Nemesis
				    			weaponHeldText = "Nemesis";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 110) { //Volt
				    			weaponHeldText = "Volt";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 107) { //TripleTake
				    			weaponHeldText = "Triple Take";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 93) { //LSTAR
				    			weaponHeldText = "L-STAR";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 84) { //Devotion
				    			weaponHeldText = "Devotion";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 86) { //Havoc
				    			weaponHeldText = "Havoc";
				    			weaponHeldColor = ImColor(EnergyWeaponColor[0], EnergyWeaponColor[1], EnergyWeaponColor[2], EnergyWeaponColor[3]);
				    		}
				    		//Shotguns
				    		if (weaponHeldID == 96) { //Mozambique
				    			weaponHeldText = "Mozambique";
				    			weaponHeldColor = ImColor(ShotgunWeaponColor[0], ShotgunWeaponColor[1], ShotgunWeaponColor[2], ShotgunWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 87) { //EVA8
				    			weaponHeldText = "EVA-8 Auto";
				    			weaponHeldColor = ImColor(ShotgunWeaponColor[0], ShotgunWeaponColor[1], ShotgunWeaponColor[2], ShotgunWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 103) { //Peacekeeper
				    			weaponHeldText = "Peacekeeper";
				    			weaponHeldColor = ImColor(ShotgunWeaponColor[0], ShotgunWeaponColor[1], ShotgunWeaponColor[2], ShotgunWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 95) { //Mastiff
				    			weaponHeldText = "Mastiff";
				    			weaponHeldColor = ImColor(ShotgunWeaponColor[0], ShotgunWeaponColor[1], ShotgunWeaponColor[2], ShotgunWeaponColor[3]);
				    		}
				    		//Snipers
				    		if (weaponHeldID == 1) { //Sentinel
				    			weaponHeldText = "Sentinel";
				    			weaponHeldColor = ImColor(SniperWeaponColor[0], SniperWeaponColor[1], SniperWeaponColor[2], SniperWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 83) { //ChargeRifle
				    			weaponHeldText = "Charge Rifle";
				    			weaponHeldColor = ImColor(SniperWeaponColor[0], SniperWeaponColor[1], SniperWeaponColor[2], SniperWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 85) { //Longbow
				    			weaponHeldText = "Longbow";
				    			weaponHeldColor = ImColor(SniperWeaponColor[0], SniperWeaponColor[1], SniperWeaponColor[2], SniperWeaponColor[3]);
				    		}
				    		//Legendary Weapons
				    		if (weaponHeldID == 109) { //Wingman
				    			weaponHeldText = "Wingman";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 102) { //Prowler
				    			weaponHeldText = "Prowler";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 2) { //Bocek
				    			weaponHeldText = "Bocek";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 92) { //Kraber
				    			weaponHeldText = "Kraber";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 163) { //Knife
				    			weaponHeldText = "Throwing Knife";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 3) { //BusterSword
				    			weaponHeldText = "Buster Sword";
				    			weaponHeldColor = ImColor(LegendaryWeaponColor[0], LegendaryWeaponColor[1], LegendaryWeaponColor[2], LegendaryWeaponColor[3]);
				    		}
				    		//Melee & Grenade
				    		/*if (weaponHeldID == 213) { //Thermite Grenade
				    			weaponHeldText = "Thermite Grenade";
				    			weaponHeldColor = ThrowableWeaponColor;
				    		}*/
				    		if (p->IsHoldingGrenade) {
				    			weaponHeldText = "Throwable";
				    			weaponHeldColor = ImColor(ThrowableWeaponColor[0], ThrowableWeaponColor[1], ThrowableWeaponColor[2], ThrowableWeaponColor[3]);
				    		}
				    		if (weaponHeldID == 114) { //Melee
				    			weaponHeldText = "Melee";
				    			weaponHeldColor = ImColor(MeleeWeaponColor[0], MeleeWeaponColor[1], MeleeWeaponColor[2], MeleeWeaponColor[3]);
				    		}
				    	}
					
					if (WeaponColorType) { //Changes color to ammo type
						if (DrawWeapon && DrawStatus) {
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 20)), weaponHeldText, ImColor(weaponHeldColor), true, true, false);
						}
						
						if (DrawWeapon && !DrawStatus) {
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 0)), weaponHeldText, ImColor(weaponHeldColor), true, true, false);
						}
					}
					if (!WeaponColorType) {
						if (DrawWeapon && DrawStatus) {
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 20)), weaponHeldText, ImColor(WeaponColor[0], WeaponColor[1], WeaponColor[2], WeaponColor[3]), true, true, false);
						}
						
						if (DrawWeapon && !DrawStatus) {
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 0)), weaponHeldText, ImColor(WeaponColor[0], WeaponColor[1], WeaponColor[2], WeaponColor[3]), true, true, false);
						}
					}
				}
			}
			
			/*bool TestWeaponID = false; //For finding weapon IDs (Used for finding melee ID)
			if (TestWeaponID) {
				if (p->IsHostile) {
					Vector2D testWScreenPosition;
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), testWScreenPosition);
					
					std::stringstream wepID;
					wepID << p->WeaponIndex;
					std::string wepInt = wepID.str() + " ";
					const char* wepText = (char*)wepInt.c_str();

					ImColor weaponWHeldColor;
					weaponWHeldColor = ImColor(255, 255, 255);
					
					Renderer::DrawText(Canvas, testWScreenPosition.Add(Vector2D(0, 0)), wepText, ImColor(weaponWHeldColor), true, true, false);
				}
			}*/
				
			// DrawBox
			if (DrawBox && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(ESPMaxDistance))) {
				Vector2D Head, Foot;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
				    
				if (!ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(VisibleBoxColor[0], VisibleBoxColor[1], VisibleBoxColor[2], VisibleBoxColor[3]), BoxThickness);
					}
				}
				    
				if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(VisibleBoxColor[0], VisibleBoxColor[1], VisibleBoxColor[2], VisibleBoxColor[3]), BoxThickness);
					}
					if (p->IsAlly && p->IsVisible) {
						Renderer::DrawBox(Canvas, Foot, Head, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]), BoxThickness);
					}
				}
			}
			
			// Draw Filled Box
			if (DrawFilledBox && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(ESPMaxDistance))) {
				Vector2D Head, Foot;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
				    
				if (!ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(VisibleFilledBoxColor[0], VisibleFilledBoxColor[1], VisibleFilledBoxColor[2], VisibleFilledBoxColor[3]));
					}
				}
				    
				if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(VisibleFilledBoxColor[0], VisibleFilledBoxColor[1], VisibleFilledBoxColor[2], VisibleFilledBoxColor[3]));
					}
					if (p->IsAlly && p->IsVisible) {
						Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
					}
				}
			}
			
			// Draw Health + Shield
			if (DrawStatus) {
				Vector2D StatusPos;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), StatusPos);
				
				std::stringstream healthValue, shieldValue, maxHealthValue, maxShieldValue;
				healthValue << p->Health;
				shieldValue << p->Shield;
				maxHealthValue << p->MaxHealth;
				maxShieldValue << p->MaxShield;
				std::string healthInt = healthValue.str() + " HP";
				std::string shieldInt = shieldValue.str() + " AP";
				const char* healthText = (char*)healthInt.c_str();
				const char* shieldText = (char*)shieldInt.c_str();
				std::string combinedHealth = healthValue.str() + " / " + maxHealthValue.str() + " HP";
				const char* combinedHealthText = combinedHealth.c_str();
				std::string combinedShield = shieldValue.str() + " / " + maxShieldValue.str() + " AP";
				const char* combinedShieldText = combinedShield.c_str();
					
				ImColor ShieldColor;
				if (p->MaxShield == 50) { //white
					ShieldColor = ImColor(247, 247, 247);
				}
				else if (p->MaxShield == 75) { //blue
					ShieldColor = ImColor(39, 178, 255);
				}
				else if (p->MaxShield == 100) { //purple
					ShieldColor = ImColor(206, 59, 255);
				}
				else if (p->MaxShield == 125) { //red
					ShieldColor = ImColor(219, 2, 2);
				}
				else {
					ShieldColor = ImColor(247, 247, 247);
				}
				
				//Render Text
				if (ShowTeam) {
					if (!ShowMaxStatusValues && p->IsVisible) {
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), healthText, ImColor(0, 255, 0), true, true, false);
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0 + 10)), shieldText, ShieldColor, true, true, false);
					}
					if (ShowMaxStatusValues && p->IsVisible) {
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), combinedHealthText, ImColor(0, 255, 0), true, true, false);
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0 + 10)), combinedShieldText, ShieldColor, true, true, false);
					}
				}
				if (!ShowTeam) {
					if (!ShowMaxStatusValues && p->IsHostile && p->IsVisible) {
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), healthText, ImColor(0, 255, 0), true, true, false);
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0 + 10)), shieldText, ShieldColor, true, true, false);
					}
					if (ShowMaxStatusValues && p->IsHostile && p->IsVisible) {
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), combinedHealthText, ImColor(0, 255, 0), true, true, false);
						Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0 + 10)), combinedShieldText, ShieldColor, true, true, false);
					}
				}
			}
			
			//Draw Health Bar
			if (ShowTeam) {
				if (HealthBar && p->IsVisible) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int health = p->Health;
					
					Renderer::DrawHealthBar(Canvas, Foot, Head, health, BarThickness);
				}
			}
			if (!ShowTeam) {
				if (HealthBar && p->IsHostile && p->IsVisible) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int health = p->Health;
					
					Renderer::DrawHealthBar(Canvas, Foot, Head, health, BarThickness);
				}
			}
			
			//Draw Shield Bar
			if (ShowTeam) {
				if (ShieldBar && p->IsVisible) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int shield = p->Shield;
					
					ImColor shieldBarColor;
					if (p->MaxShield == 50) { //white
						shieldBarColor = ImColor(247, 247, 247);
					}
					else if (p->MaxShield == 75) { //blue
						shieldBarColor = ImColor(39, 178, 255);
					}
					else if (p->MaxShield == 100) { //purple
						shieldBarColor = ImColor(206, 59, 255);
					}
					else if (p->MaxShield == 125) { //red
						shieldBarColor = ImColor(219, 2, 2);
					}
					else {
						shieldBarColor = ImColor(247, 247, 247);
					}
					
					
					Renderer::DrawShieldBar(Canvas, Foot, Head, shield, shieldBarColor, BarThickness);
				}
			}
			
			if (!ShowTeam) {
				if (ShieldBar && p->IsHostile && p->IsVisible) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int shield = p->Shield;
					
					ImColor shieldBarColor;
					if (p->MaxShield == 50) { //white
						shieldBarColor = ImColor(247, 247, 247);
					}
					else if (p->MaxShield == 75) { //blue
						shieldBarColor = ImColor(39, 178, 255);
					}
					else if (p->MaxShield == 100) { //purple
						shieldBarColor = ImColor(206, 59, 255);
					}
					else if (p->MaxShield == 125) { //red
						shieldBarColor = ImColor(219, 2, 2);
					}
					else {
						shieldBarColor = ImColor(247, 247, 247);
					}
					
					
					Renderer::DrawShieldBar(Canvas, Foot, Head, shield, shieldBarColor, BarThickness);
				}
			}
				
			//Draw Skeleton
			if (Skeleton) {
		 
				Vector2D Head, Neck, UpperChest, LowerChest, Stomach, Leftshoulder, Leftelbow, LeftHand, Rightshoulder, RightelbowBone, RightHand, LeftThighs, Leftknees, Leftleg, RightThighs, Rightknees, Rightleg;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Neck), Neck);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::UpperChest), UpperChest);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LowerChest), LowerChest);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Stomach), Stomach);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftshoulder), Leftshoulder);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftelbow), Leftelbow);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftHand), LeftHand);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightshoulder), Rightshoulder);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightelbowBone), RightelbowBone);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightHand), RightHand);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftThighs), LeftThighs);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftknees), Leftknees);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftleg), Leftleg);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightThighs), RightThighs);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightknees), Rightknees);
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightleg), Rightleg);
		 
				if (!ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
				    	}
				}
				    
		 		if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, ImColor(VisibleSkeletonColor[0], VisibleSkeletonColor[1], VisibleSkeletonColor[2], VisibleSkeletonColor[3]));
				    	}
			    		
			    		if (p->IsAlly && p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, ImColor(TeamColor[0], TeamColor[1], TeamColor[2], TeamColor[3]));
				        }
				}
			}
			
			// Seer
			if (DrawSeer && p->IsHostile && p->IsVisible) {
				Vector2D headScreenPosition;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), headScreenPosition);
				if (!headScreenPosition.IsZeroVector())
				    Renderer::DrawSeer(Canvas, headScreenPosition.x, headScreenPosition.y - 20, p->Shield, p->MaxShield, p->Health);
			    }
			    
			//Show Near
			if (ShowNear)
			{
			    // Gui DrawText Version
			    Renderer::DrawText(Canvas, Vector2D(ScreenWidth * 0.5, ScreenHeight * 0.6), ("NEAR : " + std::to_string(PlayersNear)).c_str(), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), true, true, false);
			    // Gui Version
			    /*
			   ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
			   ImGui::SetNextWindowPos(ImVec2(Center.x, Center.y * 1.2), ImGuiCond_Once, ImVec2(0.50f, 0.5f));
			   ImGui::SetNextWindowBgAlpha(0.3f);
			   ImGui::Begin("Near", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
			   ImGui::Text("Near: ");
			   ImGui::SameLine();
			   ImGui::TextColored(PlayersNear > 0 ? ImVec4(0.4, 1, 0.343, 1) : ImVec4(1, 1, 1, 1), "%d", PlayersNear);
			   ImGui::End();
			   */
			}
			PlayersNear = 0;
			
	//		// Draw Seer on locked target
	//		if (AimAssistState->TargetSelected && AimAssistState->CurrentTarget) {
	//		    Vector2D headScreenPosition;
	//		    GameCamera->WorldToScreen(AimAssistState->CurrentTarget->GetBonePosition(HitboxType::Head), headScreenPosition);
	//		    if (headScreenPosition.IsZeroVector())
	//		        return;
	//	 
	//		    Renderer::DrawSeer(Canvas, headScreenPosition.x, headScreenPosition.y - 20, AimAssistState->CurrentTarget->Shield, AimAssistState->CurrentTarget->MaxShield, AimAssistState->CurrentTarget->Health);
	//		    return;
	//		}
		    }
		    
		}
	   }
    }
};
