// Externals
#pragma once
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#define GLFW_EXPOSE_NATIVE_X11
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Internals
#include "Font.hpp"
#include "../Utils/InputManager.hpp"
#include "Utils/Themes.hpp"
#include "Utils/Config.hpp"
#include "../Utils/Modules.hpp"

class Overlay {
private:
GLFWwindow* OverlayWindow;
    int ScreenWidth;
    int ScreenHeight;
    int ScreenPosX;
    int ScreenPosY;
 
    void GrabScreenSize() {
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);
        glfwGetMonitorPos(primaryMonitor, &ScreenPosX, &ScreenPosY);
        ScreenWidth = vidMode->width;
        ScreenHeight = vidMode->height;
    }

    std::string RandomString(int ch) {
        char alpha[35] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                            'h', 'i', 'j', 'k', 'l', 'm', 'n',
                            'o', 'p', 'q', 'r', 's', 't', 'u',
                            'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        std::string result = "";
        for (int i = 0; i<ch; i++)
            result = result + alpha[rand() % 35];
        return result;
    }

    static void GLFWErrorCallback(int error, const char *description) {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }

    long long CurrentEpochMilliseconds() {
        auto currentTime = std::chrono::system_clock::now();
        auto duration = currentTime.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    ImWchar *GetFontGlyphRanges() noexcept
    {
        static ImVector<ImWchar> ranges;
        if (ranges.empty())
        {
            ImFontGlyphRangesBuilder builder;
            constexpr ImWchar baseRanges[] = {
                0x0100, 0x024F, // Latin Extended-A + Latin Extended-B
                0x0300, 0x03FF, // Combining Diacritical Marks + Greek/Coptic
                0x0600, 0x06FF, // Arabic
                0x0E00, 0x0E7F, // Thai
                0
            };
            builder.AddRanges(baseRanges);
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesDefault());
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
            // ★龍王™
            builder.AddChar(u'\u2605'); // ★
            builder.AddChar(u'\u9F8D'); // 龍
            builder.AddChar(u'\u738B'); // 王
            builder.AddChar(u'\u2122'); // ™
            builder.BuildRanges(&ranges);
        }
        return ranges.Data;
    }

public:
    int ProcessingTime;
    long long StartTime;
    int SleepTime;
    int TimeLeftToSleep;
    
    int AsciiArt = 5;
    int AsciiArtSpeed = 100;
    int ThemeStyle;
    int ThemeColor;
    bool TeamGamemode = true;
    bool ErrorLogging = false;

    bool InitializeOverlay() {
        glfwSetErrorCallback(GLFWErrorCallback);
        if (!glfwInit()) {
            return false;
        }

        GrabScreenSize();
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwDefaultWindowHints();

        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_REFRESH_RATE, 60);

        OverlayWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, RandomString(12).c_str(), NULL, NULL);

        glfwSetWindowPos(OverlayWindow, ScreenPosX, ScreenPosY);
        CaptureInput(true);
        glfwMakeContextCurrent(OverlayWindow);
        
        // Centering //
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);
        glfwSetWindowPos(OverlayWindow, (vidMode->width - ScreenWidth) / 2, (vidMode->height - ScreenHeight) / 2);
        // End of Centering //

        InitializeUI();

        glfwShowWindow(OverlayWindow);
        glfwSwapInterval(0);

        return true;
    }

    void InitializeUI() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImFontConfig cfg;
        cfg.OversampleH = cfg.OversampleV = 1;
        cfg.PixelSnapH = true;
        cfg.SizePixels = 13.0f;
        cfg.GlyphOffset = {1.0f, -1.0f};
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.Fonts->AddFontFromMemoryCompressedTTF(_compressedFontData, _compressedFontSize, cfg.SizePixels, &cfg, GetFontGlyphRanges());

        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding                     = ImVec2(8.00f, 8.00f);
	style.FramePadding                      = ImVec2(5.00f, 2.00f);
	style.CellPadding                       = ImVec2(6.00f, 6.00f);
	style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
	style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
	style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
	style.IndentSpacing                     = 25;
	style.ScrollbarSize                     = 12;
	style.GrabMinSize                       = 10;
	style.WindowBorderSize                  = 1;
	style.ChildBorderSize                   = 1;
	style.PopupBorderSize                   = 1;
	style.FrameBorderSize                   = 1;
	style.TabBorderSize                     = 1;
	style.WindowRounding                    = 7;
	style.ChildRounding                     = 4;
	style.FrameRounding                     = 3;
	style.PopupRounding                     = 4;
	style.ScrollbarRounding                 = 9;
	style.GrabRounding                      = 3;
	style.LogSliderDeadzone                 = 4;
	style.TabRounding                       = 4;

	style.Colors[ImGuiCol_Text]                   = Text;
  	style.Colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  	style.Colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  	style.Colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  	style.Colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  	style.Colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
  	style.Colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  	style.Colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  	style.Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  	style.Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  	style.Colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  	style.Colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  	style.Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  	style.Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  	style.Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.00f);
  	style.Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  	style.Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  	style.Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
 	style.Colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
 	style.Colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  	style.Colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  	style.Colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  	style.Colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  	style.Colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  	style.Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  	style.Colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  	style.Colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  	style.Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  	style.Colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  	style.Colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  	style.Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  	style.Colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  	style.Colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  	style.Colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  	style.Colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  	style.Colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  	style.Colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  	style.Colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  	style.Colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  	style.Colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  	style.Colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  	style.Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  	style.Colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  	style.Colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  	style.Colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  	style.Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  	style.Colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  	style.Colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  	style.Colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  	style.Colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
  	style.Colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
  	style.Colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

        ImGui_ImplGlfw_InitForOpenGL(OverlayWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    bool AlignedButton(const char* label, float alignment = 0.5f) {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Button(label);
    }
		//Style
		float Alpha 			       = 1.0f;
		float DisabledAlpha 		       = 1.0f;
		float TabMinWidthForCloseButton        = 0.0f;
		float ColumnsMinSpacing 	       = 6.0f;
		ImVec2 WindowPadding                   = ImVec2(8.00f, 8.00f);
		ImVec2 FramePadding                    = ImVec2(5.00f, 2.00f);
		ImVec2 CellPadding                     = ImVec2(6.00f, 6.00f);
		ImVec2 ItemSpacing                     = ImVec2(6.00f, 6.00f);
		ImVec2 ItemInnerSpacing                = ImVec2(6.00f, 6.00f);
		ImVec2 TouchExtraPadding               = ImVec2(0.00f, 0.00f);
		ImVec2 SelectableTextAlign             = ImVec2(0.0f, 0.0f);
		ImVec2 ButtonTextAlign 		       = ImVec2(0.5f, 0.5f);
		ImVec2 WindowTitleAlign                = ImVec2(0.5f, 0.5f);
		ImVec2 WindowMinSize                   = ImVec2(20.0f, 20.0f);
		int IndentSpacing                      = 25;
		int ScrollbarSize                      = 12;
		int GrabMinSize                        = 10;
		int WindowBorderSize                   = 1;
		int ChildBorderSize                    = 1;
		int PopupBorderSize                    = 1;
		int FrameBorderSize                    = 1;
		int TabBorderSize                      = 1;
		int WindowRounding                     = 7;
		int ChildRounding                      = 4;
		int FrameRounding                      = 3;
		int PopupRounding                      = 4;
		int ScrollbarRounding                  = 9;
		int GrabRounding                       = 3;
		int LogSliderDeadzone                  = 4;
		int TabRounding                        = 4;
		
		//Colors
	    ImVec4 Text                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	  	ImVec4 TextDisabled           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	  	ImVec4 WindowBg               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	  	ImVec4 ChildBg                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	  	ImVec4 PopupBg                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	  	ImVec4 Border                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	  	ImVec4 BorderShadow           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	  	ImVec4 FrameBg                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	  	ImVec4 FrameBgHovered         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	  	ImVec4 FrameBgActive          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	  	ImVec4 TitleBg                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	  	ImVec4 TitleBgActive          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	  	ImVec4 TitleBgCollapsed       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	  	ImVec4 MenuBarBg              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	  	ImVec4 ScrollbarBg            = ImVec4(0.05f, 0.05f, 0.05f, 0.00f);
	  	ImVec4 ScrollbarGrab          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	  	ImVec4 ScrollbarGrabHovered   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	  	ImVec4 ScrollbarGrabActive    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	 	ImVec4 CheckMark              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		ImVec4 SliderGrab             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	 	ImVec4 SliderGrabActive       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	  	ImVec4 Button                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	  	ImVec4 ButtonHovered          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	  	ImVec4 ButtonActive           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	  	ImVec4 Header                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	  	ImVec4 HeaderHovered          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	  	ImVec4 HeaderActive           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	  	ImVec4 Separator              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	  	ImVec4 SeparatorHovered       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	  	ImVec4 SeparatorActive        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	  	ImVec4 ResizeGrip             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	  	ImVec4 ResizeGripHovered      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	  	ImVec4 ResizeGripActive       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	  	ImVec4 Tab                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	  	ImVec4 TabHovered             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	  	ImVec4 TabActive              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
	  	ImVec4 TabUnfocused           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	  	ImVec4 TabUnfocusedActive     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	  	ImVec4 PlotLines              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	  	ImVec4 PlotLinesHovered       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	  	ImVec4 PlotHistogram          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	  	ImVec4 PlotHistogramHovered   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	  	ImVec4 TableHeaderBg          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	  	ImVec4 TableBorderStrong      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	  	ImVec4 TableBorderLight       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	  	ImVec4 TableRowBg             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	  	ImVec4 TableRowBgAlt          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	  	ImVec4 TextSelectedBg         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	  	ImVec4 DragDropTarget         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	  	ImVec4 NavHighlight           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	  	ImVec4 NavWindowingHighlight  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	  	ImVec4 NavWindowingDimBg      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	  	ImVec4 ModalWindowDimBg       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

    void SetUIStyle() {
    	if (ImGui::BeginTabItem("Home", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton)) {
			ImVec2 TabSize;
			TabSize = ImGui::GetWindowSize();
			ImGui::Text("Homepage");
			if (ImGui::BeginChild("Homepage", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 154), true, ImGuiWindowFlags_NoScrollbar)) {
				ImGui::Text("Info: ");
				ImGui::TextColored(ImVec4(1, 0, 0, 1),"Detection Status: ");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(0, 1, 0, 1), "Undetected");
				ImGui::Text("(Disclamer: I'm not responsible for any bans)");
				ImGui::Text("ESP/Aimbot not working? Sounds like a config issue ngl... (Hint: Team Check, Smoothing Settings)");
				ImGui::Text("Got banned? Just create a new account and/or change config.");
				ImGui::Separator();
				ImGui::Text("Main Settings");
				ImGui::Checkbox("Team Check", &TeamGamemode);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Enable if playing BR, Gun Run or Training\nDisable if playing Control or TDM");
				Modules::Home::TeamGamemode = TeamGamemode;

				ImGui::EndChild();
			}

			ImGui::Text("Menu Configuration");
			if (ImGui::BeginChild("Menu Configuration", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 145), true, ImGuiWindowFlags_NoScrollbar)) {
			ImGui::Text("Menu Configration Tab");
	    	ImGui::SliderInt("Menu Width", &Modules::Home::MenuX, 250, 1920);
	    	//ImGui::SliderInt("Y", &Modules::Home::MenuY, 250, 1080);
    		ImGui::Text("Style Selection");
    		if (ImGui::Button("Original##Theme")) {
    		    ThemeStyle = 0;
				Alpha                   = 1.0f;             
				WindowPadding           = ImVec2(8,8);      
				WindowRounding          = 0.0f;             
				WindowBorderSize        = 1.0f;             
				WindowMinSize           = ImVec2(32,32);    
				WindowTitleAlign        = ImVec2(0.0f,0.5f);
				ChildRounding           = 0.0f;             
				ChildBorderSize         = 1.0f;             
				PopupRounding           = 0.0f;            
				PopupBorderSize         = 1.0f;        
				FramePadding            = ImVec2(4,3);    
				FrameRounding           = 0.0f;          
				FrameBorderSize         = 0.0f;       
				ItemSpacing             = ImVec2(8,4);    
				ItemInnerSpacing        = ImVec2(4,4);     
				CellPadding             = ImVec2(4,2);      
				TouchExtraPadding       = ImVec2(0,0);     
				IndentSpacing           = 21.0f;          
				ColumnsMinSpacing       = 6.0f;            
				ScrollbarSize           = 12.0f;          
				ScrollbarRounding       = 9.0f;         
				GrabMinSize             = 10.0f;      
				GrabRounding            = 0.0f;          
				LogSliderDeadzone       = 4.0f;             
				TabRounding             = 4.0f;         
				TabBorderSize           = 0.0f;            
				TabMinWidthForCloseButton = 0.0f;           
				ButtonTextAlign         = ImVec2(0.5f,0.5f);
				SelectableTextAlign     = ImVec2(0.0f,0.0f);
    		}

    		ImGui::SameLine();
    		if (ImGui::Button("xap-client##Theme")) {
    			ThemeStyle = 1;
	    		Alpha 			= 1.0f;
				DisabledAlpha 		= 1.0f;
				WindowPadding 		= ImVec2(12.0f, 12.0f);
				WindowRounding 		= 0.0f;
				WindowBorderSize 	= 0.0f;
				WindowMinSize 		= ImVec2(20.0f, 20.0f);
				WindowTitleAlign 	= ImVec2(0.5f, 0.5f);
				ChildRounding 		= 0.0f;
				ChildBorderSize 	= 1.0f;
				PopupRounding 		= 0.0f;
				PopupBorderSize 	= 1.0f;
				FramePadding 		= ImVec2(6.0f, 6.0f);
				FrameRounding 		= 0.0f;
				FrameBorderSize 	= 0.0f;
				ItemSpacing 		= ImVec2(12.0f, 6.0f);
				ItemInnerSpacing 	= ImVec2(6.0f, 3.0f);
				CellPadding 		= ImVec2(12.0f, 6.0f);
				IndentSpacing 		= 20.0f;
				ColumnsMinSpacing 	= 6.0f;
				ScrollbarSize 		= 12.0f;
				ScrollbarRounding 	= 0.0f;
				GrabMinSize 		= 12.0f;
				GrabRounding 		= 0.0f;
				TabRounding 		= 0.0f;
				TabBorderSize 		= 0.0f;
				TabMinWidthForCloseButton = 0.0f;
				ButtonTextAlign 	= ImVec2(0.5f, 0.5f);
				SelectableTextAlign 	= ImVec2(0.0f, 0.0f);
				LogSliderDeadzone 	= 4;
    		}

    		ImGui::SameLine();
    	    if (ImGui::Button("EmbraceTheDarkness##Theme")) {
    	    	ThemeStyle = 2;
    	    	Alpha 				= 1.0f;
				DisabledAlpha 			= 1.0f;
    			WindowPadding                   = ImVec2(8.00f, 8.00f);
				FramePadding                    = ImVec2(5.00f, 2.00f);
				CellPadding                     = ImVec2(6.00f, 6.00f);
				ItemSpacing                     = ImVec2(6.00f, 6.00f);
				ItemInnerSpacing                = ImVec2(6.00f, 6.00f);
				TouchExtraPadding               = ImVec2(0.00f, 0.00f);
				WindowTitleAlign                = ImVec2(0.5f, 0.5f);
				IndentSpacing                      = 25;
				ScrollbarSize                      = 12;
				GrabMinSize                        = 10;
				WindowBorderSize                   = 1;
				ChildBorderSize                    = 1;
				PopupBorderSize                    = 1;
				FrameBorderSize                    = 1;
				TabBorderSize                      = 1;
				WindowRounding                     = 7;
				ChildRounding                      = 4;
				FrameRounding                      = 3;
				PopupRounding                      = 4;
				ScrollbarRounding                  = 9;
				GrabRounding                       = 3;
				LogSliderDeadzone                  = 4;
				TabRounding                        = 4;
    		}

    		ImGui::SameLine();
    		if (ImGui::Button("Enemymouse##Theme")) {
    			ThemeStyle = 3;
		    	Alpha = 1.0f;
			DisabledAlpha = 1.0f;
			WindowPadding = ImVec2(12.0f, 12.0f);
			WindowRounding = 3.0f;
			WindowBorderSize = 0.0f;
			WindowMinSize = ImVec2(20.0f, 20.0f);
			WindowTitleAlign = ImVec2(0.5f, 0.5f);
			ChildRounding = 3.0f;
			ChildBorderSize = 1.0f;
			PopupRounding = 0.0f;
			PopupBorderSize = 1.0f;
			FramePadding = ImVec2(6.0f, 6.0f);
			FrameRounding = 3.0f;
			FrameBorderSize = 0.0f;
			ItemSpacing = ImVec2(12.0f, 6.0f);
			ItemInnerSpacing = ImVec2(6.0f, 3.0f);
			CellPadding = ImVec2(12.0f, 6.0f);
			IndentSpacing = 20.0f;
			ColumnsMinSpacing = 6.0f;
			ScrollbarSize = 12.0f;
			ScrollbarRounding = 0.0f;
			GrabMinSize = 20.0f;
			GrabRounding = 1.0f;
			TabRounding = 0.0f;
			TabBorderSize = 0.0f;
			TabMinWidthForCloseButton = 0.0f;
			ButtonTextAlign = ImVec2(0.5f, 0.5f);
			SelectableTextAlign = ImVec2(0.0f, 0.0f);
    		}
    		
    		ImGui::SameLine();
    	    	if (ImGui::Button("Cyberpunk##Theme")) {
    	    		ThemeStyle = 4;
    	    		Alpha 				= 1.0f;
			DisabledAlpha 			= 1.0f;
    			WindowPadding                   = ImVec2(8.00f, 8.00f);
			FramePadding                    = ImVec2(5.00f, 2.00f);
		 	CellPadding                     = ImVec2(6.00f, 6.00f);
		 	ItemSpacing                     = ImVec2(6.00f, 6.00f);
		 	ItemInnerSpacing                = ImVec2(6.00f, 6.00f);
			TouchExtraPadding               = ImVec2(0.00f, 0.00f);
			WindowTitleAlign                = ImVec2(0.5f, 0.5f);
			IndentSpacing                      = 25;
			ScrollbarSize                      = 12;
			GrabMinSize                        = 10;
			WindowBorderSize                   = 1;
			ChildBorderSize                    = 1;
			PopupBorderSize                    = 1;
			FrameBorderSize                    = 1;
			TabBorderSize                      = 1;
			WindowRounding                     = 7;
			ChildRounding                      = 4;
			FrameRounding                      = 3;
			PopupRounding                      = 4;
			ScrollbarRounding                  = 9;
			GrabRounding                       = 3;
			LogSliderDeadzone                  = 4;
			TabRounding                        = 4;
    		}
    		
    		ImGui::SameLine();
    		if (ImGui::Button("Moonlight##Theme")) {
    			ThemeStyle = 5;
			Alpha = 1.0f;
			DisabledAlpha = 1.0f;
			WindowPadding = ImVec2(12.0f, 12.0f);
			WindowRounding = 11.5f;
			WindowBorderSize = 0.0f;
			WindowMinSize = ImVec2(20.0f, 20.0f);
			WindowTitleAlign = ImVec2(0.5f, 0.5f);
			ChildRounding = 0.0f;
			ChildBorderSize = 1.0f;
			PopupRounding = 0.0f;
			PopupBorderSize = 1.0f;
			FramePadding = ImVec2(20.0f, 3.400000095367432f);
			FrameRounding = 11.89999961853027f;
			FrameBorderSize = 0.0f;
			ItemSpacing = ImVec2(4.300000190734863f, 5.5f);
			ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
			CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
			IndentSpacing = 0.0f;
			ColumnsMinSpacing = 4.900000095367432f;
			ScrollbarSize = 12.0f;
			ScrollbarRounding = 15.89999961853027f;
			GrabMinSize = 3.700000047683716f;
			GrabRounding = 20.0f;
			TabRounding = 0.0f;
			TabBorderSize = 0.0f;
			TabMinWidthForCloseButton = 0.0f;
			ButtonTextAlign = ImVec2(0.5f, 0.5f);
			SelectableTextAlign = ImVec2(0.0f, 0.0f);
		}
		ImGui::SameLine();
    		if (ImGui::Button("Vine##Theme")) {
    		    ThemeStyle = 6;
			Alpha = 1.0f;
			DisabledAlpha = 0.20f;
			WindowPadding = ImVec2(8.0f, 8.0f);
			WindowRounding = 4.0f;
			WindowBorderSize = 0.0f;
			WindowMinSize = ImVec2(32.0f, 32.0f);
			WindowTitleAlign = ImVec2(0.5f, 0.5f);
			ChildRounding = 4.0f;
			ChildBorderSize = 1.0f;
			PopupRounding = 4.0f;
			PopupBorderSize = 1.0f;
			FramePadding = ImVec2(14.30f, 5.0f);
			FrameRounding = 4.0f;
			FrameBorderSize = 0.0f;
			ItemSpacing = ImVec2(8.0f, 4.0f);
			ItemInnerSpacing = ImVec2(4.0f, 4.0f);
			CellPadding = ImVec2(4.0f, 2.0f);
			IndentSpacing = 21.0f;
			ColumnsMinSpacing = 6.0f;
			ScrollbarSize = 12.0f;
			ScrollbarRounding = 9.0f;
			GrabMinSize = 9.89f;
			GrabRounding = 0.0f;
			TabRounding = 4.0f;
			TabBorderSize = 0.0f;
			TabMinWidthForCloseButton = 0.0f;
			ButtonTextAlign = ImVec2(0.5f, 0.5f);
			SelectableTextAlign = ImVec2(0.0f, 0.0f);
		}
		
    		ImGui::Separator();
    		
    		ImGui::Text("Color Selection");
    		if (ImGui::Button("Original##Color")) {
    		    ThemeColor = 0;
		    Text                   = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		    TextDisabled           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		    WindowBg               = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		    ChildBg                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		    PopupBg                = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
		    Border                 = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
		    BorderShadow           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		    FrameBg                = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
		    FrameBgHovered         = ImVec4(0.47f, 0.47f, 0.69f, 0.40f);
		    FrameBgActive          = ImVec4(0.42f, 0.41f, 0.64f, 0.69f);
		    TitleBg                = ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
		    TitleBgActive          = ImVec4(0.32f, 0.32f, 0.63f, 0.87f);
		    TitleBgCollapsed       = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
		    MenuBarBg              = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
		    ScrollbarBg            = ImVec4(0.20f, 0.25f, 0.30f, 0.00f);
		    ScrollbarGrab          = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
		    ScrollbarGrabHovered   = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
		    ScrollbarGrabActive    = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
		    CheckMark              = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
		    SliderGrab             = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		    SliderGrabActive       = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
		    Button                 = ImVec4(0.35f, 0.40f, 0.61f, 0.62f);
		    ButtonHovered          = ImVec4(0.40f, 0.48f, 0.71f, 0.79f);
		    ButtonActive           = ImVec4(0.46f, 0.54f, 0.80f, 1.00f);
		    Header                 = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
		    HeaderHovered          = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
		    HeaderActive           = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
		    Separator              = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
		    SeparatorHovered       = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
		    SeparatorActive        = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);
		    ResizeGrip             = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
		    ResizeGripHovered      = ImVec4(0.78f, 0.82f, 1.00f, 0.60f);
		    ResizeGripActive       = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);
		    TabHovered             = HeaderHovered;
		    PlotLines              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		    PlotLinesHovered       = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		    PlotHistogram          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		    PlotHistogramHovered   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		    TableHeaderBg          = ImVec4(0.27f, 0.27f, 0.38f, 1.00f);
		    TableBorderStrong      = ImVec4(0.31f, 0.31f, 0.45f, 1.00f);   // Prefer using Alpha=1.0 here
		    TableBorderLight       = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);   // Prefer using Alpha=1.0 here
		    TableRowBg             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		    TableRowBgAlt          = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
		    TextSelectedBg         = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
		    DragDropTarget         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		    NavHighlight           = HeaderHovered;
		    NavWindowingHighlight  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		    NavWindowingDimBg      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		    ModalWindowDimBg       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    		}
    		ImGui::SameLine();
    		if (ImGui::Button("xap-client##Color")) {
    			ThemeColor = 1;
			Text 			= ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			TextDisabled 		= ImVec4(0.27f, 0.31f, 0.45f, 1.0f);
			WindowBg 		= ImVec4(0.07f, 0.08f, 0.10f, 1.00f);
			ChildBg 		= ImVec4(0.078f, 0.08f, 0.10f, 1.0f);
			PopupBg 		= ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			Border 			= ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
			BorderShadow 		= ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			FrameBg 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			FrameBgHovered 		= ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
			FrameBgActive 		= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
			TitleBg 		= ImVec4(0.047f, 0.05f, 0.07f, 1.0f);
			TitleBgActive 		= ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
			TitleBgCollapsed 	= ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			MenuBarBg 		= ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
			ScrollbarBg 		= ImVec4(0.04f, 0.05f, 0.07f, 0.00f);
			ScrollbarGrab 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			ScrollbarGrabHovered 	= ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
			ScrollbarGrabActive 	= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			CheckMark 		= ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
			SliderGrab 		= ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
			SliderGrabActive 	= ImVec4(0.53f, 0.55f, 1.0f, 1.0f);
			Button 			= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			ButtonHovered 		= ImVec4(0.19f, 0.17f, 0.54f, 1.0f);
			ButtonActive 		= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
			Header 			= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			HeaderHovered 		= ImVec4(0.19f, 0.17f, 0.54f, 1.0f);
			HeaderActive 		= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
			Separator 		= ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
			SeparatorHovered 	= ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
			SeparatorActive 	= ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
			ResizeGrip 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			ResizeGripHovered 	= ImVec4(0.19f, 0.17f, 0.54f, 1.0f);
			ResizeGripActive 	= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
			Tab 			= ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
			TabHovered 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			TabActive 		= ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
			TabUnfocused 		= ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
			TabUnfocusedActive 	= ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			PlotLines 		= ImVec4(0.52f, 0.60f, 0.70f, 1.0f);
			PlotLinesHovered 	= ImVec4(0.03f, 0.98f, 0.98f, 1.0f);
			PlotHistogram 		= ImVec4(1.0f, 0.29f, 0.59f, 1.0f);
			PlotHistogramHovered 	= ImVec4(0.99f, 0.47f, 0.69f, 1.0f);
			TableHeaderBg 		= ImVec4(0.047f, 0.05f, 0.07f, 1.0f);
			TableBorderStrong 	= ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
			TableBorderLight 	= ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			TableRowBg 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			TableRowBgAlt 		= ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
			TextSelectedBg 		= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
			DragDropTarget 		= ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
			NavHighlight 		= ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
			NavWindowingHighlight 	= ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
			NavWindowingDimBg 	= ImVec4(0.19f, 0.17f, 0.54f, 0.50f);
			ModalWindowDimBg 	= ImVec4(0.19f, 0.17f, 0.54f, 0.50f);
    		}
    		ImGui::SameLine();
    	    	if (ImGui::Button("EmbraceTheDarkness##Color")) {
    	    		ThemeColor = 2;
			Text                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		  	TextDisabled           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		  	WindowBg               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		  	ChildBg                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		  	PopupBg                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
		  	Border                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
		  	BorderShadow           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		  	FrameBg                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		  	FrameBgHovered         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		  	FrameBgActive          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		  	TitleBg                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		  	TitleBgActive          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		  	TitleBgCollapsed       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		  	MenuBarBg              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		  	ScrollbarBg            = ImVec4(0.05f, 0.05f, 0.05f, 0.00f);
		  	ScrollbarGrab          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		  	ScrollbarGrabHovered   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		  	ScrollbarGrabActive    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		  	CheckMark              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		  	SliderGrab             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		  	SliderGrabActive       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		  	Button                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		  	ButtonHovered          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		  	ButtonActive           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		  	Header                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		  	HeaderHovered          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
		  	HeaderActive           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		  	Separator              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		  	SeparatorHovered       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		  	SeparatorActive        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		  	ResizeGrip             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		  	ResizeGripHovered      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		  	ResizeGripActive       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		  	Tab                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		  	TabHovered             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		  	TabActive              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
		  	TabUnfocused           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		  	TabUnfocusedActive     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		  	PlotLines              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		  	PlotLinesHovered       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		  	PlotHistogram          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		  	PlotHistogramHovered   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		  	TableHeaderBg          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		  	TableBorderStrong      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		  	TableBorderLight       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		  	TableRowBg             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		  	TableRowBgAlt          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		  	TextSelectedBg         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		  	DragDropTarget         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		  	NavHighlight           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		  	NavWindowingHighlight  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		  	NavWindowingDimBg      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
		  	ModalWindowDimBg       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
    		}
    		ImGui::SameLine();
    		if (ImGui::Button("Enemymouse##Color")) {
    			ThemeColor = 3;
			Text = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
			TextDisabled = ImVec4(0.00f, 0.40f, 0.41f, 1.00f);
			WindowBg = ImVec4(0.00f, 0.00f, 0.00f, 0.7f);
			Border = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
			BorderShadow = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			FrameBg = ImVec4(0.00f, 1.00f, 1.00f, 0.18f);
			FrameBgHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
			FrameBgActive = ImVec4(0.00f, 1.00f, 1.00f, 0.66f);
			PlotLines = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
			Tab = ImVec4(0.00f, 1.00f, 1.00f, 0.18f);
			TabHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.60f);
			TabActive = ImVec4(0.00f, 1.00f, 1.00f, 0.60f);
			TitleBg = ImVec4(0.14f, 0.18f, 0.21f, 0.73f);
			TitleBgCollapsed = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
			TitleBgActive = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
			MenuBarBg = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
			ScrollbarBg = ImVec4(0.22f, 0.29f, 0.30f, 0.00f);
			ScrollbarGrab = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
			ScrollbarGrabHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
			ScrollbarGrabActive = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
			Separator = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
			CheckMark = ImVec4(0.00f, 1.00f, 1.00f, 0.68f);
			SliderGrab = ImVec4(0.00f, 1.00f, 1.00f, 0.36f);
			SliderGrabActive = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
			Button = ImVec4(0.00f, 0.65f, 0.65f, 0.46f);
			ButtonHovered = ImVec4(0.01f, 1.00f, 1.00f, 0.43f);
			ButtonActive = ImVec4(0.00f, 1.00f, 1.00f, 0.62f);
			Header = ImVec4(0.00f, 1.00f, 1.00f, 0.33f);
			HeaderHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.42f);
			HeaderActive = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
			ResizeGrip = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
			ResizeGripHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
			ResizeGripActive = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
			PlotLinesHovered = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
			PlotHistogram = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
			PlotHistogramHovered = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
			TextSelectedBg = ImVec4(0.00f, 1.00f, 1.00f, 0.22f);
    		}
    		
    		ImGui::SameLine();
    	    	if (ImGui::Button("Cyberpunk##Color")) {
    	    		ThemeColor = 4;
			Text                   = ImVec4(0.00f, 0.82f, 1.00f, 1.00f);
			TextDisabled           = ImVec4(0.00f, 0.36f, 0.63f, 1.00f);
			WindowBg               = ImVec4(0.00f, 0.04f, 0.12f, 1.00f);
			ChildBg                = ImVec4(0.03f, 0.04f, 0.22f, 1.00f);
			PopupBg                = ImVec4(0.12f, 0.06f, 0.27f, 1.00f);
			Border                 = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
			FrameBg                = ImVec4(0.00f, 0.75f, 1.00f, 0.20f);
			FrameBgHovered         = ImVec4(0.34f, 0.00f, 1.00f, 1.00f);
			FrameBgActive          = ImVec4(0.08f, 0.00f, 1.00f, 1.00f);
			TitleBg                = ImVec4(0.00f, 0.81f, 0.95f, 1.00f);
			TitleBgActive          = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
			TitleBgCollapsed       = ImVec4(0.25f, 0.00f, 0.54f, 0.81f);
			MenuBarBg              = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
			ScrollbarBg            = ImVec4(0.00f, 0.88f, 1.00f, 0.00f);
			ScrollbarGrab          = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
			ScrollbarGrabHovered   = ImVec4(0.00f, 0.82f, 1.00f, 1.00f);
			ScrollbarGrabActive    = ImVec4(0.95f, 0.19f, 0.67f, 1.00f);
			CheckMark              = ImVec4(0.95f, 0.19f, 0.92f, 1.00f);
			SliderGrab             = ImVec4(0.00f, 1.00f, 0.95f, 1.00f);
			SliderGrabActive       = ImVec4(0.81f, 0.00f, 1.00f, 1.00f);
			Button                 = ImVec4(0.00f, 0.98f, 1.00f, 0.52f);
			ButtonHovered          = ImVec4(0.94f, 0.00f, 1.00f, 0.80f);
			ButtonActive           = ImVec4(0.01f, 0.00f, 1.00f, 1.00f);
			Header                 = ImVec4(0.00f, 0.95f, 1.00f, 0.40f);
			HeaderHovered          = ImVec4(0.94f, 0.00f, 1.00f, 0.80f);
			HeaderActive           = ImVec4(0.01f, 0.00f, 1.00f, 1.00f);
			Separator              = ImVec4(0.74f, 0.00f, 1.00f, 0.50f);
			SeparatorHovered       = ImVec4(0.34f, 0.00f, 1.00f, 0.78f);
			SeparatorActive        = ImVec4(0.00f, 1.00f, 0.85f, 1.00f);
			ResizeGrip             = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
			ResizeGripHovered      = ImVec4(0.89f, 0.26f, 0.98f, 0.67f);
			ResizeGripActive       = ImVec4(0.00f, 0.88f, 1.00f, 0.95f);
			Tab                    = ImVec4(0.36f, 0.00f, 1.00f, 1.00f);
			TabHovered             = ImVec4(0.00f, 0.92f, 1.00f, 0.80f);
			TabActive              = ImVec4(0.62f, 0.00f, 0.80f, 1.00f);
			PlotHistogram          = ImVec4(0.00f, 1.00f, 0.88f, 1.00f);
    		}
    		
    		ImGui::SameLine();
    		if (ImGui::Button("Moonlight##Color")) {
    			ThemeColor = 5;
			Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			TextDisabled = ImVec4(0.27f, 0.31f, 0.45f, 1.0f);
			WindowBg = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			ChildBg = ImVec4(0.09f, 0.10f, 0.11f, 1.0f);
			PopupBg = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			Border = ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
			BorderShadow = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			FrameBg = ImVec4(0.11f, 0.12f, 0.15f, 1.0f);
			FrameBgHovered = ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
			FrameBgActive = ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
			TitleBg = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
			TitleBgActive = ImVec4(0.047f, 0.05f, 0.07f, 1.0f);
			TitleBgCollapsed = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			MenuBarBg = ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
			ScrollbarBg = ImVec4(0.04f, 0.05f, 0.07f, 0.00f);
			ScrollbarGrab = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			ScrollbarGrabHovered = ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
			ScrollbarGrabActive = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			CheckMark = ImVec4(0.97f, 1.0f, 0.49f, 1.0f);
			SliderGrab = ImVec4(0.97f, 1.0f, 0.49f, 1.0f);
			SliderGrabActive = ImVec4(1.0f, 0.79f, 0.49f, 1.0f);
			Button = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			ButtonHovered = ImVec4(0.18f, 0.18f, 0.19f, 1.0f);
			ButtonActive = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
			Header = ImVec4(0.14f, 0.16f, 0.20f, 1.0f);
			HeaderHovered = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
			HeaderActive = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			Separator = ImVec4(0.12f, 0.14f, 0.19f, 1.0f);
			SeparatorHovered = ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
			SeparatorActive = ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
			ResizeGrip = ImVec4(0.14f, 0.14f, 0.14f, 1.0f);
			ResizeGripHovered = ImVec4(0.97f, 1.0f, 0.49f, 1.0f);
			ResizeGripActive = ImVec4(0.99f, 1.0f, 0.99f, 1.0f);
			Tab = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			TabHovered = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			TabActive = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			TabUnfocused = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
			TabUnfocusedActive = ImVec4(0.12f, 0.27f, 0.57f, 1.0f);
			PlotLines = ImVec4(0.52f, 0.60f, 0.70f, 1.0f);
			PlotLinesHovered = ImVec4(0.03f, 0.98f, 0.98f, 1.0f);
			PlotHistogram = ImVec4(0.88f, 0.79f, 0.56f, 1.0f);
			PlotHistogramHovered = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
			TableHeaderBg = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
			TableBorderStrong = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
			TableBorderLight = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			TableRowBg = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
			TableRowBgAlt = ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
			TextSelectedBg = ImVec4(0.93f, 0.93f, 0.93f, 1.0f);
			DragDropTarget = ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
			NavHighlight = ImVec4(0.26f, 0.28f, 1.0f, 1.0f);
			NavWindowingHighlight = ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
			NavWindowingDimBg = ImVec4(0.19f, 0.17f, 0.54f, 0.50f);
			ModalWindowDimBg = ImVec4(0.19f, 0.17f, 0.54f, 0.50f);
		}
		ImGui::SameLine();
		if (ImGui::Button("Purpur-Fetthenne##Color")) {
			  ThemeColor = 6;
			  Text                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			  TextDisabled           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			  WindowBg               = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  ChildBg                = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  PopupBg                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
			  Border                 = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  BorderShadow           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			  FrameBg                = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
			  FrameBgHovered         = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
			  FrameBgActive          = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
			  TitleBg                = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  TitleBgActive          = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  TitleBgCollapsed       = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  MenuBarBg              = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  ScrollbarBg            = ImVec4(0.27f, 0.27f, 0.28f, 0.00f);
			  ScrollbarGrab          = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
			  ScrollbarGrabHovered   = ImVec4(0.36f, 0.38f, 0.39f, 1.00f);
			  ScrollbarGrabActive    = ImVec4(0.36f, 0.38f, 0.39f, 1.00f);
			  CheckMark              = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
			  SliderGrab             = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
			  SliderGrabActive       = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
			  Button                 = ImVec4(0.36f, 0.38f, 0.39f, 1.00f);
			  ButtonHovered          = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
			  ButtonActive           = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
			  Header                 = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  HeaderHovered          = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  HeaderActive           = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
			  Separator              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
			  SeparatorHovered       = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
			  SeparatorActive        = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
			  ResizeGrip             = ImVec4(0.36f, 0.38f, 0.39f, 1.00f);
			  ResizeGripHovered      = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
			  ResizeGripActive       = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
			  PlotLines              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			  PlotLinesHovered       = ImVec4(0.60f, 0.36f, 0.76f, 0.40f);
			  PlotHistogram          = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
			  PlotHistogramHovered   = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
			  TextSelectedBg         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			  DragDropTarget         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
			  NavHighlight           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			  NavWindowingHighlight  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	        }
	        ImGui::SameLine();
	        if (ImGui::Button("Vine##Color")) {
    		    ThemeColor = 7;
    		        Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			TextDisabled = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
			WindowBg = ImVec4(0.05490196123719215f, 0.03529411926865578f, 0.1843137294054031f, 1.0f);
			ChildBg = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			PopupBg = ImVec4(0.05490196123719215f, 0.03529411926865578f, 0.1843137294054031f, 1.0f);
			Border = ImVec4(0.2745098173618317f, 0.3568627536296844f, 0.9058823585510254f, 1.0f);
			BorderShadow = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			FrameBg = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			FrameBgHovered = ImVec4(0.1333333402872086f, 0.1764705926179886f, 0.5058823823928833f, 1.0f);
			FrameBgActive = ImVec4(0.2745098173618317f, 0.3568627536296844f, 0.9058823585510254f, 1.0f);
			TitleBg = ImVec4(0.1333333402872086f, 0.1764705926179886f, 0.5058823823928833f, 1.0f);
			TitleBgActive = ImVec4(0.2745098173618317f, 0.3568627536296844f, 0.9058823585510254f, 1.0f);
			TitleBgCollapsed = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			MenuBarBg = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			ScrollbarBg = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.00f);
			ScrollbarGrab = ImVec4(0.2745098173618317f, 0.3568627536296844f, 0.9058823585510254f, 1.0f);
			ScrollbarGrabHovered = ImVec4(0.1647058874368668f, 0.7529411911964417f, 0.9490196108818054f, 1.0f);
			ScrollbarGrabActive = ImVec4(0.1647058874368668f, 0.7529411911964417f, 0.9490196108818054f, 1.0f);
			CheckMark = ImVec4(0.1647058874368668f, 0.7529411911964417f, 0.9490196108818054f, 1.0f);
			SliderGrab = ImVec4(0.2745098173618317f, 0.3568627536296844f, 0.9058823585510254f, 1.0f);
			SliderGrabActive = ImVec4(0.1647058874368668f, 0.7529411911964417f, 0.9490196108818054f, 1.0f);
			Button = ImVec4(0.2745098173618317f, 0.3568627536296844f, 0.9058823585510254f, 1.0f);
			ButtonHovered = ImVec4(0.1333333402872086f, 0.1764705926179886f, 0.5058823823928833f, 1.0f);
			ButtonActive = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			Header = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			HeaderHovered = ImVec4(0.1333333402872086f, 0.1764705926179886f, 0.5058823823928833f, 1.0f);
			HeaderActive = ImVec4(0.2745098173618317f, 0.3568627536296844f, 0.9058823585510254f, 1.0f);
			Separator = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
			SeparatorHovered = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 0.7799999713897705f);
			SeparatorActive = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
			ResizeGrip = ImVec4(0.2313725501298904f, 0.3568627536296844f, 0.9960784316062927f, 1.0f);
			ResizeGripHovered = ImVec4(0.1584483087062836f, 0.2800911366939545f, 0.8025751113891602f, 1.0f);
			ResizeGripActive = ImVec4(0.09891508519649506f, 0.2253202944993973f, 0.7682403326034546f, 1.0f);
			Tab = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			TabHovered = ImVec4(0.1333333402872086f, 0.1764705926179886f, 0.5058823823928833f, 1.0f);
			TabActive = ImVec4(0.2745098173618317f, 0.3568627536296844f, 0.9058823585510254f, 1.0f);
			TabUnfocused = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			TabUnfocusedActive = ImVec4(0.2745098173618317f, 0.3568627536296844f, 0.9058823585510254f, 1.0f);
			PlotLines = ImVec4(0.1584483087062836f, 0.2800911366939545f, 0.8025751113891602f, 1.0f);
			PlotLinesHovered = ImVec4(0.2313725501298904f, 0.3568627536296844f, 0.9960784316062927f, 1.0f);
			PlotHistogram = ImVec4(0.1584483087062836f, 0.2800911366939545f, 0.8025751113891602f, 1.0f);
			PlotHistogramHovered = ImVec4(0.2313725501298904f, 0.3568627536296844f, 0.9960784316062927f, 1.0f);
			TableHeaderBg = ImVec4(0.2313725501298904f, 0.3568627536296844f, 0.9960784316062927f, 1.0f);
			TableBorderStrong = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			TableBorderLight = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			TableRowBg = ImVec4(0.1333333402872086f, 0.1764705926179886f, 0.5058823823928833f, 1.0f);
			TableRowBgAlt = ImVec4(0.105882354080677f, 0.09411764889955521f, 0.3254902064800262f, 1.0f);
			TextSelectedBg = ImVec4(0.2313725501298904f, 0.3568627536296844f, 0.9960784316062927f, 1.0f);
			DragDropTarget = ImVec4(0.2313725501298904f, 0.3568627536296844f, 0.9960784316062927f, 1.0f);
			NavHighlight = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
			NavWindowingHighlight = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
			NavWindowingDimBg = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
			ModalWindowDimBg = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
    		}
			ImGui::EndChild();
			}

			ImGui::Text("Credits Tab");
			if (ImGui::BeginChild("Credits", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 231), true, ImGuiWindowFlags_NoScrollbar)) {
				ImGui::TextColored(ImVec4(0.65, 1, 0.95, 1), "Credits:");
            	ImGui::TextColored(ImVec4(0.03, 1, 0.95, 1), "arturzxc: ESP, Triggerbot and X11Display's Move Mouse method");
            	ImGui::TextColored(ImVec4(0.3, 1, 0.64, 1), "Koelion: ImGui Menu, AimbotResolver");
            	ImGui::TextColored(ImVec4(0.3, 0.6, 0.9, 1), "unknowncheats: Offsets and ton of other things");
            	ImGui::TextColored(ImVec4(0.6, 1, 0.64, 1), "Made by Azreol/Nexilist");
            	ImGui::TextColored(ImVec4(0.744, 0.0400, 1.00, 1), "Pasted + Updated (With love) by Gerosity <3");
				ImGui::EndChild();
			}
    	
				/*ImGui::Text("Advanced Menu Customization");
    		if (ImGui::CollapsingHeader("Menu Customization", nullptr)) {
    			ImGui::Text("Some things may not change.");
    			ImGui::Text("These do not save.");
    			ImGui::Separator();
    			ImGui::Text("Styling");
    			ImGui::SliderFloat("Alpha", &Alpha, 0.10f, 1.00f, "%.01f");
    			ImGui::SliderFloat("Disabled Alpha", &DisabledAlpha, 0.10f, 1.00f, "%.01f");
    			ImGui::SliderFloat("Tab Min Width For Close Button", &TabMinWidthForCloseButton, 0.10f, 1.00f, "%.01f");
    			ImGui::SliderFloat("Columns Min Spacing", &ColumnsMinSpacing, 1.00f, 10.00f, "%.01f");
    			ImGui::SliderInt("Indent Spacing", &IndentSpacing, 1, 100);
    			ImGui::SliderInt("Scrollbar Size", &ScrollbarSize, 1, 100);
    			ImGui::SliderInt("Grab Min Size", &GrabMinSize, 1, 100);
    			ImGui::SliderInt("Window Border Size", &WindowBorderSize, 1, 100);
    			ImGui::SliderInt("Child Border Size", &ChildBorderSize, 1, 100);
    			ImGui::SliderInt("Popup Border Size", &PopupBorderSize, 1, 100);
    			ImGui::SliderInt("Frame Border Size", &FrameBorderSize, 1, 100);
    			ImGui::SliderInt("Tab Border Size", &TabBorderSize, 1, 100);
    			ImGui::SliderInt("Window Rounding", &WindowRounding, 1, 100);
    			ImGui::SliderInt("Child Rounding", &ChildRounding, 1, 100);
    			ImGui::SliderInt("Frame Rounding", &FrameRounding, 1, 100);
    			ImGui::SliderInt("Popup Rounding", &PopupRounding, 1, 100);
    			ImGui::SliderInt("Scrollbar Rounding", &ScrollbarRounding, 1, 100);
    			ImGui::SliderInt("Grab Rounding", &GrabRounding, 1, 100);
    			ImGui::SliderInt("Log Slider Deadzone", &LogSliderDeadzone, 1, 100);
    			ImGui::SliderInt("Tab Rounding", &TabRounding, 1, 100);
    			
    			ImGui::Spacing();
    			
    			ImGui::Text("Colors");
    			ImGui::ColorEdit4("Text", (float*)&Text, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TextDisabled", (float*)&Text, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("WindowBg", (float*)&WindowBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ChildBg", (float*)&ChildBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("PopupBg", (float*)&PopupBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("Border", (float*)&Border, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("BorderShadow", (float*)&BorderShadow, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("FrameBg", (float*)&FrameBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("FrameBgHovered", (float*)&FrameBgHovered, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("FrameBgActive", (float*)&FrameBgActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TitleBg", (float*)&TitleBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TitleBgActive", (float*)&TitleBgActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TitleBgCollapsed", (float*)&TitleBgCollapsed, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("MenuBarBg", (float*)&MenuBarBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ScrollbarBg", (float*)&ScrollbarBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ScrollbarGrab", (float*)&ScrollbarGrab, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ScrollbarGrabHovered", (float*)&ScrollbarGrabHovered, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ScrollbarGrabActive", (float*)&ScrollbarGrabActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("CheckMark", (float*)&CheckMark, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("SliderGrab", (float*)&SliderGrab, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("SliderGrabActive", (float*)&SliderGrabActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("Button", (float*)&Button, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ButtonHovered", (float*)&ButtonHovered, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ButtonActive", (float*)&ButtonActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("Header", (float*)&Header, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("HeaderHovered", (float*)&HeaderHovered, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("HeaderActive", (float*)&HeaderActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("Separator", (float*)&Separator, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("SeparatorHovered", (float*)&SeparatorHovered, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("SeparatorActive", (float*)&SeparatorActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ResizeGrip", (float*)&ResizeGrip, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ResizeGripHovered", (float*)&ResizeGripHovered, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ResizeGripActive", (float*)&ResizeGripActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("Tab", (float*)&Tab, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TabHovered", (float*)&TabHovered, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TabActive", (float*)&TabActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TabUnfocused", (float*)&TabUnfocused, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TabUnfocusedActive", (float*)&TabUnfocusedActive, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("PlotLines", (float*)&PlotLines, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("PlotLinesHovered", (float*)&PlotLinesHovered, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("PlotHistogram", (float*)&PlotHistogram, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("PlotHistogramHovered", (float*)&PlotHistogramHovered, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TableHeaderBg", (float*)&TableHeaderBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TableBorderStrong", (float*)&TableBorderStrong, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TableBorderLight", (float*)&TableBorderLight, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TableRowBg", (float*)&TableRowBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TableRowBgAlt", (float*)&TableRowBgAlt, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("TextSelectedBg", (float*)&TextSelectedBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("DragDropTarget", (float*)&DragDropTarget, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("NavHighlight", (float*)&NavHighlight, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("NavWindowingHighlight", (float*)&NavWindowingHighlight, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("NavWindowingDimBg", (float*)&NavWindowingDimBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    			ImGui::ColorEdit4("ModalWindowDimBg", (float*)&ModalWindowDimBg, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
    		}*/

    	ImGui::EndTabItem();
    
        ImGuiStyle& style = ImGui::GetStyle();
	style.Alpha 				= Alpha;
	style.DisabledAlpha 			= DisabledAlpha;
	style.WindowMinSize 			= WindowMinSize;
	style.WindowTitleAlign 			= WindowTitleAlign;
	style.WindowPadding                     = WindowPadding;
	style.FramePadding                      = FramePadding;
	style.CellPadding                       = CellPadding;
	style.ItemSpacing                       = ItemSpacing;
	style.ItemInnerSpacing                  = ItemInnerSpacing;
	style.TouchExtraPadding                 = TouchExtraPadding;
	style.IndentSpacing                     = IndentSpacing;
	style.ScrollbarSize                     = ScrollbarSize;
	style.GrabMinSize                       = GrabMinSize;
	style.WindowBorderSize                  = WindowBorderSize;
	style.ChildBorderSize                   = ChildBorderSize;
	style.PopupBorderSize                   = PopupBorderSize;
	style.FrameBorderSize                   = FrameBorderSize;
	style.TabBorderSize                     = TabBorderSize;
	style.WindowRounding                    = WindowRounding;
	style.ChildRounding                     = ChildRounding;
	style.FrameRounding                     = FrameRounding;
	style.PopupRounding                     = PopupRounding;
	style.ScrollbarRounding                 = ScrollbarRounding;
	style.GrabRounding                      = GrabRounding;
	style.LogSliderDeadzone                 = LogSliderDeadzone;
	style.TabRounding                       = TabRounding;
	style.TabMinWidthForCloseButton	 	= TabMinWidthForCloseButton;
	style.ButtonTextAlign 			= ButtonTextAlign;
	style.SelectableTextAlign 		= SelectableTextAlign;

	style.Colors[ImGuiCol_Text]                   = Text;
  	style.Colors[ImGuiCol_TextDisabled]           = TextDisabled;
  	style.Colors[ImGuiCol_WindowBg]               = WindowBg;
  	style.Colors[ImGuiCol_ChildBg]                = ChildBg;
  	style.Colors[ImGuiCol_PopupBg]                = PopupBg;
  	style.Colors[ImGuiCol_Border]                 = Border;
  	style.Colors[ImGuiCol_BorderShadow]           = BorderShadow;
  	style.Colors[ImGuiCol_FrameBg]                = FrameBg;
  	style.Colors[ImGuiCol_FrameBgHovered]         = FrameBgHovered;
  	style.Colors[ImGuiCol_FrameBgActive]          = FrameBgActive;
  	style.Colors[ImGuiCol_TitleBg]                = TitleBg;
  	style.Colors[ImGuiCol_TitleBgActive]          = TitleBgActive;
  	style.Colors[ImGuiCol_TitleBgCollapsed]       = TitleBgCollapsed;
  	style.Colors[ImGuiCol_MenuBarBg]              = MenuBarBg;
  	style.Colors[ImGuiCol_ScrollbarBg]            = ScrollbarBg;
  	style.Colors[ImGuiCol_ScrollbarGrab]          = ScrollbarGrab;
  	style.Colors[ImGuiCol_ScrollbarGrabHovered]   = ScrollbarGrabHovered;
  	style.Colors[ImGuiCol_ScrollbarGrabActive]    = ScrollbarGrabActive;
 	style.Colors[ImGuiCol_CheckMark]              = CheckMark;
	style.Colors[ImGuiCol_SliderGrab]             = SliderGrab;
 	style.Colors[ImGuiCol_SliderGrabActive]       = SliderGrabActive;
  	style.Colors[ImGuiCol_Button]                 = Button;
  	style.Colors[ImGuiCol_ButtonHovered]          = ButtonHovered;
  	style.Colors[ImGuiCol_ButtonActive]           = ButtonActive;
  	style.Colors[ImGuiCol_Header]                 = Header;
  	style.Colors[ImGuiCol_HeaderHovered]          = HeaderHovered;
  	style.Colors[ImGuiCol_HeaderActive]           = HeaderActive;
  	style.Colors[ImGuiCol_Separator]              = Separator;
  	style.Colors[ImGuiCol_SeparatorHovered]       = SeparatorHovered;
  	style.Colors[ImGuiCol_SeparatorActive]        = SeparatorActive;
  	style.Colors[ImGuiCol_ResizeGrip]             = ResizeGrip;
  	style.Colors[ImGuiCol_ResizeGripHovered]      = ResizeGripHovered;
  	style.Colors[ImGuiCol_ResizeGripActive]       = ResizeGripActive;
  	style.Colors[ImGuiCol_Tab]                    = Tab;
  	style.Colors[ImGuiCol_TabHovered]             = TabHovered;
  	style.Colors[ImGuiCol_TabActive]              = TabActive;
  	style.Colors[ImGuiCol_TabUnfocused]           = TabUnfocused;
  	style.Colors[ImGuiCol_TabUnfocusedActive]     = TabUnfocusedActive;
  	style.Colors[ImGuiCol_PlotLines]              = PlotLines;
  	style.Colors[ImGuiCol_PlotLinesHovered]       = PlotLinesHovered;
  	style.Colors[ImGuiCol_PlotHistogram]          = PlotHistogram;
  	style.Colors[ImGuiCol_PlotHistogramHovered]   = PlotHistogramHovered;
  	style.Colors[ImGuiCol_TableHeaderBg]          = TableHeaderBg;
  	style.Colors[ImGuiCol_TableBorderStrong]      = TableBorderStrong;
  	style.Colors[ImGuiCol_TableBorderLight]       = TableBorderLight;
  	style.Colors[ImGuiCol_TableRowBg]             = TableRowBg;
  	style.Colors[ImGuiCol_TableRowBgAlt]          = TableRowBgAlt;
  	style.Colors[ImGuiCol_TextSelectedBg]         = TextSelectedBg;
  	style.Colors[ImGuiCol_DragDropTarget]         = DragDropTarget;
  	style.Colors[ImGuiCol_NavHighlight]           = NavHighlight;
  	style.Colors[ImGuiCol_NavWindowingHighlight]  = NavWindowingHighlight;
  	style.Colors[ImGuiCol_NavWindowingDimBg]      = NavWindowingDimBg;
  	style.Colors[ImGuiCol_ModalWindowDimBg]       = ModalWindowDimBg;
        }
    }
    
    bool Save() {
        try {
            Config::Home::AsciiArt = AsciiArt;
            Config::Home::AsciiArtSpeed = AsciiArtSpeed;
            Config::Home::TeamGamemode = TeamGamemode;
            Config::Home::Style = ThemeStyle;
            Config::Home::Color = ThemeColor;
            //Config::Home::MenuX = MenuX;
            //Config::Home::MenuY = MenuY;
            Config::Home::ErrorLogging = ErrorLogging;
            return true;
        } catch (...) {
            return false;
        }
    }

    void DestroyOverlay() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if(OverlayWindow != nullptr) {
            glfwDestroyWindow(OverlayWindow);
        }

        glfwTerminate();
    }

    void CaptureInput(bool capture) {
        glfwSetWindowAttrib(OverlayWindow, GLFW_MOUSE_PASSTHROUGH, capture ? GLFW_FALSE : GLFW_TRUE);
    }

    void FocusOverlay() {
        glfwFocusWindow(OverlayWindow);
    }

    void Start(bool(*Update)(), void(*RenderUI)()) {
        while(!glfwWindowShouldClose(OverlayWindow)) {
            StartTime = CurrentEpochMilliseconds();
            glfwPollEvents();
            glViewport(0, 0, ScreenWidth, ScreenHeight);
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, ScreenWidth, ScreenHeight, 0, -1, 1);

			//Update
			if (Update != nullptr) {
                Update();
            }

			ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            // Render
            if (RenderUI != nullptr){
                RenderUI();
            }
            
            // Render ImGui and swap buffers
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(OverlayWindow);
            
            ProcessingTime = static_cast<int>(CurrentEpochMilliseconds() - StartTime);
            SleepTime = 6; // 16.67 > 60hz | 6.97 > 144hz
            TimeLeftToSleep = std::max(0, SleepTime - ProcessingTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(TimeLeftToSleep));
        }

        DestroyOverlay();
    }

    void GetScreenResolution(int& Width, int& Height) const {
        Width = ScreenWidth;
        Height = ScreenHeight;
    }
};
