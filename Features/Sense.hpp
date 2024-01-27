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
    
    //Position Changer
    float StatusVec3Y = 0;
    float StatusVec2Y = 0;
    
    ImVec4 InvisibleBoxColor = ImColor(255, 0, 0, 255);
    ImVec4 VisibleBoxColor = ImColor(0, 255, 0, 255);
    ImVec4 InvisibleFilledBoxColor = ImColor(0, 0, 0, 30);
    ImVec4 VisibleFilledBoxColor = ImColor(0, 0, 0, 30);
    ImVec4 InvisibleTracerColor = ImColor(255, 0, 0, 255);
    ImVec4 VisibleTracerColor = ImColor(0, 255, 0, 255);
    ImVec4 InvisibleSkeletonColor = ImColor(255, 255, 255, 255);
    ImVec4 VisibleSkeletonColor = ImColor(255, 255, 255, 255);
    ImVec4 InvisibleNameColor = ImColor(255, 255, 255, 255);
    ImVec4 VisibleNameColor = ImColor(255, 255, 255, 255);
    ImVec4 InvisibleDistanceColor = ImColor(255, 255, 255, 255);
    ImVec4 VisibleDistanceColor = ImColor(255, 255, 255, 255);
    ImVec4 FOVColor = ImColor(255, 255, 255, 255);
    ImVec4 FilledFOVColor = ImColor(0, 0, 0, 20);
    ImVec4 WeaponColor = ImColor(255, 255, 255, 255);
    ImVec4 NearColor = ImColor(255, 255, 255, 255);
    ImVec4 TeamColor = ImColor(0, 255, 255, 255);
    ImVec4 TeamNameColor = ImColor(255, 255, 255, 255);
    ImVec4 CrosshairColor = ImColor(255, 255, 255, 255);
    //WeaponESP Colors
    ImVec4 LightWeaponColor = ImColor(255, 153, 0, 255);
    ImVec4 HeavyWeaponColor = ImColor(69, 255, 184, 255);
    ImVec4 EnergyWeaponColor = ImColor(83, 242, 15, 255);
    ImVec4 ShotgunWeaponColor = ImColor(255, 0, 0, 255);
    ImVec4 SniperWeaponColor = ImColor(66, 85, 255, 255);
    ImVec4 LegendaryWeaponColor = ImColor(255, 130, 245, 255);
    ImVec4 MeleeWeaponColor = ImColor(255, 255, 255, 255);
    ImVec4 ThrowableWeaponColor = ImColor(255, 255, 0, 255);

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
		        ImGui::ColorEdit4("Color##ESPTeam", (float*)&TeamColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the color of teammates\nRecomended: Blue");
		        
		        ImGui::Checkbox("Show Team Names", &TeamNames);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draw Name ESP on Teammates");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Color##ESPTeamName", (float*)&TeamNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the color of teammate's names\nRecomended: White");
		    }
		    
		    ImGui::Separator();

		    if (ImGui::CollapsingHeader("Boxes", nullptr)) {
			    ImGui::Checkbox("Draw Box", &DrawBox);
			    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Drawbox on enemy");
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Visible Color##ESPBox", (float*)&VisibleBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Invisible Color##ESPBox", (float*)&InvisibleBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			    ImGui::Checkbox("Draw Filled Box", &DrawFilledBox);
			    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Draw a Filled box on enemy");
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Visible Color##ESPFilledBox", (float*)&VisibleFilledBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Invisible Color##ESPFilledBox", (float*)&InvisibleFilledBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
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
			    ImGui::ColorEdit4("Visible Color##ESPTracer", (float*)&VisibleTracerColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			    ImGui::SameLine();
			    ImGui::ColorEdit4("Invisible Color##ESPTracer", (float*)&InvisibleTracerColor, ImGuiColorEditFlags_NoInputs);
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
		        ImGui::ColorEdit4("Visible Color##ESPSkeleton", (float*)&VisibleSkeletonColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPSkeleton", (float*)&InvisibleSkeletonColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
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
		        	ImGui::ColorEdit4("Color##ESPWeapon", (float*)&WeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        }
		        if(WeaponColorType) {
				ImGui::Text("Weapon ESP Colors");
				ImGui::ColorEdit4("Light##ESPWeaponColor", (float*)&LightWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Heavy##ESPWeaponColor", (float*)&HeavyWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Energy##ESPWeaponColor", (float*)&EnergyWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Shotguns##ESPWeaponColor", (float*)&ShotgunWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				//ImGui::SameLine();
				ImGui::ColorEdit4("Snipers##ESPWeaponColor", (float*)&SniperWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Legendary##ESPWeaponColor", (float*)&LegendaryWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Throwables##ESPWeapon", (float*)&ThrowableWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4("Melee##ESPWeapon", (float*)&MeleeWeaponColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        }
		        
		        ImGui::Separator();
		    
		        ImGui::Checkbox("Draw Names", &DrawNames);
		        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			        ImGui::SetTooltip("Show enemies names");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Visible Color##ESPNames", (float*)&VisibleNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPNames", (float*)&InvisibleNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        
		        ImGui::Separator();
		        
		        ImGui::Checkbox("Draw Distance", &DrawDistance);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Show how far away the enemies are");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Visible Color##ESPDistance", (float*)&VisibleDistanceColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPDistance", (float*)&InvisibleDistanceColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);

			ImGui::Separator();

		        ImGui::Checkbox("Show Enemy Count Near", &ShowNear);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Show how many enemies are near");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Color##ESPNear", (float*)&NearColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    }
		    
		    ImGui::Separator();
		        	
		    if (ImGui::CollapsingHeader("FOV Settings", nullptr)) {
		    ImGui::Checkbox("Draw FOV Circle", &DrawFOVCircle);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Draw FOV Circle");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Color##ESPFOV", (float*)&FOVColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::Checkbox("Draw Filled FOV Circle", &DrawFilledFOVCircle);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Draw a Filled FOV Circle");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Color##ESPFilledFOV", (float*)&FilledFOVColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
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
		        ImGui::ColorEdit4("Color##ESPCrosshair", (float*)&CrosshairColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    	ImGui::SliderFloat("Crosshair Size", &CrosshairSize, 0, 1000, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the size of the crosshair");
		        ImGui::SliderFloat("Crosshair Thickness", &CrosshairThickness, 1, 50, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the Crosshair's thickness");
		    }
		    
		    ImGui::Separator();
		    
		    ImGui::Text("Misc");
		    ImGui::Checkbox("Show Spectators [!]", &ShowSpectators);
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
            Config::Sense::InvisibleBoxColor = InvisibleBoxColor;
            Config::Sense::VisibleBoxColor = VisibleBoxColor;
            Config::Sense::InvisibleFilledBoxColor = InvisibleFilledBoxColor;
            Config::Sense::VisibleFilledBoxColor = VisibleFilledBoxColor;
            Config::Sense::InvisibleTracerColor = InvisibleTracerColor;
            Config::Sense::VisibleTracerColor = VisibleTracerColor;
            Config::Sense::InvisibleSkeletonColor = InvisibleSkeletonColor;
            Config::Sense::VisibleSkeletonColor = VisibleSkeletonColor;
            Config::Sense::InvisibleNameColor = InvisibleNameColor;
            Config::Sense::VisibleNameColor = VisibleNameColor;
            Config::Sense::InvisibleDistanceColor = InvisibleDistanceColor;
            Config::Sense::VisibleDistanceColor = VisibleDistanceColor;
            Config::Sense::FOVColor = FOVColor;
            Config::Sense::FilledFOVColor = FilledFOVColor;
            Config::Sense::NearColor = NearColor;
            Config::Sense::TeamColor = TeamColor;
            Config::Sense::TeamNameColor = TeamNameColor;
            Config::Sense::CrosshairColor = CrosshairColor;
            
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
		LocalwepID << Myself->WeaponHandle;
		std::string LocalwepInt = LocalwepID.str() + " ";
		const char* LocalwepText = (char*)LocalwepInt.c_str();
		
            	ImGui::Text("Current ID: ");
            	ImGui::SameLine();
            	ImGui::Text(LocalwepText);
            	ImGui::End();
		}
	}*/
        if(!Map->IsPlayable) return;
        if (ShowSpectators) //Crashing
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
        	Renderer::DrawLine(Canvas, Vector2D(x - CrosshairSize, y), Vector2D(x + CrosshairSize, y), CrosshairThickness, CrosshairColor); //Left - right
        	Renderer::DrawLine(Canvas, Vector2D(x, y - CrosshairSize), Vector2D(x, y + CrosshairSize), CrosshairThickness, CrosshairColor); //Top - bottom
        }
 
        // Draw FOV Circle
        if (DrawFOVCircle && Myself->IsCombatReady())
        {
            float FOV = std::min(AimAssistState->FOV, AimAssistState->FOV * (AimAssistState->GetFOVScale() * AimAssistState->ZoomScale));
            float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(GameFOV) / 2) * ScreenWidth;
            Renderer::DrawCircle(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(FOVColor), FOVThickness);
        }
        
        // Draw Filled FOV Circle
        if (DrawFilledFOVCircle && Myself->IsCombatReady())
        {
            float FOV = std::min(AimAssistState->FOV, AimAssistState->FOV * (AimAssistState->GetFOVScale() * AimAssistState->ZoomScale));
            float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(GameFOV) / 2) * ScreenWidth;
            Renderer::DrawCircleFilled(Canvas, Vector2D(ScreenWidth /2, ScreenHeight / 2), Radius, 40, ImColor(FilledFOVColor));
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
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor));
						}
				        	if (p->IsHostile & !p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor));
						}
					}
					
					if (ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor));
						}
				        	if (p->IsHostile & !p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor));
						}
						
						if (p->IsAlly) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, TracerThickness, ImColor(TeamColor));
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
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor));
				        	}
				        	if (p->IsHostile & !p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor));
				        	}
				        }
				        
				        if (ShowTeam) {
				        	if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor));
				        	}
				        	if (p->IsHostile & !p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor));
				        	}
				    		
				    		if (p->IsAlly) {
				    			Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, TracerThickness, ImColor(TeamColor));
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
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor));
				    		}
						if (p->IsHostile & !p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor));
				    		}
					}
					
					if (ShowTeam) {
						if (p->IsHostile & p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(VisibleTracerColor));
				    		}
						if (p->IsHostile & !p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(InvisibleTracerColor));
				    		}
				    		
				    		if (p->IsAlly) {
				    			Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, TracerThickness, ImColor(TeamColor));
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
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor), true, true, false);
						}
						if (p->IsHostile && !p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(InvisibleDistanceColor), true, true, false);
						}
					}
				}
				if (!ShowTeam) {
					if (!distanceScreenPosition.IsZeroVector()) {
						if (p->IsHostile && p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor), true, true, false);
						}
						if (p->IsHostile && !p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(InvisibleDistanceColor), true, true, false);
						}
					}
				}
			}
			
			// Draw Names
			if (DrawNames) {
				Vector2D nameScreenPosition;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head).Add(Vector3D(0, 0, 60)), nameScreenPosition);
				if (p->IsHostile && p->IsVisible && !p->IsDummy()) {
					Renderer::DrawText(Canvas, nameScreenPosition.Subtract(Vector2D(0, 0)), p->GetPlayerName().c_str(), VisibleNameColor, true, true, false);
				}
				if (p->IsHostile && !p->IsVisible && !p->IsDummy()) {
					Renderer::DrawText(Canvas, nameScreenPosition.Subtract(Vector2D(0, 0)), p->GetPlayerName().c_str(), InvisibleNameColor, true, true, false);
				}
				    
				// Draw Team Names
				if (ShowTeam && TeamNames && p->IsAlly && !p->IsDummy()) {
					Renderer::DrawText(Canvas, nameScreenPosition.Add(Vector2D(0, 0)), p->GetPlayerName().c_str(), TeamNameColor, true, true, false);
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
				    			weaponHeldColor = LightWeaponColor;
				    		}
				    		if (weaponHeldID == 81) { //RE-45
				    			weaponHeldText = "RE-45";
				    			weaponHeldColor = LightWeaponColor;
				    		}
				    		if (weaponHeldID == 80) { //Alternator
				    			weaponHeldText = "Alternator";
				    			weaponHeldColor = LightWeaponColor;
				    		}
				    		if (weaponHeldID == 104) { //R-99
				    			weaponHeldText = "R-99";
				    			weaponHeldColor = LightWeaponColor;
				    		}
				    		if (weaponHeldID == 0) { //R-301
				    			weaponHeldText = "R-301";
				    			weaponHeldColor = LightWeaponColor;
				    		}
				    		if (weaponHeldID == 106) { //Spitfire
				    			weaponHeldText = "Spitfire";
				    			weaponHeldColor = LightWeaponColor;
				    		}
				    		if (weaponHeldID == 89) { //G7
				    			weaponHeldText = "G7 Scout";
				    			weaponHeldColor = LightWeaponColor;
				    		}
				    		//Heavy Weapons
				    		if (weaponHeldID == 112) { //CARSMG
				    			weaponHeldText = "CAR SMG";
				    			weaponHeldColor = HeavyWeaponColor;
				    		}
				    		if (weaponHeldID == 21) { //Rampage
				    			weaponHeldText = "Rampage";
				    			weaponHeldColor = HeavyWeaponColor;
				    		}
				    		if (weaponHeldID == 111) { //Repeater
				    			weaponHeldText = "Repeater";
				    			weaponHeldColor = HeavyWeaponColor;
				    		}
				    		if (weaponHeldID == 90) { //Hemlock
				    			weaponHeldText = "Hemlock";
				    			weaponHeldColor = HeavyWeaponColor;
				    		}
				    		if (weaponHeldID == 88) { //Flatline
				    			weaponHeldText = "Flatline";
				    			weaponHeldColor = HeavyWeaponColor;
				    		}
				    		//Energy Weapons
				    		if (weaponHeldID == 113) { //Nemesis
				    			weaponHeldText = "Nemesis";
				    			weaponHeldColor = EnergyWeaponColor;
				    		}
				    		if (weaponHeldID == 110) { //Volt
				    			weaponHeldText = "Volt";
				    			weaponHeldColor = EnergyWeaponColor;
				    		}
				    		if (weaponHeldID == 107) { //TripleTake
				    			weaponHeldText = "Triple Take";
				    			weaponHeldColor = EnergyWeaponColor;
				    		}
				    		if (weaponHeldID == 93) { //LSTAR
				    			weaponHeldText = "L-STAR";
				    			weaponHeldColor = EnergyWeaponColor;
				    		}
				    		if (weaponHeldID == 84) { //Devotion
				    			weaponHeldText = "Devotion";
				    			weaponHeldColor = EnergyWeaponColor;
				    		}
				    		if (weaponHeldID == 86) { //Havoc
				    			weaponHeldText = "Havoc";
				    			weaponHeldColor = EnergyWeaponColor;
				    		}
				    		//Shotguns
				    		if (weaponHeldID == 96) { //Mozambique
				    			weaponHeldText = "Mozambique";
				    			weaponHeldColor = ShotgunWeaponColor;
				    		}
				    		if (weaponHeldID == 87) { //EVA8
				    			weaponHeldText = "EVA-8 Auto";
				    			weaponHeldColor = ShotgunWeaponColor;
				    		}
				    		if (weaponHeldID == 103) { //Peacekeeper
				    			weaponHeldText = "Peacekeeper";
				    			weaponHeldColor = ShotgunWeaponColor;
				    		}
				    		if (weaponHeldID == 95) { //Mastiff
				    			weaponHeldText = "Mastiff";
				    			weaponHeldColor = ShotgunWeaponColor;
				    		}
				    		//Snipers
				    		if (weaponHeldID == 1) { //Sentinel
				    			weaponHeldText = "Sentinel";
				    			weaponHeldColor = SniperWeaponColor;
				    		}
				    		if (weaponHeldID == 83) { //ChargeRifle
				    			weaponHeldText = "Charge Rifle";
				    			weaponHeldColor = SniperWeaponColor;
				    		}
				    		if (weaponHeldID == 85) { //Longbow
				    			weaponHeldText = "Longbow";
				    			weaponHeldColor = SniperWeaponColor;
				    		}
				    		//Legendary Weapons
				    		if (weaponHeldID == 109) { //Wingman
				    			weaponHeldText = "Wingman";
				    			weaponHeldColor = LegendaryWeaponColor;
				    		}
				    		if (weaponHeldID == 102) { //Prowler
				    			weaponHeldText = "Prowler";
				    			weaponHeldColor = LegendaryWeaponColor;
				    		}
				    		if (weaponHeldID == 2) { //Bocek
				    			weaponHeldText = "Bocek";
				    			weaponHeldColor = LegendaryWeaponColor;
				    		}
				    		if (weaponHeldID == 92) { //Kraber
				    			weaponHeldText = "Kraber";
				    			weaponHeldColor = LegendaryWeaponColor;
				    		}
				    		if (weaponHeldID == 163) { //Knife
				    			weaponHeldText = "Throwing Knife";
				    			weaponHeldColor = LegendaryWeaponColor;
				    		}
				    		if (weaponHeldID == 3) { //BusterSword
				    			weaponHeldText = "Buster Sword";
				    			weaponHeldColor = LegendaryWeaponColor;
				    		}
				    		//Melee & Grenade
				    		/*if (weaponHeldID == 213) { //Thermite Grenade
				    			weaponHeldText = "Thermite Grenade";
				    			weaponHeldColor = ThrowableWeaponColor;
				    		}*/
				    		if (p->IsHoldingGrenade) {
				    			weaponHeldText = "Throwable";
				    			weaponHeldColor = ThrowableWeaponColor;
				    		}
				    		if (weaponHeldID == 114) { //Melee
				    			weaponHeldText = "Melee";
				    			weaponHeldColor = MeleeWeaponColor;
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
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 20)), weaponHeldText, ImColor(WeaponColor), true, true, false);
						}
						
						if (DrawWeapon && !DrawStatus) {
							Renderer::DrawText(Canvas, wepScreenPosition.Add(Vector2D(0, 0)), weaponHeldText, ImColor(WeaponColor), true, true, false);
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
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(VisibleBoxColor), BoxThickness);
					}
					if (p->IsHostile && !p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(InvisibleBoxColor), BoxThickness);
					}
				}
				    
				if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(VisibleBoxColor), BoxThickness);
					}
					if (p->IsHostile && !p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(InvisibleBoxColor), BoxThickness);
					}
					if (p->IsAlly) {
						Renderer::DrawBox(Canvas, Foot, Head, ImColor(TeamColor), BoxThickness);
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
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(VisibleFilledBoxColor));
					}
					if (p->IsHostile && !p->IsVisible) {
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(InvisibleFilledBoxColor));
					}
				}
				    
				if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(VisibleFilledBoxColor));
					}
					if (p->IsHostile && !p->IsVisible) {
				        	Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(InvisibleFilledBoxColor));
					}
					if (p->IsAlly) {
						Renderer::DrawFilledBox(Canvas, Foot, Head, ImColor(TeamColor));
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
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, VisibleSkeletonColor);
				    	}
					if (p->IsHostile && !p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, InvisibleSkeletonColor);
				    	}
				}
				    
		 		if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, VisibleSkeletonColor);
				    	}
					if (p->IsHostile && !p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, InvisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, InvisibleSkeletonColor);
				    	}
			    		
			    		if (p->IsAlly) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, TeamColor);
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
		    
 	    	if (VisibilityCheck) { //ONLY shows esp on visible people
		    	if (DrawTracers) {
				PlayersNear++;
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
				        	if (p->IsHostile && p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, 1.5f, ImColor(VisibleTracerColor));
						}
					}
					
					if (ShowTeam) {
				        	if (p->IsHostile && p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, 1.5f, ImColor(VisibleTracerColor));
						}
						
						if (p->IsAlly && p->IsVisible) {
							Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight - ScreenHeight), chestScreenPosition, 1.5f, ImColor(TeamColor));
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
				        	if (p->IsHostile && p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, 1.5f, ImColor(VisibleTracerColor));
				        	}
				        }
				        
				        if (ShowTeam) {
				        	if (p->IsHostile && p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, 1.5f, ImColor(VisibleTracerColor));
				        	}
				    		
				    		if (p->IsAlly && p->IsVisible) {
				    			Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), chestScreenPosition, 1.5f, ImColor(TeamColor));
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
						if (p->IsHostile && p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, 1.5f, ImColor(VisibleTracerColor));
				    		}
					}
					
					if (ShowTeam) {
						if (p->IsHostile && p->IsVisible) {
				        		Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, 1.5f, ImColor(VisibleTracerColor));
				    		}
				    		
				    		if (p->IsAlly && p->IsVisible) {
				    			Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight), chestScreenPosition, 1.5f, ImColor(TeamColor));
			    			}
			    		}
			    	    }
			    	}
			    }

			// Distance
			if (DrawDistance) {
				Vector2D distanceScreenPosition;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head).Add(Vector3D(0, 0, 36)), distanceScreenPosition);

				if (ShowTeam) {
					if (!distanceScreenPosition.IsZeroVector()) {
						if (p->IsAlly && p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(255, 255, 255), true, true, false);
						}
						if (p->IsHostile && p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor), true, true, false);
						}
					}
				}
				if (!ShowTeam) {
					if (!distanceScreenPosition.IsZeroVector()) {
						if (p->IsHostile && p->IsVisible) {
							Renderer::DrawText(Canvas, distanceScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor), true, true, false);
						}
					}
				}
			}
				
			// DrawBox
			if (DrawBox && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(ESPMaxDistance))) {
				Vector2D Head, Foot;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
				    
				if (!ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(VisibleBoxColor), BoxThickness);
					}
				}
				    
				if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
				        	Renderer::DrawBox(Canvas, Foot, Head, ImColor(VisibleBoxColor), BoxThickness);
					}
					
					if (p->IsAlly && p->IsVisible) {
						Renderer::DrawBox(Canvas, Foot, Head, ImColor(TeamColor), BoxThickness);
					}
				}
			}
				
			// Draw Names
			if (DrawNames && p->IsHostile && p->IsVisible && !p->IsDummy()) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 112)), originScreenPosition);
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), p->GetPlayerName().c_str(), VisibleNameColor, true, true, false);
			}
			
			if (DrawNames && p->IsVisible && p->IsDummy()) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 112)), originScreenPosition);
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), "Dummie", VisibleNameColor, true, true, false);
			}
			    
			// Draw Team Names
			if (ShowTeam && TeamNames && p->IsAlly && p->IsVisible && !p->IsDummy()) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 110)), originScreenPosition);
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), p->GetPlayerName().c_str(), TeamNameColor, true, true, false);
			}
			
			// Draw Health + Shield
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
				if (DrawStatus && !ShowMaxStatusValues && p->IsVisible) {
					Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), healthText, ImColor(0, 255, 0), true, true, false);
					Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 10)), shieldText, ShieldColor, true, true, false);
				}
				if (DrawStatus && ShowMaxStatusValues && p->IsVisible) {
					Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), combinedHealthText, ImColor(0, 255, 0), true, true, false);
					Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 10)), combinedShieldText, ShieldColor, true, true, false);
				}
			}
			if (!ShowTeam) {
				if (DrawStatus && !ShowMaxStatusValues && p->IsHostile && p->IsVisible) {
					Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), healthText, ImColor(0, 255, 0), true, true, false);
					Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 10)), shieldText, ShieldColor, true, true, false);
				}
				if (DrawStatus && ShowMaxStatusValues && p->IsHostile && p->IsVisible) {
					Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 0)), combinedHealthText, ImColor(0, 255, 0), true, true, false);
					Renderer::DrawText(Canvas, StatusPos.Add(Vector2D(0, 10)), combinedShieldText, ShieldColor, true, true, false);
				}
			}
			
			//Draw Health Bar
			if (ShowTeam) {
				if (HealthBar && p->IsVisible) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int health = p->Health;
					
					Renderer::DrawHealthBar(Canvas, Foot, Head, health, 2);
				}
			}
			if (!ShowTeam) {
				if (HealthBar && p->IsHostile && p->IsVisible) {
					Vector2D Head, Foot;
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), Head);
					GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 0)), Foot);
					
					int health = p->Health;
					
					Renderer::DrawHealthBar(Canvas, Foot, Head, health, 2);
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
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, VisibleSkeletonColor);
				    	}
				}
				    
		 		if (ShowTeam) {
					if (p->IsHostile && p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, VisibleSkeletonColor);
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, VisibleSkeletonColor);
				    	}
			    		
			    		if (p->IsAlly && p->IsVisible) {
						Renderer::DrawLine(Canvas, Head, Neck, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, TeamColor);
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, TeamColor);
				        }
				}
			}
			
			// Seer
			if (DrawSeer && p->IsVisible) {
				Vector2D headScreenPosition;
				GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Head), headScreenPosition);
				if (!headScreenPosition.IsZeroVector())
				    Renderer::DrawSeer(Canvas, headScreenPosition.x, headScreenPosition.y - 20, p->Shield, p->MaxShield, p->Health);
			    }
			    
			//Show Near
			if (ShowNear && p->IsVisible)
			{
			    // Gui DrawText Version
			    Renderer::DrawText(Canvas, Vector2D(ScreenWidth * 0.5, ScreenHeight * 0.6), ("NEAR : " + std::to_string(PlayersNear)).c_str(), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), true, true, false);
			}
			PlayersNear = 0;
		    }
		}
	   }
    }
};
