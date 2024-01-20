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

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

struct Misc {
    bool TeamGamemode = true;
    bool Superglide = false;

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
            ImGui::Checkbox("Team Check", &TeamGamemode);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Enable if playing BR, Gun Run or Training\nDisable if playing Control or TDM");
            
            ImGui::Checkbox("Auto Superglide [!!!]", &Superglide);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Hold space whilst climbing over an object to gain extra speed!\n[!!!] It works but breaks the overlay, so I do not recommend using this until I find a fix.");
            ImGui::EndTabItem();
        }
    }

    bool Save() {
        try {
            Config::Misc::TeamGamemode = TeamGamemode;
            Config::Misc::Superglide = Superglide;
            return true;
        } catch (...) {
            return false;
        }
    }

    void Update() {
    	if (Superglide) {
        	while (X11Display->KeyDown(XK_space)) {
           		static float startjumpTime = 0;
            		static bool startSg = false;
            		static float traversalProgressTmp = 0.0;
            		
			float worldtime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE); // Current time
            		float traversalStartTime = Memory::Read<float>(Myself->BasePointer + OFFSET_TRAVERSAL_START_TIME); // Time to start wall climbing
            		float traversalProgress = Memory::Read<float>(Myself->BasePointer + OFFSET_TRAVERSAL_PROGRESS); // Wall climbing, if > 0.87 it is almost over.

            		auto HangOnWall = -(traversalStartTime - worldtime);
 
            		if (HangOnWall > 0.1 && HangOnWall < 0.12) {
            		
                		Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
            		}
            		if (traversalProgress > 0.87f && !startSg && HangOnWall > 0.1f && HangOnWall < 1.5f) {
                		//Start SG
                		startjumpTime = worldtime;
                		startSg = true;
            		}
            		if (startSg) {

                		Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
               		 	while (Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE) - startjumpTime < 0.011);
                	{
                    		Memory::Write<int>(OFF_REGION + OFF_IN_DUCK + 0x8, 6);
                    		std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    		Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
                    		std::this_thread::sleep_for(std::chrono::milliseconds(600));
                	}
                	startSg = false;
                	break;
                 	}
             	}
	}
    }
};
