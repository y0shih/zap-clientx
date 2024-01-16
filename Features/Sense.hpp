#pragma once
#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/GlowMode.hpp"
#include "../Core/Camera.hpp"

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



struct Sense {
    // Glow
    bool GlowEnabled = false;
    float GlowMaxDistance = 200;
    
    std::vector<GlowMode>* StoredGlowMode = new std::vector<GlowMode>;
    bool ItemGlow = true;
    
    //Drawings
    bool VisibilityCheck = false;
    bool DrawBox = true;
    float BoxThickness = 1.0;
    bool Skeleton = true;
    float SkeletonThickness = 1.0;
    float ESPMaxDistance = 200;
    bool ShowNear = true;
    bool DrawSeer = true;
    bool DrawDistance = true;
    bool DrawFOVCircle = true;
    float FOVThickness = 1.0;
    bool DrawNames = true;
    int TracerPos = 0;
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
    
    //Colors
    ImVec4 InvisibleBoxColor = ImColor(255, 0, 0, 255);
    ImVec4 VisibleBoxColor = ImColor(0, 255, 0, 255);
    ImVec4 InvisibleTracerColor = ImColor(255, 0, 0, 255);
    ImVec4 VisibleTracerColor = ImColor(0, 255, 0, 255);
    ImVec4 InvisibleSkeletonColor = ImColor(255, 255, 255, 255);
    ImVec4 VisibleSkeletonColor = ImColor(255, 255, 255, 255);
    ImVec4 InvisibleNameColor = ImColor(255, 255, 255, 255);
    ImVec4 VisibleNameColor = ImColor(255, 255, 255, 255);
    ImVec4 InvisibleDistanceColor = ImColor(255, 255, 255, 255);
    ImVec4 VisibleDistanceColor = ImColor(255, 255, 255, 255);
    ImVec4 FOVColor = ImColor(255, 255, 255, 255);
    ImVec4 NearColor = ImColor(255, 255, 255, 255);
    ImVec4 TeamColor = ImColor(0, 255, 255, 255);
    ImVec4 TeamNameColor = ImColor(255, 255, 255, 255);
    ImVec4 CrosshairColor = ImColor(255, 255, 255, 255);

    // Variables
    Camera* GameCamera;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;
    std::chrono::milliseconds LastUpdateTime;
    int TotalSpectators = 0;
    std::vector<std::string> Spectators;

    Sense(std::vector<Player*>* Players, Camera* GameCamera, LocalPlayer* Myself) {
        this->Players = Players;
        this->GameCamera = GameCamera;
        this->Myself = Myself;
    }


    void RenderUI() {
    	if (Config::Menu::Layout == 0) {
		if (ImGui::BeginTabItem("Sense", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		
		    // Glow //
		    ImGui::Text("Glow");
		    ImGui::Checkbox("Glow##ESP", &GlowEnabled);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Toggle Glowing\nMay crash when enabled");
		    ImGui::SameLine();
		    ImGui::Checkbox("Item Glow", &ItemGlow);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("You will have Loba's ability to see weapons");
		    ImGui::SliderFloat("Glow Max Distance", &GlowMaxDistance, 0, 1000, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Only those in range will glow");

		    ImGui::Separator();

		    // Drawings
		    ImGui::Text("ESP");
		    
		    ImGui::Separator();
		    
		    ImGui::Text("Checks");
		    ImGui::Checkbox("Visibility Check", &VisibilityCheck);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Draw's ESP ONLY on visible players");
		    ImGui::Checkbox("Show Team", &ShowTeam);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Draw's ESP on Teammates");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Color##ESPTeam", (float*)&TeamColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::Checkbox("Show Team Names", &TeamNames);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Draw Name ESP on Teammates");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Color##ESPTeamName", (float*)&TeamNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);

		    ImGui::Separator();

		    ImGui::Text("Box");
		    ImGui::Checkbox("Draw Box", &DrawBox);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Drawbox on enemy");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Visible Color##ESPBox", (float*)&VisibleBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Invisible Color##ESPBox", (float*)&InvisibleBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::SliderFloat("Box Thickness", &BoxThickness, 1, 10, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Changes the thickness of the boxes");
		    
		    ImGui::Separator();
		    
		    ImGui::Text("Tracers");
		    ImGui::Checkbox("Draw Tracers", &DrawTracers);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Draw lines to enemies");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Visible Color##ESPTracer", (float*)&VisibleTracerColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Invisible Color##ESPTracer", (float*)&InvisibleTracerColor, ImGuiColorEditFlags_NoInputs);
		    const char* TracerPos[] = {"Top", "Crosshair", "Bottom"};
		    int TracerPosition = static_cast<int>(Config::Sense::TracerPos);
		    ImGui::Combo("Tracer Position", &TracerPosition, TracerPos, IM_ARRAYSIZE(TracerPos));
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Where tracers will be drawn from.");
		    Config::Sense::TracerPos = static_cast<int>(TracerPosition);
		    const char* TracerBone[] = {"Top", "Bottom"};
		    int TracerBones = static_cast<int>(Config::Sense::TracerBone);
		    ImGui::Combo("Tracer Bone", &TracerBones, TracerBone, IM_ARRAYSIZE(TracerBone));
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Where tracers will be drawn to.");
		    Config::Sense::TracerBone = static_cast<int>(TracerBones);
		    ImGui::SliderFloat("Tracer Thickness", &TracerThickness, 1, 10, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Changes the thickness of the tracers");
		    
		    ImGui::Separator();
		    
		    ImGui::Text("Skeleton");
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
		    
		    ImGui::Separator();
		    
		    ImGui::Text("Player Info");
		    
		    ImGui::Checkbox("Draw Seer", &DrawSeer);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Draw Seer's abilitiy (Show Health & Armor) on enemies");
		    
		    ImGui::Checkbox("Draw Names", &DrawNames);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Show enemies names");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Visible Color##ESPNames", (float*)&VisibleNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Invisible Color##ESPNames", (float*)&InvisibleNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		          
		        
		    ImGui::Checkbox("Draw Distance", &DrawDistance);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Show how far away the enemies are");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Visible Color##ESPDistance", (float*)&VisibleDistanceColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Invisible Color##ESPDistance", (float*)&InvisibleDistanceColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);


		    ImGui::Checkbox("Show Enemy Count Near", &ShowNear);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Show how many enemies are near");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Color##ESPNear", (float*)&NearColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        	 	
		    ImGui::Separator();    
		        	
		    ImGui::Text("FOV");
		    ImGui::Checkbox("Draw FOV Circle", &DrawFOVCircle);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Draw FOV Circle");
		    ImGui::SameLine();
		    ImGui::ColorEdit4("Color##ESPFOV", (float*)&FOVColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    ImGui::SliderFloat("FOV Circle Thickness", &FOVThickness, 1, 10, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Changes the FOV Circle's thickness\n Recomended: 1-2");
		    ImGui::SliderFloat("Game's FOV", &GameFOV, 70, 120, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Your current FOV in Settings");

		    
		    ImGui::Text("Crosshair");
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
		    
		    ImGui::Separator();
		    
		    ImGui::Text("Misc");
		    ImGui::Checkbox("Show Spectators", &ShowSpectators);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Show spectators");
		        
		    ImGui::Separator();
		        
		    //Sense Settings
		    ImGui::Text("Sense Settings");
		    ImGui::SliderFloat("ESP Max Distance", &ESPMaxDistance, 0, 1000, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		    	ImGui::SetTooltip("Only those in range will ESP");

		    ImGui::EndTabItem();
		}
	}
		
    	if (Config::Menu::Layout == 1) {
		if (ImGui::BeginTabItem("Sense", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		
		    // Glow //
		    ImGui::Text("Glow");
		    ImGui::Checkbox("Glow##ESP", &GlowEnabled);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Toggle Glowing\nMay crash when enabled");
		    ImGui::SameLine();
		    ImGui::Checkbox("Item Glow", &ItemGlow);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("You will have Loba's ability to see weapons");
		    ImGui::SliderFloat("Glow Max Distance", &GlowMaxDistance, 0, 1000, "%.0f");
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Only those in range will glow");

		    ImGui::Separator();

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

		    if (ImGui::CollapsingHeader("Boxes", nullptr)) {
		    	ImGui::Checkbox("Draw Box", &DrawBox);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Drawbox on enemy");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Visible Color##ESPBox", (float*)&VisibleBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPBox", (float*)&InvisibleBoxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SliderFloat("Box Thickness", &BoxThickness, 1, 10, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the thickness of the boxes");
		    }
		    
		    if (ImGui::CollapsingHeader("Tracers", nullptr)) {
		    	ImGui::Checkbox("Draw Tracers", &DrawTracers);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draw lines to enemies");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Visible Color##ESPTracer", (float*)&VisibleTracerColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPTracer", (float*)&InvisibleTracerColor, ImGuiColorEditFlags_NoInputs);
		    	const char* TracerPos[] = {"Top", "Crosshair", "Bottom"};
		    		int TracerPosition = static_cast<int>(Config::Sense::TracerPos);
		    		ImGui::Combo("Tracer Position", &TracerPosition, TracerPos, IM_ARRAYSIZE(TracerPos));
		    		if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        		ImGui::SetTooltip("Where tracers will be drawn from.");
		    		Config::Sense::TracerPos = static_cast<int>(TracerPosition);
		    	const char* TracerBone[] = {"Top", "Bottom"};
		    	int TracerBones = static_cast<int>(Config::Sense::TracerBone);
		    	ImGui::Combo("Tracer Bone", &TracerBones, TracerBone, IM_ARRAYSIZE(TracerBone));
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Where tracers will be drawn to.");
		    	Config::Sense::TracerBone = static_cast<int>(TracerBones);
		        ImGui::SliderFloat("Tracer Thickness", &TracerThickness, 1, 10, "%.0f");
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Changes the thickness of the tracers");
		    }
		    
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
		    
		    if (ImGui::CollapsingHeader("Player Info", nullptr)) {
		        ImGui::Checkbox("Draw Seer", &DrawSeer);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draw Seer's abilitiy (Show Health & Armor) on enemies");
		    
		    	ImGui::Checkbox("Draw Names", &DrawNames);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Show enemies names");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Visible Color##ESPNames", (float*)&VisibleNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPNames", (float*)&InvisibleNameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        
		        ImGui::Checkbox("Draw Distance", &DrawDistance);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Show how far away the enemies are");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Visible Color##ESPDistance", (float*)&VisibleDistanceColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Invisible Color##ESPDistance", (float*)&InvisibleDistanceColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);

		        ImGui::Checkbox("Show Enemy Count Near", &ShowNear);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Show how many enemies are near");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Color##ESPNear", (float*)&NearColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
		    }
		        	
		    if (ImGui::CollapsingHeader("FOV Settings", nullptr)) {
		    	ImGui::Checkbox("Draw FOV Circle", &DrawFOVCircle);
		    	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        	ImGui::SetTooltip("Draw FOV Circle");
		        ImGui::SameLine();
		        ImGui::ColorEdit4("Color##ESPFOV", (float*)&FOVColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
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
		    ImGui::Checkbox("Show Spectators", &ShowSpectators);
		    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		        ImGui::SetTooltip("Show spectators");
		        
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
            Config::Sense::GlowEnabled = GlowEnabled;
            Config::Sense::ItemGlow = ItemGlow;
            Config::Sense::VisibilityCheck = VisibilityCheck;
            Config::Sense::GlowMaxDistance = GlowMaxDistance;
            Config::Sense::DrawSeer = DrawSeer;
            Config::Sense::ShowSpectators = ShowSpectators;
            Config::Sense::DrawFOVCircle = DrawFOVCircle;
            Config::Sense::GameFOV = GameFOV;
            Config::Sense::DrawBox = DrawBox;
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
            Config::Sense::TracerThickness = TracerThickness;
            Config::Sense::TracerPos = static_cast<int>(Modules::Sense::TracerPos);
            Config::Sense::TracerBone = static_cast<int>(Modules::Sense::TracerBone);
            
            //Colors
            Config::Sense::InvisibleBoxColor = InvisibleBoxColor;
            Config::Sense::VisibleBoxColor = VisibleBoxColor;
            Config::Sense::InvisibleTracerColor = InvisibleTracerColor;
            Config::Sense::VisibleTracerColor = VisibleTracerColor;
            Config::Sense::InvisibleSkeletonColor = InvisibleSkeletonColor;
            Config::Sense::VisibleSkeletonColor = VisibleSkeletonColor;
            Config::Sense::InvisibleNameColor = InvisibleNameColor;
            Config::Sense::VisibleNameColor = VisibleNameColor;
            Config::Sense::InvisibleDistanceColor = InvisibleDistanceColor;
            Config::Sense::VisibleDistanceColor = VisibleDistanceColor;
            Config::Sense::FOVColor = FOVColor;
            Config::Sense::NearColor = NearColor;
            Config::Sense::TeamColor = TeamColor;
            Config::Sense::TeamNameColor = TeamNameColor;
            Config::Sense::CrosshairColor = CrosshairColor;
            
            return true;
        } catch (...) {
            return false;
        }
    }
   
    

    void Initialize() {
        for (int placebo = 0; placebo < 101; placebo++) {
            const GlowMode Ehh = { 135, 132, 35, 127 };
            StoredGlowMode->push_back(Ehh);
        }

        const GlowMode FirstStyle = { 135, 135, 128, 64 };
        const GlowMode SecondStyle = { 135, 135, 160, 64 };
        const GlowMode ThirdStyle = { 135, 135, 255, 64 };
        const GlowMode FourthStyle = { 135, 135, 32, 64 };

        StoredGlowMode->push_back(FirstStyle);
        StoredGlowMode->push_back(SecondStyle);
        StoredGlowMode->push_back(ThirdStyle);
        StoredGlowMode->push_back(FourthStyle);
    }

    void RenderDrawings(ImDrawList *Canvas, Aimbot *AimAssistState, LocalPlayer *Myself, Overlay OverlayWindow)
    {
        int ScreenWidth;
        int ScreenHeight;
        OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
        
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
 
        // Draw lot of things
        int PlayersNear = 0;
        for (int i = 0; i < Players->size(); i++)
        {
            Player *p = Players->at(i);
            
	    if (!p->IsLocal && p->IsCombatReady() && p->DistanceToLocalPlayer < (Conversion::ToGameUnits(ESPMaxDistance))) {
 	    	if (!VisibilityCheck) { //Always shows esp
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

			// Distance
			if (DrawDistance) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, -4)), originScreenPosition);
				
				if (ShowTeam) {
					if (!originScreenPosition.IsZeroVector()) {
						if (p->IsAlly) {
							Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(255, 255, 255), true, true, false);
						}
						if (p->IsHostile && p->IsVisible) {
							Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor), true, true, false);
						}
						if (p->IsHostile && !p->IsVisible) {
							Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(InvisibleDistanceColor), true, true, false);
						}
					}
				}
				if (!ShowTeam) {
					if (!originScreenPosition.IsZeroVector()) {
						if (p->IsHostile && p->IsVisible) {
							Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor), true, true, false);
						}
						if (p->IsHostile && !p->IsVisible) {
							Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(InvisibleDistanceColor), true, true, false);
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
				
			// Draw Names
			if (DrawNames && p->IsHostile && p->IsVisible && !p->IsDummy()) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 112)), originScreenPosition);
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), p->GetPlayerName().c_str(), VisibleNameColor, true, true, false);
			}
			if (DrawNames && p->IsHostile && !p->IsVisible && !p->IsDummy()) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 112)), originScreenPosition);
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), p->GetPlayerName().c_str(), InvisibleNameColor, true, true, false);
			}
			
			if (DrawNames && p->IsVisible && p->IsDummy()) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 112)), originScreenPosition);
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), "Dummy", VisibleNameColor, true, true, false);
			}
			if (DrawNames && !p->IsVisible && p->IsDummy()) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 112)), originScreenPosition);
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), "Dummy", InvisibleNameColor, true, true, false);
			}
			    
			// Draw Team Names
			if (ShowTeam && TeamNames && p->IsAlly && !p->IsDummy()) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 110)), originScreenPosition);
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), p->GetPlayerName().c_str(), TeamNameColor, true, true, false);
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
			    Renderer::DrawText(Canvas, Vector2D(ScreenWidth * 0.5, ScreenHeight * 0.6), ("NEAR : " + std::to_string(PlayersNear)).c_str(), NearColor, true, true, false);
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
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, -4)), originScreenPosition);
				
				
				if (!originScreenPosition.IsZeroVector()) {
					if (p->IsAlly && p->IsVisible) {
						Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(255, 255, 255), true, true, false);
				        }
				        if (p->IsHostile && p->IsVisible) {
						Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), std::to_string((int)Conversion::ToMeters(p->DistanceToLocalPlayer)).c_str(), ImColor(VisibleDistanceColor), true, true, false);
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
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), "Dummy", VisibleNameColor, true, true, false);
			}
			    
			// Draw Team Names
			if (ShowTeam && TeamNames && p->IsAlly && p->IsVisible && !p->IsDummy()) {
				Vector2D originScreenPosition;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, 110)), originScreenPosition);
				Renderer::DrawText(Canvas, originScreenPosition.Add(Vector2D(0, 0)), p->GetPlayerName().c_str(), TeamNameColor, true, true, false);
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

    void SetGlowState(long HighlightSettingsPointer, long HighlightSize, int HighlightID, GlowMode NewGlowMode) {
        const GlowMode oldGlowMode = Memory::Read<GlowMode>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 0);
        if (NewGlowMode != oldGlowMode)
            Memory::Write<GlowMode>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 0, NewGlowMode);
    }

    void SetColorState(long HighlightSettingsPointer, long HighlightSize, int HighlightID, Color NewColor) {
        const Color oldColor = Memory::Read<Color>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 4);
        if (oldColor != NewColor)
            Memory::Write<Color>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 4, NewColor);
    }

    void SetGlow(Player* Target, int GlowEnabled, int GlowThroughWall, int HighlightID) {
        if (Target->GlowEnable != GlowEnabled) Memory::Write<int>(Target->BasePointer + OFF_GLOW_ENABLE, GlowEnabled);
        if (Target->GlowThroughWall != GlowThroughWall) {
            Memory::Write<int>(Target->BasePointer + OFF_GLOW_THROUGH_WALL, GlowThroughWall);
            Memory::Write<int>(Target->BasePointer + OFF_GLOW_FIX, 2);
        }
        if (Target->HighlightID != HighlightID) Memory::Write<int>(Target->BasePointer + OFF_GLOW_HIGHLIGHT_ID + 1, HighlightID);
    }

    void Update() {
        const long HighlightSettingsPointer = Memory::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS);
        const long HighlightSize = 0x34;

        // Item Glow //
        if (ItemGlow) {
            for (int highlightId = 34; highlightId < 39; highlightId++) {
                const GlowMode newGlowMode = { 137, 138, 35, 127 };
                SetGlowState(HighlightSettingsPointer, HighlightSize, highlightId, newGlowMode);
            }
        } else {
            for (int highlightId = 34; highlightId < 39; highlightId++) {
                const GlowMode newGlowMode = StoredGlowMode->at(highlightId);
                SetGlowState(HighlightSettingsPointer, HighlightSize, highlightId, newGlowMode);
            }
        }

        // Player Glow //
        // -> Visible
        const GlowMode VisibleMode = { 2, 4, 20, 127 };
        const Color VisibleColor = { 0, 255, 0 };
        SetGlowState(HighlightSettingsPointer, HighlightSize, 0, VisibleMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 0, VisibleColor);

        // -> Invisible
        const GlowMode InvisibleMode = { 2, 4, 20, 127 };
        const Color InvisibleColor = { 255, 0, 0 };
        SetGlowState(HighlightSettingsPointer, HighlightSize, 1, InvisibleMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 1, InvisibleColor);

        // -> Knocked
        const GlowMode KnockedMode = { 2, 4, 20, 127 };
        const Color KnockedColor = { 255, 150, 0 };
        SetGlowState(HighlightSettingsPointer, HighlightSize, 90, KnockedMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 90, KnockedColor);

        // -> Disabled
        const GlowMode DisabledMode = { 0, 0, 0, 0 };
        const Color DisabledColor = { 1, 1, 1 };
        SetGlowState(HighlightSettingsPointer, HighlightSize, 91, DisabledMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 91, DisabledColor);

        // -> Locked On
        const GlowMode LockedOnMode = { 136, 6, 32, 127 };
        const Color LockedOnColor = { 0, 0.75, 0.75 };
        SetGlowState(HighlightSettingsPointer, HighlightSize, 92, LockedOnMode);
        SetColorState(HighlightSettingsPointer, HighlightSize, 92, LockedOnColor);


        for (int i = 0; i < Players->size(); i++) {
            Player* Target = Players->at(i);
            if (!Target->IsValid()) continue;
            if (!Target->IsHostile) continue;

            if (GlowEnabled) {
                if (Target->IsLockedOn) {
                    SetGlow(Target, 1, 2, 92);
                    continue;
                }

                if (Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)) {
                    if (Target->IsKnocked) {
                        SetGlow(Target, 1, 2, 90);
                        continue;
                    }

                    int Highlight = (Target->IsVisible) ? 0 : 1;
                    SetGlow(Target, 1, 2, Highlight);
                    continue;
                }
            }

            SetGlow(Target, 0, 0, 91);
        }
    }
};
