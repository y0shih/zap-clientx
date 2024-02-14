#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <unistd.h>

typedef unsigned long DWORD;
typedef int* DWORD_PTR;

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
#include "../Utils/Modules.hpp"
#include "../Utils/HitboxType.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Geometry
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI / 180.f) )
#define ABS(x)  ((x <0) ? (-x) : (x))

struct Glow {
    // Glow
    bool GlowEnabled = false; //OLD GLOW
    bool NewGlow = true;
    float GlowMaxDistance = 200;
    
    int GlowColorMode = 0;
    int GlowColorShieldMode = 0;
    int GlowRadius = 64;
    int InsideFunction = 2; //Leave
    int OutlineFunction = 125; //Leave
    int BodyStyle = 13;
    int OutlineStyle = 1;
    
    std::vector<GlowMode>* StoredGlowMode = new std::vector<GlowMode>;
    bool ItemGlow = true;
    
    //Colors
    float InvisibleGlowColor[3] = {1, 0, 0};
    float VisibleGlowColor[3] = {0, 1, 0};
    float LowGlowColor[3] = {1, 1, 0};
    
    float RedShieldColor[3] = {1, 0, 0};
    float PurpleShieldColor[3] = {0.5, 0, 0.5};
    float BlueShieldColor[3] = {0, 0.5, 1};
    float GreyShieldColor[3] = {0.540, 0.545, 0.545};
    
    // Variables
    Camera* GameCamera;
    Level* Map;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;
    std::chrono::milliseconds LastUpdateTime;
    int TotalSpectators = 0;
    std::vector<std::string> Spectators;

    Glow(Level* Map, std::vector<Player*>* Players, Camera* GameCamera, LocalPlayer* Myself) {
        this->Players = Players;
        this->Map = Map;
        this->GameCamera = GameCamera;
        this->Myself = Myself;
    }


    void RenderUI() {
		if (ImGui::BeginTabItem("Glow", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
            ImVec2 TabSize;
            TabSize = ImGui::GetWindowSize();
            //Glow
            ImGui::Text("Player Glow");
            if (ImGui::BeginChild("Glow Tab", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 270), true)) {
                ImGui::Text("Player Glow Tab");
                ImGui::Checkbox("Enable Glow##ESP", &NewGlow);
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                    ImGui::SetTooltip("Toggle Glowing.");
                
                if (NewGlow) {
                    const char* GlowColorModeIndex[] = {"Shield Based", "Custom Color"};
                    ImGui::Combo("Color Mode", &GlowColorMode, GlowColorModeIndex, IM_ARRAYSIZE(GlowColorModeIndex));
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                        ImGui::SetTooltip("What Color The Glow Will Be.\nShield Based = What Shield The Player Has\nCustom Color = Whatever Color You Want.");
                    
                    if (GlowColorMode == 0) {
                        const char* GlowShieldModeIndex[] = {"Current Shield", "Max Shield"};
                        ImGui::Combo("Shield Mode", &GlowColorShieldMode, GlowShieldModeIndex, IM_ARRAYSIZE(GlowShieldModeIndex));
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                            ImGui::SetTooltip("What Color The Glow Will Change To\nCurrent Shield = Player's Current Shield Points\nMax Shield = Player's Max Shield Points.");
                        ImGui::ColorEdit3("Red Shield##GlowColor", RedShieldColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
                            ImGui::SameLine();
                        ImGui::ColorEdit3("Purple Shield##GlowColor", PurpleShieldColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
                            ImGui::SameLine();
                        ImGui::ColorEdit3("Blue Shield##GlowColor", BlueShieldColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
                            ImGui::SameLine();
                        ImGui::ColorEdit3("Grey Shield##GlowColor", GreyShieldColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
                            ImGui::SameLine();
                    }
                    
                    if (GlowColorMode == 0 && GlowColorShieldMode == 0) {
                        ImGui::ColorEdit3("Low HP Color##GlowColor", LowGlowColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
                            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                            ImGui::SetTooltip("What Color The Glow Will Change To When The Player Has No Shield.");
                            ImGui::SameLine();
                        }
                    
                    if (GlowColorMode == 1) {
                        ImGui::ColorEdit3("Invisible Color##GlowColor", InvisibleGlowColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
                        ImGui::SameLine();
                    }
                    
                    ImGui::ColorEdit3("Visible Color##GlowColor", VisibleGlowColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
                    
                    
                    ImGui::SliderInt("Border Thickness##Glow", &GlowRadius, 32, 200);
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                        ImGui::SetTooltip("How Thick The Border Is Around A Player.");
                    
                    const char* GlowBodyStyleIndex[] = {"None", "Pink", "Pink Visible Only", "Pulsing 1", "Pulsing Line Invisible Only", "Dark Pulsing Line", "Sharp Pulsing Visible", "Sharp Pulsing", "Pulsing Red Line", "Fast Pulsing Invisible Only", "Pulsing Up Visible Only", "Solid Pulsing", "Solid Pulsing 2", "Bright", "Bright 2", "Light", "Light Solid", "Red Pulsing Visible Only", "Wave", "Shaded Visible", "Wireframe", "Wireframe Visible Only", "Black", "Black Visible Only"};
                    ImGui::Combo("Body Style", &BodyStyle, GlowBodyStyleIndex, IM_ARRAYSIZE(GlowBodyStyleIndex));
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                        ImGui::SetTooltip("Changes The Player's Body Style.");
                        
                    const char* GlowOutlineStyleIndex[] = {"None", "Bright", "Bright Invisible Only", "Dark", "Pink", "White", "Gold Flashing", "Gold", "Brown", "Wave", "Red Visible Only", "Red Bright", "Heartbeat Visible Only", "Green Invisible Only", "Visible Only", "Bright Orange", "Red 2"};
                    ImGui::Combo("Outline Style", &OutlineStyle, GlowOutlineStyleIndex, IM_ARRAYSIZE(GlowOutlineStyleIndex));
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                        ImGui::SetTooltip("Changes The Player's Outline Style.");
                }
                ImGui::EndChild();
            }
            
            ImGui::Text("Item Glow");
            if (ImGui::BeginChild("Item Glow", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 285), true)) {
                ImGui::Text("Item Glow Tab");
                ImGui::Checkbox("Item Glow", &ItemGlow);
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                    ImGui::SetTooltip("You will have Loba's ability to see weapons");
                if(ItemGlow) {
                    ImGui::SliderFloat("Glow Max Distance", &GlowMaxDistance, 0, 1000, "%.0f");
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                        ImGui::SetTooltip("Only those in range will glow");
                }
                ImGui::EndChild();
            }

		    ImGui::EndTabItem();
		}
	} //End of RenderUI
    
    bool Save() {
        try {
            Config::Glow::GlowEnabled = GlowEnabled;
            Config::Glow::ItemGlow = ItemGlow;
            Config::Glow::GlowMaxDistance = GlowMaxDistance;
            
            Config::Glow::NewGlow = NewGlow;
            Config::Glow::GlowColorMode = GlowColorMode;
            Config::Glow::GlowColorShieldMode = GlowColorShieldMode;
            Config::Glow::GlowRadius = GlowRadius; //Glow Thickness
            Config::Glow::InsideFunction = InsideFunction; //Leave
            Config::Glow::OutlineFunction = OutlineFunction; //Leave
            Config::Glow::BodyStyle = BodyStyle;
            Config::Glow::OutlineStyle = OutlineStyle;
            Config::Glow::InvisibleGlowColorR = InvisibleGlowColor[0];
            Config::Glow::InvisibleGlowColorG = InvisibleGlowColor[1];
            Config::Glow::InvisibleGlowColorB = InvisibleGlowColor[2];
            Config::Glow::VisibleGlowColorR = VisibleGlowColor[0];
            Config::Glow::VisibleGlowColorG = VisibleGlowColor[1];
            Config::Glow::VisibleGlowColorB = VisibleGlowColor[2];
            Config::Glow::LowGlowColorR = LowGlowColor[0];
            Config::Glow::LowGlowColorG = LowGlowColor[1];
            Config::Glow::LowGlowColorB = LowGlowColor[2];
            Config::Glow::RedShieldColorR = RedShieldColor[0];
            Config::Glow::RedShieldColorG = RedShieldColor[1];
            Config::Glow::RedShieldColorB = RedShieldColor[2];
            Config::Glow::PurpleShieldColorR = PurpleShieldColor[0];
            Config::Glow::PurpleShieldColorG = PurpleShieldColor[1];
            Config::Glow::PurpleShieldColorB = PurpleShieldColor[2];
            Config::Glow::BlueShieldColorR = BlueShieldColor[0];
            Config::Glow::BlueShieldColorG = BlueShieldColor[1];
            Config::Glow::BlueShieldColorB = BlueShieldColor[2];
            Config::Glow::GreyShieldColorR = GreyShieldColor[0];
            Config::Glow::GreyShieldColorG = GreyShieldColor[1];
            Config::Glow::GreyShieldColorB = GreyShieldColor[2];
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
    //Old Glow & Item Glow
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
            Memory::Write<int>(Target->BasePointer + OFF_GLOW_FIX, 1);
        }
        if (Target->HighlightID != HighlightID) Memory::Write<int>(Target->BasePointer + OFF_GLOW_HIGHLIGHT_ID + 1, HighlightID);
    }
    
    
    //New Glow
    void setGlowEnable(Player* Target, int glowEnable)
    {
        long ptrLong = Target->BasePointer + OFF_GLOW_ENABLE;
        Memory::Write<int>(ptrLong, glowEnable);
    }
    void setGlowThroughWall(Player* Target, int glowThroughWall)
    {
        long ptrLong = Target->BasePointer + OFF_GLOW_THROUGH_WALL;
        Memory::Write<int>(ptrLong, glowThroughWall);
    }
    int getGlowThroughWall(Player* Target)
    {
        int ptrInt = Memory::Read<int>(Target->BasePointer + OFF_GLOW_THROUGH_WALL);
        if (!Memory::IsValidPointer(ptrInt))
            return -1;
        return ptrInt;
    }
    int getGlowEnable(Player* Target)
    {
        int ptrInt = Memory::Read<int>(Target->BasePointer + OFF_GLOW_ENABLE);
        if (!Memory::IsValidPointer(ptrInt))
            return -1;
        return ptrInt;
    }
    
    void setCustomGlow(Player* Target, int health, bool isVisible, bool isSameTeam)
    {
        static const int contextId = 0; // Same as glow enable
        long basePointer = Target->BasePointer;
        int settingIndex = 65;
        //Custom Glow Body Style
        if (BodyStyle == 0) { //None
        	InsideFunction = 0;
        }
        if (BodyStyle == 1) { //Pink
        	InsideFunction = 1;
        }
        if (BodyStyle == 2) { //Pink Visible Only
        	InsideFunction = 110;
        }
        if (BodyStyle == 3) { //Pulsing 1
        	InsideFunction = 117;
        }
        if (BodyStyle == 4) { //Pulsing Line Invisible Only
        	InsideFunction = 12;
        }
        if (BodyStyle == 5) { //Dark Pulsing Line
        	InsideFunction = 13;
        }
        if (BodyStyle == 6) { //Sharp Pulsing Visible Only
        	InsideFunction = 124;
        }
        if (BodyStyle == 7) { //Sharp Pulsing
        	InsideFunction = 126;
        }
        if (BodyStyle == 8) { //Pulsing Red Line
        	InsideFunction = 3;
        }
        if (BodyStyle == 9) { //Fast Pulsing Invisible
        	InsideFunction = -500;
        }
        if (BodyStyle == 10) { //Pulsing Up
        	InsideFunction = 132;
        }
        if (BodyStyle == 11) { //Solid Pulsing
        	InsideFunction = 14;
        }
        if (BodyStyle == 12) { //Solid Pulsing 2
        	InsideFunction = 117;
        }
        if (BodyStyle == 13) { //Bright
        	InsideFunction = 109;
        }
        if (BodyStyle == 14) { //Bright 2
        	InsideFunction = 118;
        }
        if (BodyStyle == 15) { //Light
        	InsideFunction = 101;
        }
        if (BodyStyle == 16) { //Light Solid
        	InsideFunction = 112;
        }
        if (BodyStyle == 17) { //Red Pulsing Visible Only
        	InsideFunction = 115;
        }
        if (BodyStyle == 18) { //Wave
        	InsideFunction = 103;
        }
        if (BodyStyle == 19) { //Shaded Visible
        	InsideFunction = 136;
        }
        if (BodyStyle == 20) { //Wireframe
        	InsideFunction = 134;
        }
        if (BodyStyle == 21) { //Wireframe Visible Only
        	InsideFunction = 133;
        }
        if (BodyStyle == 22) { //Black
        	InsideFunction = 75;
        }
        if (BodyStyle == 23) { //Black Visible Only
        	InsideFunction = 77;
        }
        
        //Custom Outline Style
        if (OutlineStyle == 0) { //None
        	OutlineFunction = 0;
        }
        if (OutlineStyle == 1) { //Bright
        	OutlineFunction = 6;
        }
        if (OutlineStyle == 2) { //Bright Invisible Only
        	OutlineFunction = 102;
        }
        if (OutlineStyle == 3) { //Dark
        	OutlineFunction = 101;
        }
        if (OutlineStyle == 4) { //Pink
        	OutlineFunction = 1;
        }
        if (OutlineStyle == 5) { //White
        	OutlineFunction = 4;
        }
        if (OutlineStyle == 6) { //Gold Flashing
        	OutlineFunction = 5;
        }
        if (OutlineStyle == 7) { //Gold
        	OutlineFunction = 7;
        }
        if (OutlineStyle == 8) { //Brown
        	OutlineFunction = 8;
        }
        if (OutlineStyle == 9) { //Wave
        	OutlineFunction = 103;
        }
        if (OutlineStyle == 10) { //Red
        	OutlineFunction = 107;
        }
        if (OutlineStyle == 11) { //Red Bright
        	OutlineFunction = 108;
        }
        if (OutlineStyle == 12) { //Heartbeat Visible Only
        	OutlineFunction = 110;
        }
	if (OutlineStyle == 13) { //Invisible Only Green
        	OutlineFunction = -372;
        }
        if (OutlineStyle == 15) { //Orange
        	OutlineFunction = -249;
        }
        if (OutlineStyle == 14) { //Visible Only
        	OutlineFunction = -151;
        }
        if (OutlineStyle == 16) { //Red
        	OutlineFunction = 364;
        }
        
        std::array<unsigned char, 4> highlightFunctionBits = {
            InsideFunction,   // InsideFunction							2
            OutlineFunction, // OutlineFunction: HIGHLIGHT_OUTLINE_OBJECTIVE			125
            GlowRadius,  // OutlineRadius: size * 255 / 8				64
            64   // (EntityVisible << 6) | State & 0x3F | (AfterPostProcess << 7) 	64
        };
        std::array<float, 3> glowColorRGB = { 0, 0, 0 };
        if (GlowColorMode == 0) {
        	if (GlowColorShieldMode == 0) {
			if (isSameTeam) {
			    settingIndex = 20;
			} else if (!isVisible) {
			    settingIndex = 65;
			    glowColorRGB = {VisibleGlowColor[0], VisibleGlowColor[1], VisibleGlowColor[2]}; // Visible Enemies
			} else if (health >= 201) {
			    settingIndex = 66;
			    glowColorRGB = { RedShieldColor[0], RedShieldColor[1], RedShieldColor[2] }; // red shield
			} else if (health >= 176) {
			    settingIndex = 67;
			    glowColorRGB = { PurpleShieldColor[0], PurpleShieldColor[1], PurpleShieldColor[2] }; // purple shield
			} else if (health >= 151) {
			    settingIndex = 68;
			    glowColorRGB = { BlueShieldColor[0], BlueShieldColor[1], BlueShieldColor[2] }; // blue shield
			} else if (health >= 101) {
			    settingIndex = 69;
			    glowColorRGB = { GreyShieldColor[0], GreyShieldColor[1], GreyShieldColor[2] }; // gray shield // cyan 
			} else {
			    settingIndex = 70;
			    glowColorRGB = {LowGlowColor[0], LowGlowColor[1], LowGlowColor[2]}; // low health enemies // greeen
			}
		}
		
        	if (GlowColorShieldMode == 1) {
			if (isSameTeam) {
			    settingIndex = 20;
			} else if (!isVisible) {
			    settingIndex = 65;
			    glowColorRGB = {VisibleGlowColor[0], VisibleGlowColor[1], VisibleGlowColor[2]}; // Visible Enemies
			} else if (health >= 125) {
			    settingIndex = 66;
			    glowColorRGB = { RedShieldColor[0], RedShieldColor[1], RedShieldColor[2] }; // red shield
			} else if (health >= 100) {
			    settingIndex = 67;
			    glowColorRGB = { PurpleShieldColor[0], PurpleShieldColor[1], PurpleShieldColor[2] }; // purple shield
			} else if (health >= 75) {
			    settingIndex = 68;
			    glowColorRGB = { BlueShieldColor[0], BlueShieldColor[1], BlueShieldColor[2] }; // blue shield
			} else if (health >= 50) {
			    settingIndex = 69;
			    glowColorRGB = { GreyShieldColor[0], GreyShieldColor[1], GreyShieldColor[2] }; // gray shield // cyan 
			} else {
			    settingIndex = 70;
			    glowColorRGB = {LowGlowColor[0], LowGlowColor[1], LowGlowColor[2]}; // low health enemies // greeen
			}
		}
	}
	
        if (GlowColorMode == 1) {
		if (isSameTeam) {
			settingIndex = 20;
		} else if (!isVisible) {
			settingIndex = 65;
			glowColorRGB = {VisibleGlowColor[0], VisibleGlowColor[1], VisibleGlowColor[2]}; // Visible Enemies
		} else if (isVisible) {
			settingIndex = 70;
			glowColorRGB = {InvisibleGlowColor[0], InvisibleGlowColor[1], InvisibleGlowColor[2]}; // Invisible Enemies
		}
	}
	
        Memory::Write<unsigned char>(Target->BasePointer + OFF_GLOW_HIGHLIGHT_ID + contextId, settingIndex);
        
        long highlightSettingsPtr = Memory::Read<long>( OFF_REGION + OFF_GLOW_HIGHLIGHTS);
        if (!isSameTeam) {
            Memory::Write<typeof(highlightFunctionBits)>(
                highlightSettingsPtr + OFF_HIGHLIGHT_TYPE_SIZE * settingIndex + 0, highlightFunctionBits);
            Memory::Write<typeof(glowColorRGB)>(
                highlightSettingsPtr + OFF_HIGHLIGHT_TYPE_SIZE * settingIndex + 4, glowColorRGB);
            Memory::Write<int>(Target->BasePointer + OFF_GLOW_FIX, 0);
        }
    }
    

    void Update() {
    	if(!Map->IsPlayable) return;
        const long HighlightSettingsPointer = Memory::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS);
        const long HighlightSize = OFF_HIGHLIGHT_TYPE_SIZE;

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
        //const GlowMode VisibleMode = { 2, 4, 20, 127 };
        //const Color VisibleColor = { 0, 255, 0 };
        //SetGlowState(HighlightSettingsPointer, HighlightSize, 0, VisibleMode);
        //SetColorState(HighlightSettingsPointer, HighlightSize, 0, VisibleColor);

        // -> Invisible
        //const GlowMode InvisibleMode = { 2, 4, 20, 127 };
        //const Color InvisibleColor = { 255, 0, 0 };
        //SetGlowState(HighlightSettingsPointer, HighlightSize, 1, InvisibleMode);
        //SetColorState(HighlightSettingsPointer, HighlightSize, 1, InvisibleColor);

        // -> Knocked
        //const GlowMode KnockedMode = { 2, 4, 20, 127 };
        //const Color KnockedColor = { 255, 150, 0 };
        //SetGlowState(HighlightSettingsPointer, HighlightSize, 90, KnockedMode);
        //SetColorState(HighlightSettingsPointer, HighlightSize, 90, KnockedColor);

        // -> Disabled
        //const GlowMode DisabledMode = { 0, 0, 0, 0 };
        //const Color DisabledColor = { 1, 1, 1 };
        //SetGlowState(HighlightSettingsPointer, HighlightSize, 91, DisabledMode);
        //SetColorState(HighlightSettingsPointer, HighlightSize, 91, DisabledColor);

        // -> Locked On
        //const GlowMode LockedOnMode = { 136, 6, 32, 127 };
        //const Color LockedOnColor = { 0, 0.75, 0.75 };
        //SetGlowState(HighlightSettingsPointer, HighlightSize, 92, LockedOnMode);
        //SetColorState(HighlightSettingsPointer, HighlightSize, 92, LockedOnColor);

        for (int i = 0; i < Players->size(); i++) {
            Player* Target = Players->at(i);
            if (!Target->IsValid()) continue;
            if (!Target->IsHostile) continue;

	    //Old Glow
            //if (GlowEnabled) {
                //if (Target->IsLockedOn) {
                    //SetGlow(Target, 1, 2, 92);
                    //continue;
                //}

                //if (Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)) {
                    //if (Target->IsKnocked) {
                        //SetGlow(Target, 1, 2, 90);
                        //continue;
                    //}

                    //int Highlight = (Target->IsVisible) ? 0 : 1;
                    //SetGlow(Target, 1, 2, Highlight);
                    //continue;
                //}
            //}

            //SetGlow(Target, 0, 0, 91);
            
            if (NewGlow) {
            	if (GlowColorMode == 0) {
			    if (GlowColorShieldMode == 0) {
				    if (Target->IsVisible && !Target->IsKnocked && Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)) {
					setGlowEnable(Target, 1);
					setGlowThroughWall(Target, 1);
					int healthShield = Target->Health + Target->Shield;
					setCustomGlow(Target, healthShield, true, false);
				    } 
				    if (!Target->IsVisible && !Target->IsKnocked && Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)){
					setGlowEnable(Target, 1);
					setGlowThroughWall(Target, 1);  
					int healthShield = Target->Health + Target->Shield; 
					setCustomGlow(Target, healthShield, true, false);
				    }
				    //If player is out of max distance
				    else if (Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)) {
					setGlowEnable(Target, 1);
					setGlowThroughWall(Target, 1);
					setCustomGlow(Target, 0, false, false);
				    } else if (getGlowEnable(Target) == 1 && getGlowThroughWall(Target) == 1) {
					setGlowEnable(Target, 0);
					setGlowThroughWall(Target, 0);
				    }
				}
				
			    if (GlowColorShieldMode == 1) {
				    if (Target->IsVisible && !Target->IsKnocked && Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)) {
					setGlowEnable(Target, 1);
					setGlowThroughWall(Target, 1);
					int healthShield = Target->MaxShield;
					setCustomGlow(Target, healthShield, true, false);
				    } 
				    if (!Target->IsVisible && !Target->IsKnocked && Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)){
					setGlowEnable(Target, 1);
					setGlowThroughWall(Target, 1);  
					int healthShield = Target->MaxShield; 
					setCustomGlow(Target, healthShield, true, false);
				    }
				    //If player is out of max distance
				    else if (Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)) {
					setGlowEnable(Target, 1);
					setGlowThroughWall(Target, 1);
					setCustomGlow(Target, 0, false, false);
				    } else if (getGlowEnable(Target) == 1 && getGlowThroughWall(Target) == 1) {
					setGlowEnable(Target, 0);
					setGlowThroughWall(Target, 0);
				    }
			    }
		}
		
		if (GlowColorMode == 1) {
			    if (Target->IsVisible && !Target->IsKnocked && Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)) {
				setGlowEnable(Target, 1);
				setGlowThroughWall(Target, 1);
				int healthShield = Target->MaxShield;
				setCustomGlow(Target, healthShield, true, false);
			    } 
			    if (!Target->IsVisible && !Target->IsKnocked && Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)){
				setGlowEnable(Target, 1);
				setGlowThroughWall(Target, 1);  
				int healthShield = Target->MaxShield; 
				setCustomGlow(Target, healthShield, true, false);
			    }
			    //If player is out of max distance
			    else if (Target->DistanceToLocalPlayer < Conversion::ToGameUnits(GlowMaxDistance)) {
				setGlowEnable(Target, 1);
				setGlowThroughWall(Target, 1);
				setCustomGlow(Target, 0, false, false);
			    } else if (getGlowEnable(Target) == 1 && getGlowThroughWall(Target) == 1) {
				setGlowEnable(Target, 0);
				setGlowThroughWall(Target, 0);
			    }
		    }
		
	   }
        }
    }
};
