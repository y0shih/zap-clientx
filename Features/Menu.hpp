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

#include "../Overlay/Overlay.hpp"

#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/QAngle.hpp"
#include "../Math/Resolver.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

struct MenuUI {

   int MenuLayout;

   void RenderUI() {
    	if (ImGui::BeginTabItem("Menu", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
    	    ImGui::Text("Menu Layout");
    	    const char* MenuLayoutChoice[] = {"Simple", "Compact"};
    	    static int MenuLayout = Modules::Menu::Layout;
    	    ImGui::Combo("Menu Layout", &MenuLayout, MenuLayoutChoice, IM_ARRAYSIZE(MenuLayoutChoice));
	    Config::Menu::Layout = MenuLayout;
            ImGui::Text("Menu Theme");
	    ImGui::Text("WIP (Work In Progress)");
            	
            ImGui::EndTabItem();
        }
    }

    bool Save() {
        try {
            Config::Menu::Layout = MenuLayout;
            return true;
        } catch (...) {
            return false;
        }
    }

    void Update() { 	
    }
};
