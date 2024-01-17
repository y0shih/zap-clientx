// Externals
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

// Internals
#include "Core/Level.hpp"
#include "Core/Player.hpp"
#include "Core/LocalPlayer.hpp"
#include "Core/Camera.hpp"

#include "Features/Aimbot.hpp"
#include "Features/Sense.hpp"
#include "Features/Triggerbot.hpp"
#include "Features/Misc.hpp"
#include "Features/Menu.hpp"

#include "Overlay/Overlay.hpp"

#include "Utils/Config.hpp"
#include "Utils/Memory.hpp"
#include "Utils/XDisplay.hpp"

// Objects
XDisplay* X11Display = new XDisplay();
Overlay OverlayWindow = Overlay();
ImDrawList* Canvas;

// Game Objects
Level* Map = new Level();
LocalPlayer* Myself = new LocalPlayer();
Camera* GameCamera = new Camera();

// Players
std::vector<Player*>* HumanPlayers = new std::vector<Player*>;
std::vector<Player*>* Dummies = new std::vector<Player*>;
std::vector<Player*>* Players = new std::vector<Player*>;

// Features
Sense* ESP = new Sense(Players, GameCamera, Myself);
Aimbot* AimAssist = new Aimbot(X11Display, Myself, Players);
Triggerbot* Trigger = new Triggerbot(X11Display, Myself, Players);
Misc* MiscTab = new Misc(X11Display, Map, Myself, Players);
MenuUI* MenuTab = new MenuUI;

// Booleans and Variables
bool IsMenuOpened = true;

// Thread
std::atomic_bool StopThread(false);

// Inputs
void HandleKeyEvent(Display* display, XEvent* Event) {
    if (Event->type == KeyPress) {
        if (IsMenuOpened) {
            IsMenuOpened = false;
            OverlayWindow.CaptureInput(false);
        } else {
            IsMenuOpened = true;
            OverlayWindow.CaptureInput(true);
        }
    }
}

void X11EventListener() {
    Display* display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(display);
    XGrabKey(display, XKeysymToKeycode(display, XK_Insert), AnyModifier, root, False, GrabModeAsync, GrabModeAsync);
    XEvent event;
    while (!StopThread) {
        XNextEvent(display, &event);
        HandleKeyEvent(display, &event);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    XCloseDisplay(display);
}

// Overlay
bool InitializeOverlayWindow() {
    if (!OverlayWindow.InitializeOverlay()) {
        OverlayWindow.DestroyOverlay();
        return false;
    }
    int ScreenWidth;
    int ScreenHeight;
    OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
    GameCamera->Initialize(ScreenWidth, ScreenHeight);
    std::cout << "overlay initialized" << std::endl;
    return true;
}

// Config
void LoadConfig() {
    bool success = ReadConfig("config.ini");
    if (success)
        std::cout << "successfully read config" << std::endl;
    else
        std::cout << "can't read config for some reason so new config file has been created" << std::endl;

    // Aimbot //
    AimAssist->AimbotEnabled = Config::Aimbot::Enabled;
    Modules::Aimbot::Hitbox = static_cast<HitboxType>(Config::Aimbot::HitBox);
    AimAssist->OnFire = Config::Aimbot::OnFire;
    AimAssist->OnADS = Config::Aimbot::OnADS;
    AimAssist->PredictMovement = Config::Aimbot::PredictMovement;
    AimAssist->PredictBulletDrop = Config::Aimbot::PredictBulletDrop;
    AimAssist->Speed = Config::Aimbot::Speed;
    AimAssist->Smooth = Config::Aimbot::Smooth;
    AimAssist->FOV = Config::Aimbot::FOV;
    AimAssist->ZoomScale = Config::Aimbot::ZoomScale;
    AimAssist->MinDistance = Config::Aimbot::MinDistance;
    AimAssist->HipfireDistance = Config::Aimbot::HipfireDistance;
    AimAssist->ZoomDistance = Config::Aimbot::ZoomDistance;
    AimAssist->RecoilEnabled = Config::Aimbot::RecoilControl;
    AimAssist->PitchPower = Config::Aimbot::PitchPower;
    AimAssist->YawPower = Config::Aimbot::YawPower;
    //Weapons
    AimAssist->P2020 = Config::Aimbot::P2020;
    AimAssist->RE45 = Config::Aimbot::RE45;
    AimAssist->Alternator = Config::Aimbot::Alternator;
    AimAssist->R99 = Config::Aimbot::R99;
    AimAssist->R301 = Config::Aimbot::R301;
    AimAssist->Spitfire = Config::Aimbot::Spitfire;
    AimAssist->G7 = Config::Aimbot::G7;
    AimAssist->Flatline = Config::Aimbot::Flatline;
    AimAssist->Hemlock = Config::Aimbot::Hemlock;
    AimAssist->Repeater = Config::Aimbot::Repeater;
    AimAssist->Rampage = Config::Aimbot::Rampage;
    AimAssist->CARSMG = Config::Aimbot::CARSMG;
    AimAssist->Havoc = Config::Aimbot::Havoc;
    AimAssist->Devotion = Config::Aimbot::Devotion;
    AimAssist->LSTAR = Config::Aimbot::LSTAR;
    AimAssist->TripleTake = Config::Aimbot::TripleTake;
    AimAssist->Volt = Config::Aimbot::Volt;
    AimAssist->Nemesis = Config::Aimbot::Nemesis;
    AimAssist->Mozambique = Config::Aimbot::Mozambique;
    AimAssist->EVA8 = Config::Aimbot::EVA8;
    AimAssist->Peacekeeper = Config::Aimbot::Peacekeeper;
    AimAssist->Mastiff = Config::Aimbot::Mastiff;
    AimAssist->Longbow = Config::Aimbot::Longbow;
    AimAssist->ChargeRifle = Config::Aimbot::ChargeRifle;
    AimAssist->Sentinel = Config::Aimbot::Sentinel;
    AimAssist->Wingman = Config::Aimbot::Wingman;
    AimAssist->Prowler = Config::Aimbot::Prowler;
    AimAssist->Bocek = Config::Aimbot::Bocek;
    AimAssist->Kraber = Config::Aimbot::Kraber;
    AimAssist->Knife = Config::Aimbot::Knife;
    
    
    // ESP //
    ESP->GlowEnabled = Config::Sense::GlowEnabled;
    ESP->VisibilityCheck = Config::Sense::VisibilityCheck;
    ESP->ItemGlow = Config::Sense::ItemGlow;
    ESP->GlowMaxDistance = Config::Sense::GlowMaxDistance;
    ESP->DrawSeer = Config::Sense::DrawSeer;
    ESP->ESPMaxDistance = Config::Sense::ESPMaxDistance;
    ESP->ShowSpectators = Config::Sense::ShowSpectators;
    ESP->DrawFOVCircle = Config::Sense::DrawFOVCircle;
    ESP->DrawFilledFOVCircle = Config::Sense::DrawFilledFOVCircle;
    ESP->FOVThickness = Config::Sense::FOVThickness;
    ESP->GameFOV = Config::Sense::GameFOV;
    ESP->DrawBox = Config::Sense::DrawBox;
    ESP->DrawFilledBox = Config::Sense::DrawFilledBox;
    ESP->BoxThickness = Config::Sense::BoxThickness;
    ESP->DrawNames = Config::Sense::DrawNames;
    ESP->ShowNear = Config::Sense::ShowNear;
    ESP->Skeleton = Config::Sense::Skeleton;
    ESP->SkeletonThickness = Config::Sense::SkeletonThickness;
    ESP->TracerPosition = Config::Sense::TracerPos;
    ESP->TracerBone = Config::Sense::TracerBone;
    ESP->DrawTracers = Config::Sense::DrawTracers;
    ESP->TracerThickness = Config::Sense::TracerThickness;
    ESP->ShowTeam = Config::Sense::ShowTeam;
    ESP->DrawCrosshair = Config::Sense::DrawCrosshair;
    ESP->CrosshairThickness = Config::Sense::CrosshairThickness;
    ESP->CrosshairSize = Config::Sense::CrosshairSize;
    ESP->TeamNames = Config::Sense::TeamNames;

    // Triggerbot //
    Trigger->TriggerbotEnabled = Config::Triggerbot::Enabled;
    Trigger->OnADS = Config::Triggerbot::OnADS;
    Trigger->TriggerbotRange = Config::Triggerbot::Range;
    //Weapons
    Trigger->P2020 = Config::Aimbot::P2020;
    Trigger->RE45 = Config::Aimbot::RE45;
    Trigger->Alternator = Config::Aimbot::Alternator;
    Trigger->R99 = Config::Aimbot::R99;
    Trigger->R301 = Config::Aimbot::R301;
    Trigger->Spitfire = Config::Aimbot::Spitfire;
    Trigger->G7 = Config::Aimbot::G7;
    Trigger->Flatline = Config::Aimbot::Flatline;
    Trigger->Hemlock = Config::Aimbot::Hemlock;
    Trigger->Repeater = Config::Aimbot::Repeater;
    Trigger->Rampage = Config::Aimbot::Rampage;
    Trigger->CARSMG = Config::Aimbot::CARSMG;
    Trigger->Havoc = Config::Aimbot::Havoc;
    Trigger->Devotion = Config::Aimbot::Devotion;
    Trigger->LSTAR = Config::Aimbot::LSTAR;
    Trigger->TripleTake = Config::Aimbot::TripleTake;
    Trigger->Volt = Config::Aimbot::Volt;
    Trigger->Nemesis = Config::Aimbot::Nemesis;
    Trigger->Mozambique = Config::Aimbot::Mozambique;
    Trigger->EVA8 = Config::Aimbot::EVA8;
    Trigger->Peacekeeper = Config::Aimbot::Peacekeeper;
    Trigger->Mastiff = Config::Aimbot::Mastiff;
    Trigger->Longbow = Config::Aimbot::Longbow;
    Trigger->ChargeRifle = Config::Aimbot::ChargeRifle;
    Trigger->Sentinel = Config::Aimbot::Sentinel;
    Trigger->Wingman = Config::Aimbot::Wingman;
    Trigger->Prowler = Config::Aimbot::Prowler;
    Trigger->Bocek = Config::Aimbot::Bocek;
    Trigger->Kraber = Config::Aimbot::Kraber;
    Trigger->Knife = Config::Aimbot::Knife;
    
    //Misc //
    MiscTab->TeamGamemode = Config::Misc::TeamGamemode;
    MiscTab->Superglide = Config::Misc::Superglide;
    
    //Themes //
    MenuTab->MenuLayout = Config::Menu::Layout;
}

void SaveConfig() {
    if (!AimAssist->Save()) std::cout << "something went wrong trying to save Aimbot settings" << std::endl;
    if (!ESP->Save()) std::cout << "something went wrong trying to save ESP settings" << std::endl;
    if (!Trigger->Save()) std::cout << "something went wrong trying to save Triggerbot settings" << std::endl;
    if (!MiscTab->Save()) std::cout << "something went wrong trying to save Misc settings" << std::endl;
    if (!MenuTab->Save()) std::cout << "something went wrong trying to save Themes settings" << std::endl;
    UpdateConfig();
}

// Interface
ImVec4 ProcessingTimeColor;
void RenderUI() {
    auto io = ImGui::GetIO();
	ImGui::SetNextWindowSize(io.DisplaySize);
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("##Overlay", nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_NoBackground |
		ImGuiSliderFlags_AlwaysClamp
	);
	Canvas = ImGui::GetWindowDrawList();
    //if (Map->IsPlayable)
        ESP->RenderDrawings(Canvas, AimAssist, Myself, OverlayWindow);
	ImGui::End();

    if (!IsMenuOpened) return;

    // Menu
    ImGui::SetNextWindowSizeConstraints(ImVec2(440, 490), ImVec2(440, 490));
    ImGui::SetNextWindowSize(ImVec2(440, 490), ImGuiCond_FirstUseEver);
    ImGui::Begin("zap-client", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    
    ProcessingTimeColor = OverlayWindow.ProcessingTime > 20 ? ProcessingTimeColor = ImVec4(1, 0.343, 0.475, 1) : ProcessingTimeColor = ImVec4(0.4, 1, 0.343, 1);
    ImGui::TextColored(ProcessingTimeColor, "Processing Time: %02dms", OverlayWindow.ProcessingTime);
    ImGui::SameLine();

    if (OverlayWindow.AlignedButton("Save Config")) {
        SaveConfig();
        std::cout << "config saved" << std::endl;
    }    
    ImGui::SameLine();
    if (OverlayWindow.AlignedButton("Load Config")) {
        LoadConfig();
        std::cout << "config loaded" << std::endl;
    }   

    if (ImGui::BeginTabBar("Menus"), ImGuiTabBarFlags_NoCloseWithMiddleMouseButton) {
        // Draw Settings //
        AimAssist->RenderUI();
        Trigger->RenderUI();
        ESP->RenderUI();
        MiscTab->RenderUI();
        MenuTab->RenderUI();

        // Draw Credits //
        if (ImGui::BeginTabItem("Credits", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
            ImGui::TextColored(ImVec4(0.65, 1, 0.95, 1), "Credits:");
            ImGui::TextColored(ImVec4(0.03, 1, 0.95, 1), "arturzxc: ESP, Triggerbot and X11Display's Move Mouse method");
            ImGui::TextColored(ImVec4(0.3, 1, 0.64, 1), "Koelion: ImGui Menu, AimbotResolver");
            ImGui::TextColored(ImVec4(0.3, 0.6, 0.9, 1), "unknowncheats: Offsets and ton of other things");
            ImGui::TextColored(ImVec4(0.6, 1, 0.64, 1), "Made by Azreol/Nexilist");
            ImGui::TextColored(ImVec4(0.744, 0.0400, 1.00, 1), "Pasted + Updated (With love) by Gerosity <3");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

// Core
bool UpdateCore() {
    try {
        // Map Checking //
        Map->Read();
        if (!Map->IsPlayable) {
            return true;
        }

        // Read Local Player //
        Myself->Read();
        if (!Myself->IsValid()) {
            return true;
        }

        // Populate Players //
        Players->clear();
        if (Map->IsFiringRange) {
            for (int i = 0; i < Dummies->size(); i++) {
                Player* p = Dummies->at(i);
                p->Read();
                if (p->BasePointer != 0 && (p->IsPlayer() || p->IsDummy()))
                    Players->push_back(p);
            }
        } else {
            for (int i = 0; i < HumanPlayers->size(); i++) {
                Player* p = HumanPlayers->at(i);
                p->Read();
                if (p->BasePointer != 0 && (p->IsPlayer() || p->IsDummy()))
                    Players->push_back(p);
            }
        }

        // Updates //
        GameCamera->Update();
        ESP->Update();
        AimAssist->Update();
        Trigger->Update();
        MiscTab->Update();
        MenuTab->Update();

        return true;
    } catch(const std::exception& ex) {
        std::system("clear");
        std::cout << "Error: " << ex.what() << std::endl;
        return true;
    }

    return false;
}

// Main
int main(int argc, char *argv[]) {
    if (getuid()) { 
        std::cout << "Please run as sudo!" << std::endl;
        return -1; 
    }

    // Waiting for Apex Legends to be found //
    while (Memory::GetPID() == 0) {
        std::system("clear");
        std::cout << "waiting for apex..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    std::system("clear");
    std::cout << "zap client - ver 0.1" << std::endl;

    // Initialize Overlay Window //
    if (!InitializeOverlayWindow()) return -1;

    // Theading //
    std::thread X11Thread(X11EventListener);
    X11Thread.detach();
    std::thread InputManagerThread(InputManager::run);
    InputManagerThread.detach();

    // Initialize the whole process //
    try {
        for (int i = 0; i < 70; i++) 
            HumanPlayers->push_back(new Player(i, Myself));

        for (int i = 0; i < 15000; i++) 
            Dummies->push_back(new Player(i, Myself));

        ESP->Initialize();
        
        std::cout << "core initialized" << std::endl;
        std::cout << "-----------------------------" << std::endl;

        LoadConfig();
        // This is where the fun starts //
        OverlayWindow.Start(&UpdateCore, &RenderUI);
    }
    catch(...) {}

    StopThread = true;
    InputManager::StopThread = true;
    X11Thread.join();
    InputManagerThread.join();

    return 0;
};
