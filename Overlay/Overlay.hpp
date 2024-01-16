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
        glfwSwapInterval(1);

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
        SetUIStyle();

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

    void SetUIStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding                     = ImVec2(8.00f, 8.00f);
	style.FramePadding                      = ImVec2(5.00f, 2.00f);
	style.CellPadding                       = ImVec2(6.00f, 6.00f);
	style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
	style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
	style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
	style.IndentSpacing                     = 25;
	style.ScrollbarSize                     = 15;
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

	style.Colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
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
  	style.Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
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
