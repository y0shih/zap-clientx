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

   int MenuLayout = 1;
   int MenuX = 550;
   int MenuY = 730;

   void RenderUI() {
    	if (ImGui::BeginTabItem("Menu", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton)) {
    	    ImGui::Text("Menu Layout");
    	    const char* MenuLayoutChoice[] = {"Simple", "Compact"};
    	    ImGui::Combo("Menu Layout", &MenuLayout, MenuLayoutChoice, IM_ARRAYSIZE(MenuLayoutChoice));
	    Config::Menu::Layout = MenuLayout;
	    
	    ImGui::Text("Menu Size");
	    ImGui::SliderInt("X", &MenuX, 250, 1920);
	    ImGui::SliderInt("Y", &MenuY, 250, 1080);
	    
	    ImGui::EndTabItem();
        }
    }

    bool Save() {
        try {
            Config::Menu::Layout = MenuLayout;
            Config::Menu::MenuX = MenuX;
            Config::Menu::MenuY = MenuY;
            return true;
        } catch (...) {
            return false;
        }
    }

    void Update() { 
    }
};
