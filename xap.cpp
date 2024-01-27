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
#include "Features/RCS.hpp"
#include "Features/Glow.hpp"

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
Sense* ESP = new Sense(Map, Players, GameCamera, Myself);
Glow* GlowESP = new Glow(Map, Players, GameCamera, Myself);
Aimbot* AimAssist = new Aimbot(X11Display, Map, Myself, Players);
RCS* Recoil = new RCS(X11Display, Map, Myself);
Triggerbot* Trigger = new Triggerbot(X11Display, Map, Myself, Players);
Misc* MiscTab = new Misc(X11Display, Map, Myself, Players);
Overlay* Home = new Overlay;

// Booleans and Variables
bool IsMenuOpened = true;
int AsciiArt = Config::Home::AsciiArt;
int AsciiArtSpeed = Config::Home::AsciiArtSpeed;

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
    AimAssist->ClosestHitbox = Config::Aimbot::ClosestHitbox;
    Modules::Aimbot::Hitbox = static_cast<HitboxType>(Config::Aimbot::HitBox);
    AimAssist->OnFire = Config::Aimbot::OnFire;
    AimAssist->OnADS = Config::Aimbot::OnADS;
    AimAssist->PredictMovement = Config::Aimbot::PredictMovement;
    AimAssist->PredictBulletDrop = Config::Aimbot::PredictBulletDrop;
    AimAssist->Speed = Config::Aimbot::Speed;
    AimAssist->Smooth = Config::Aimbot::Smooth;
    AimAssist->Delay = Config::Aimbot::Delay;
    AimAssist->FOV = Config::Aimbot::FOV;
    AimAssist->ZoomScale = Config::Aimbot::ZoomScale;
    AimAssist->MinDistance = Config::Aimbot::MinDistance;
    AimAssist->HipfireDistance = Config::Aimbot::HipfireDistance;
    AimAssist->ZoomDistance = Config::Aimbot::ZoomDistance;
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
    
    //---------------Advanced---------------//
    AimAssist->AdvancedAim = Config::Aimbot::AdvancedAim;
    //Weapons
    AimAssist->P2020Speed = Config::Aimbot::P2020Speed;
    AimAssist->P2020Smooth = Config::Aimbot::P2020Smooth;
    AimAssist->RE45Speed = Config::Aimbot::RE45Speed;
    AimAssist->RE45Smooth = Config::Aimbot::RE45Smooth;
    AimAssist->AlternatorSpeed = Config::Aimbot::AlternatorSpeed;
    AimAssist->AlternatorSmooth = Config::Aimbot::AlternatorSmooth;
    AimAssist->R99Speed = Config::Aimbot::R99Speed;
    AimAssist->R99Smooth = Config::Aimbot::R99Smooth;
    AimAssist->R301Speed = Config::Aimbot::R301Speed;
    AimAssist->R301Smooth = Config::Aimbot::R301Smooth;
    AimAssist->SpitfireSpeed = Config::Aimbot::SpitfireSpeed;
    AimAssist->SpitfireSmooth = Config::Aimbot::SpitfireSmooth;
    AimAssist->G7Speed = Config::Aimbot::G7Speed;
    AimAssist->G7Smooth = Config::Aimbot::G7Smooth;
    AimAssist->FlatlineSpeed = Config::Aimbot::FlatlineSpeed;
    AimAssist->FlatlineSmooth = Config::Aimbot::FlatlineSmooth;
    AimAssist->HemlockSpeed = Config::Aimbot::HemlockSpeed;
    AimAssist->HemlockSmooth = Config::Aimbot::HemlockSmooth;
    AimAssist->RepeaterSpeed = Config::Aimbot::RepeaterSpeed;
    AimAssist->RepeaterSmooth = Config::Aimbot::RepeaterSmooth;
    AimAssist->RampageSpeed = Config::Aimbot::RampageSpeed;
    AimAssist->RampageSmooth = Config::Aimbot::RampageSmooth;
    AimAssist->CARSMGSpeed = Config::Aimbot::CARSMGSpeed;
    AimAssist->CARSMGSmooth = Config::Aimbot::CARSMGSmooth;
    AimAssist->HavocSpeed = Config::Aimbot::HavocSpeed;
    AimAssist->HavocSmooth = Config::Aimbot::HavocSmooth;
    AimAssist->DevotionSpeed = Config::Aimbot::DevotionSpeed;
    AimAssist->DevotionSmooth = Config::Aimbot::DevotionSmooth;
    AimAssist->LSTARSpeed = Config::Aimbot::LSTARSpeed;
    AimAssist->LSTARSmooth = Config::Aimbot::LSTARSmooth;
    AimAssist->TripleTakeSpeed = Config::Aimbot::TripleTakeSpeed;
    AimAssist->TripleTakeSmooth = Config::Aimbot::TripleTakeSmooth;
    AimAssist->VoltSpeed = Config::Aimbot::VoltSpeed;
    AimAssist->VoltSmooth = Config::Aimbot::VoltSmooth;
    AimAssist->NemesisSpeed = Config::Aimbot::NemesisSpeed;
    AimAssist->NemesisSmooth = Config::Aimbot::NemesisSmooth;
    AimAssist->MozambiqueSpeed = Config::Aimbot::MozambiqueSpeed;
    AimAssist->MozambiqueSmooth = Config::Aimbot::MozambiqueSmooth;
    AimAssist->EVA8Speed = Config::Aimbot::EVA8Speed;
    AimAssist->EVA8Smooth = Config::Aimbot::EVA8Smooth;
    AimAssist->PeacekeeperSpeed = Config::Aimbot::PeacekeeperSpeed;
    AimAssist->PeacekeeperSmooth = Config::Aimbot::PeacekeeperSmooth;
    AimAssist->MastiffSpeed = Config::Aimbot::MastiffSpeed;
    AimAssist->MastiffSmooth = Config::Aimbot::MastiffSmooth;
    AimAssist->LongbowSpeed = Config::Aimbot::LongbowSpeed;
    AimAssist->LongbowSmooth = Config::Aimbot::LongbowSmooth;
    AimAssist->ChargeRifleSpeed = Config::Aimbot::ChargeRifleSpeed;
    AimAssist->ChargeRifleSmooth = Config::Aimbot::ChargeRifleSmooth;
    AimAssist->SentinelSpeed = Config::Aimbot::SentinelSpeed;
    AimAssist->SentinelSmooth = Config::Aimbot::SentinelSmooth;
    AimAssist->WingmanSpeed = Config::Aimbot::WingmanSpeed;
    AimAssist->WingmanSmooth = Config::Aimbot::WingmanSmooth;
    AimAssist->ProwlerSpeed = Config::Aimbot::ProwlerSpeed;
    AimAssist->ProwlerSmooth = Config::Aimbot::ProwlerSmooth;
    AimAssist->BocekSpeed = Config::Aimbot::BocekSpeed;
    AimAssist->BocekSmooth = Config::Aimbot::BocekSmooth;
    AimAssist->KraberSpeed = Config::Aimbot::KraberSpeed;
    AimAssist->KraberSmooth = Config::Aimbot::KraberSmooth;
    AimAssist->ThrowingKnifeSpeed = Config::Aimbot::ThrowingKnifeSpeed;
    AimAssist->ThrowingKnifeSmooth = Config::Aimbot::ThrowingKnifeSmooth;
    
    //RCS //
    Recoil->RCSEnabled = Config::RCS::RCSEnabled;
    Recoil->OnADS = Config::RCS::OnADS;
    Recoil->PitchPower = Config::RCS::PitchPower;
    Recoil->YawPower = Config::RCS::YawPower;
    //Weapons
    Recoil->P2020 = Config::RCS::P2020;
    Recoil->RE45 = Config::RCS::RE45;
    Recoil->Alternator = Config::RCS::Alternator;
    Recoil->R99 = Config::RCS::R99;
    Recoil->R301 = Config::RCS::R301;
    Recoil->Spitfire = Config::RCS::Spitfire;
    Recoil->G7 = Config::RCS::G7;
    Recoil->Flatline = Config::RCS::Flatline;
    Recoil->Hemlock = Config::RCS::Hemlock;
    Recoil->Repeater = Config::RCS::Repeater;
    Recoil->Rampage = Config::RCS::Rampage;
    Recoil->CARSMG = Config::RCS::CARSMG;
    Recoil->Havoc = Config::RCS::Havoc;
    Recoil->Devotion = Config::RCS::Devotion;
    Recoil->LSTAR = Config::RCS::LSTAR;
    Recoil->TripleTake = Config::RCS::TripleTake;
    Recoil->Volt = Config::RCS::Volt;
    Recoil->Nemesis = Config::RCS::Nemesis;
    Recoil->Mozambique = Config::RCS::Mozambique;
    Recoil->EVA8 = Config::RCS::EVA8;
    Recoil->Peacekeeper = Config::RCS::Peacekeeper;
    Recoil->Mastiff = Config::RCS::Mastiff;
    Recoil->Longbow = Config::RCS::Longbow;
    Recoil->ChargeRifle = Config::RCS::ChargeRifle;
    Recoil->Sentinel = Config::RCS::Sentinel;
    Recoil->Wingman = Config::RCS::Wingman;
    Recoil->Prowler = Config::RCS::Prowler;
    Recoil->Kraber = Config::RCS::Kraber;
    
    //---------------Advanced---------------//
    Recoil->AdvancedRCS = Config::RCS::AdvancedRCS;
    //Weapons
    Recoil->P2020Pitch = Config::RCS::P2020Pitch;
    Recoil->P2020Yaw = Config::RCS::P2020Yaw;
    Recoil->RE45Pitch = Config::RCS::RE45Pitch;
    Recoil->RE45Yaw = Config::RCS::RE45Yaw;
    Recoil->AlternatorPitch = Config::RCS::AlternatorPitch;
    Recoil->AlternatorYaw = Config::RCS::AlternatorYaw;
    Recoil->R99Pitch = Config::RCS::R99Pitch;
    Recoil->R99Yaw = Config::RCS::R99Yaw;
    Recoil->R301Pitch = Config::RCS::R301Pitch;
    Recoil->R301Yaw = Config::RCS::R301Yaw;
    Recoil->SpitfirePitch = Config::RCS::SpitfirePitch;
    Recoil->SpitfireYaw = Config::RCS::SpitfireYaw;
    Recoil->G7Pitch = Config::RCS::G7Pitch;
    Recoil->G7Yaw = Config::RCS::G7Yaw;
    Recoil->FlatlinePitch = Config::RCS::FlatlinePitch;
    Recoil->FlatlineYaw = Config::RCS::FlatlineYaw;
    Recoil->HemlockPitch = Config::RCS::HemlockPitch;
    Recoil->HemlockYaw = Config::RCS::HemlockYaw;
    Recoil->RepeaterPitch = Config::RCS::RepeaterPitch;
    Recoil->RepeaterYaw = Config::RCS::RepeaterYaw;
    Recoil->RampagePitch = Config::RCS::RampagePitch;
    Recoil->RampageYaw = Config::RCS::RampageYaw;
    Recoil->CARSMGPitch = Config::RCS::CARSMGPitch;
    Recoil->CARSMGYaw = Config::RCS::CARSMGYaw;
    Recoil->HavocPitch = Config::RCS::HavocPitch;
    Recoil->HavocYaw = Config::RCS::HavocYaw;
    Recoil->DevotionPitch = Config::RCS::DevotionPitch;
    Recoil->DevotionYaw = Config::RCS::DevotionYaw;
    Recoil->LSTARPitch = Config::RCS::LSTARPitch;
    Recoil->LSTARYaw = Config::RCS::LSTARYaw;
    Recoil->TripleTakePitch = Config::RCS::TripleTakePitch;
    Recoil->TripleTakeYaw = Config::RCS::TripleTakeYaw;
    Recoil->VoltPitch = Config::RCS::VoltPitch;
    Recoil->VoltYaw = Config::RCS::VoltYaw;
    Recoil->NemesisPitch = Config::RCS::NemesisPitch;
    Recoil->NemesisYaw = Config::RCS::NemesisYaw;
    Recoil->MozambiquePitch = Config::RCS::MozambiquePitch;
    Recoil->MozambiqueYaw = Config::RCS::MozambiqueYaw;
    Recoil->EVA8Pitch = Config::RCS::EVA8Pitch;
    Recoil->EVA8Yaw = Config::RCS::EVA8Yaw;
    Recoil->PeacekeeperPitch = Config::RCS::PeacekeeperPitch;
    Recoil->PeacekeeperYaw = Config::RCS::PeacekeeperYaw;
    Recoil->MastiffPitch = Config::RCS::MastiffPitch;
    Recoil->MastiffYaw = Config::RCS::MastiffYaw;
    Recoil->LongbowPitch = Config::RCS::LongbowPitch;
    Recoil->LongbowYaw = Config::RCS::LongbowYaw;
    Recoil->ChargeRiflePitch = Config::RCS::ChargeRiflePitch;
    Recoil->ChargeRifleYaw = Config::RCS::ChargeRifleYaw;
    Recoil->SentinelPitch = Config::RCS::SentinelPitch;
    Recoil->SentinelYaw = Config::RCS::SentinelYaw;
    Recoil->WingmanPitch = Config::RCS::WingmanPitch;
    Recoil->WingmanYaw = Config::RCS::WingmanYaw;
    Recoil->ProwlerPitch = Config::RCS::ProwlerPitch;
    Recoil->ProwlerYaw = Config::RCS::ProwlerYaw;
    Recoil->KraberPitch = Config::RCS::KraberPitch;
    Recoil->KraberYaw = Config::RCS::KraberYaw;
    
    // Glow //
    GlowESP->GlowEnabled = Config::Glow::GlowEnabled;
    GlowESP->ItemGlow = Config::Glow::ItemGlow;
    GlowESP->GlowMaxDistance = Config::Glow::GlowMaxDistance;
    GlowESP->NewGlow = Config::Glow::NewGlow;
    GlowESP->GlowColorMode = Config::Glow::GlowColorMode;
    GlowESP->GlowColorShieldMode = Config::Glow::GlowColorShieldMode;
    GlowESP->GlowRadius = Config::Glow::GlowRadius;
    GlowESP->InsideFunction = Config::Glow::InsideFunction;
    GlowESP->OutlineFunction = Config::Glow::OutlineFunction;
    GlowESP->BodyStyle = Config::Glow::BodyStyle;
    GlowESP->OutlineStyle = Config::Glow::OutlineStyle;
    GlowESP->InvisibleGlowColor[3] = Config::Glow::InvisibleGlowColor[3];
    GlowESP->VisibleGlowColor[3] = Config::Glow::VisibleGlowColor[3];
    
    // ESP //
    ESP->VisibilityCheck = Config::Sense::VisibilityCheck;
    ESP->DrawSeer = Config::Sense::DrawSeer;
    ESP->DrawStatus = Config::Sense::DrawStatus;
    ESP->ShowMaxStatusValues = Config::Sense::ShowMaxStatusValues;
    ESP->HealthBar = Config::Sense::HealthBar;
    ESP->ShieldBar = Config::Sense::ShieldBar;
    ESP->BarThickness = Config::Sense::BarThickness;
    ESP->ESPMaxDistance = Config::Sense::ESPMaxDistance;
    ESP->ShowSpectators = Config::Sense::ShowSpectators;
    ESP->DrawFOVCircle = Config::Sense::DrawFOVCircle;
    ESP->DrawFilledFOVCircle = Config::Sense::DrawFilledFOVCircle;
    ESP->FOVThickness = Config::Sense::FOVThickness;
    ESP->GameFOV = Config::Sense::GameFOV;
    ESP->DrawDistance = Config::Sense::DrawDistance;
    ESP->DrawBox = Config::Sense::DrawBox;
    ESP->DrawFilledBox = Config::Sense::DrawFilledBox;
    ESP->BoxThickness = Config::Sense::BoxThickness;
    ESP->DrawNames = Config::Sense::DrawNames;
    ESP->DrawWeapon = Config::Sense::DrawWeapon;
    ESP->WeaponColorType = Config::Sense::WeaponColorType;
    ESP->ShowLegend = Config::Sense::ShowLegend;
    ESP->DrawDistance = Config::Sense::DrawDistance;
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
    // Weapons //
    Trigger->P2020 = Config::Triggerbot::P2020;
    Trigger->RE45 = Config::Triggerbot::RE45;
    Trigger->Alternator = Config::Triggerbot::Alternator;
    Trigger->R99 = Config::Triggerbot::R99;
    Trigger->R301 = Config::Triggerbot::R301;
    Trigger->Spitfire = Config::Triggerbot::Spitfire;
    Trigger->G7 = Config::Triggerbot::G7;
    Trigger->Flatline = Config::Triggerbot::Flatline;
    Trigger->Hemlock = Config::Triggerbot::Hemlock;
    Trigger->Repeater = Config::Triggerbot::Repeater;
    Trigger->Rampage = Config::Triggerbot::Rampage;
    Trigger->CARSMG = Config::Triggerbot::CARSMG;
    Trigger->Havoc = Config::Triggerbot::Havoc;
    Trigger->Devotion = Config::Triggerbot::Devotion;
    Trigger->LSTAR = Config::Triggerbot::LSTAR;
    Trigger->TripleTake = Config::Triggerbot::TripleTake;
    Trigger->Volt = Config::Triggerbot::Volt;
    Trigger->Nemesis = Config::Triggerbot::Nemesis;
    Trigger->Mozambique = Config::Triggerbot::Mozambique;
    Trigger->EVA8 = Config::Triggerbot::EVA8;
    Trigger->Peacekeeper = Config::Triggerbot::Peacekeeper;
    Trigger->Mastiff = Config::Triggerbot::Mastiff;
    Trigger->Longbow = Config::Triggerbot::Longbow;
    Trigger->ChargeRifle = Config::Triggerbot::ChargeRifle;
    Trigger->Sentinel = Config::Triggerbot::Sentinel;
    Trigger->Wingman = Config::Triggerbot::Wingman;
    Trigger->Prowler = Config::Triggerbot::Prowler;
    Trigger->Bocek = Config::Triggerbot::Bocek;
    Trigger->Kraber = Config::Triggerbot::Kraber;
    Trigger->Knife = Config::Triggerbot::Knife;
    
    // Misc //
    //MiscTab->Superglide = Config::Misc::Superglide;
    MiscTab->SkinChanger = Config::Misc::SkinChanger;
    // Weapons //
    MiscTab->SkinP2020 = Config::Misc::SkinP2020;
    MiscTab->SkinRE45 = Config::Misc::SkinRE45;
    MiscTab->SkinALTERNATOR = Config::Misc::SkinALTERNATOR;
    MiscTab->SkinR99 = Config::Misc::SkinR99;
    MiscTab->SkinR301 = Config::Misc::SkinR301;
    MiscTab->SkinSPITFIRE = Config::Misc::SkinSPITFIRE;
    MiscTab->SkinG7 = Config::Misc::SkinG7;
    MiscTab->SkinFLATLINE = Config::Misc::SkinFLATLINE;
    MiscTab->SkinHEMLOCK = Config::Misc::SkinHEMLOCK;
    MiscTab->SkinREPEATER = Config::Misc::SkinREPEATER;
    MiscTab->SkinRAMPAGE = Config::Misc::SkinRAMPAGE;
    MiscTab->SkinCAR = Config::Misc::SkinCAR;
    MiscTab->SkinHAVOC = Config::Misc::SkinHAVOC;
    MiscTab->SkinDEVOTION = Config::Misc::SkinDEVOTION;
    MiscTab->SkinLSTAR = Config::Misc::SkinLSTAR;
    MiscTab->SkinTRIPLETAKE = Config::Misc::SkinTRIPLETAKE;
    MiscTab->SkinVOLT = Config::Misc::SkinVOLT;
    MiscTab->SkinNEMESIS = Config::Misc::SkinNEMESIS;
    MiscTab->SkinMOZAMBIQUE = Config::Misc::SkinMOZAMBIQUE;
    MiscTab->SkinEVA8 = Config::Misc::SkinEVA8;
    MiscTab->SkinPEACEKEEPER = Config::Misc::SkinPEACEKEEPER;
    MiscTab->SkinMASTIFF = Config::Misc::SkinMASTIFF;
    MiscTab->SkinLONGBOW = Config::Misc::SkinLONGBOW;
    MiscTab->SkinCHARGE_RIFLE = Config::Misc::SkinCHARGE_RIFLE;
    MiscTab->SkinSENTINEL = Config::Misc::SkinSENTINEL;
    MiscTab->SkinWINGMAN = Config::Misc::SkinWINGMAN;
    MiscTab->SkinPROWLER = Config::Misc::SkinPROWLER;
    MiscTab->SkinBOCEK = Config::Misc::SkinBOCEK;
    MiscTab->SkinKRABER = Config::Misc::SkinKRABER;
    
    // Home //
    AsciiArt = Config::Home::AsciiArt; //change the starting ascii art. 0 = cat 1, 1 = shotgun, 2 = glock, 3 = racoon, 4 = cat 2, 5 = zap-client
    AsciiArtSpeed = Config::Home::AsciiArtSpeed; //Speed (in milliseconds) of the ascii art
    Home->MenuX = Config::Home::MenuX;
    Home->MenuY = Config::Home::MenuY;
    Home->TeamGamemode = Config::Home::TeamGamemode;
    Home->ErrorLogging = Config::Home::ErrorLogging;
}

void LoadOverlaySave() {
    // Overlay //
    // Styling //
    if (Config::Home::Style == 0) {
	Home->Alpha                   = 1.0f;             
	Home->WindowPadding           = ImVec2(8,8);      
	Home->WindowRounding          = 0.0f;             
	Home->WindowBorderSize        = 1.0f;             
	Home->WindowMinSize           = ImVec2(32,32);    
	Home->WindowTitleAlign        = ImVec2(0.0f,0.5f);
	Home->ChildRounding           = 0.0f;             
	Home->ChildBorderSize         = 1.0f;             
	Home->PopupRounding           = 0.0f;            
	Home->PopupBorderSize         = 1.0f;        
	Home->FramePadding            = ImVec2(4,3);    
	Home->FrameRounding           = 0.0f;          
	Home->FrameBorderSize         = 0.0f;       
	Home->ItemSpacing             = ImVec2(8,4);    
	Home->ItemInnerSpacing        = ImVec2(4,4);     
	Home->CellPadding             = ImVec2(4,2);      
	Home->TouchExtraPadding       = ImVec2(0,0);     
	Home->IndentSpacing           = 21.0f;          
	Home->ColumnsMinSpacing       = 6.0f;            
	Home->ScrollbarSize           = 14.0f;          
	Home->ScrollbarRounding       = 9.0f;         
	Home->GrabMinSize             = 10.0f;      
	Home->GrabRounding            = 0.0f;          
	Home->LogSliderDeadzone       = 4.0f;             
	Home->TabRounding             = 4.0f;         
	Home->TabBorderSize           = 0.0f;            
	Home->TabMinWidthForCloseButton = 0.0f;           
	Home->ButtonTextAlign         = ImVec2(0.5f,0.5f);
	Home->SelectableTextAlign     = ImVec2(0.0f,0.0f);
    }
    
    if (Config::Home::Style == 1) {
	Home->Alpha 			= 1.0f;
	Home->DisabledAlpha 		= 1.0f;
	Home->WindowPadding 		= ImVec2(12.0f, 12.0f);
	Home->WindowRounding 		= 0.0f;
	Home->WindowBorderSize 	= 0.0f;
	Home->WindowMinSize 		= ImVec2(20.0f, 20.0f);
	Home->WindowTitleAlign 	= ImVec2(0.5f, 0.5f);
	Home->ChildRounding 		= 0.0f;
	Home->ChildBorderSize 	= 1.0f;
	Home->PopupRounding 		= 0.0f;
	Home->PopupBorderSize 	= 1.0f;
	Home->FramePadding 		= ImVec2(6.0f, 6.0f);
	Home->FrameRounding 		= 0.0f;
	Home->FrameBorderSize 	= 0.0f;
	Home->ItemSpacing 		= ImVec2(12.0f, 6.0f);
	Home->ItemInnerSpacing 	= ImVec2(6.0f, 3.0f);
	Home->CellPadding 		= ImVec2(12.0f, 6.0f);
	Home->IndentSpacing 		= 20.0f;
	Home->ColumnsMinSpacing 	= 6.0f;
	Home->ScrollbarSize 		= 12.0f;
	Home->ScrollbarRounding 	= 0.0f;
	Home->GrabMinSize 		= 12.0f;
	Home->GrabRounding 		= 0.0f;
	Home->TabRounding 		= 0.0f;
	Home->TabBorderSize 		= 0.0f;
	Home->TabMinWidthForCloseButton = 0.0f;
	Home->ButtonTextAlign 	= ImVec2(0.5f, 0.5f);
	Home->SelectableTextAlign 	= ImVec2(0.0f, 0.0f);
	Home->LogSliderDeadzone 	= 4;
    }
    if (Config::Home::Style == 2) {
	Home->Alpha			   = 1.0f;
	Home->DisabledAlpha 		   = 1.0f;
	Home->WindowPadding                   = ImVec2(8.00f, 8.00f);
	Home->FramePadding                    = ImVec2(5.00f, 2.00f);
	Home->CellPadding                     = ImVec2(6.00f, 6.00f);
	Home->ItemSpacing                     = ImVec2(6.00f, 6.00f);
	Home->ItemInnerSpacing                = ImVec2(6.00f, 6.00f);
	Home->TouchExtraPadding               = ImVec2(0.00f, 0.00f);
	Home->WindowTitleAlign                = ImVec2(0.5f, 0.5f);
	Home->IndentSpacing                      = 25;
	Home->ScrollbarSize                      = 15;
	Home->GrabMinSize                        = 10;
	Home->WindowBorderSize                   = 1;
	Home->ChildBorderSize                    = 1;
	Home->PopupBorderSize                    = 1;
	Home->FrameBorderSize                    = 1;
	Home->TabBorderSize                      = 1;
	Home->WindowRounding                     = 7;
	Home->ChildRounding                      = 4;
	Home->FrameRounding                      = 3;
	Home->PopupRounding                      = 4;
	Home->ScrollbarRounding                  = 9;
	Home->GrabRounding                       = 3;
	Home->LogSliderDeadzone                  = 4;
	Home->TabRounding                        = 4;
    }
    
    if (Config::Home::Style == 3) {
	Home->Alpha = 1.0f;
	Home->DisabledAlpha = 1.0f;
	Home->WindowPadding = ImVec2(12.0f, 12.0f);
	Home->WindowRounding = 3.0f;
	Home->WindowBorderSize = 0.0f;
	Home->WindowMinSize = ImVec2(20.0f, 20.0f);
	Home->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	Home->ChildRounding = 3.0f;
	Home->ChildBorderSize = 1.0f;
	Home->PopupRounding = 0.0f;
	Home->PopupBorderSize = 1.0f;
	Home->FramePadding = ImVec2(6.0f, 6.0f);
	Home->FrameRounding = 3.0f;
	Home->FrameBorderSize = 0.0f;
	Home->ItemSpacing = ImVec2(12.0f, 6.0f);
	Home->ItemInnerSpacing = ImVec2(6.0f, 3.0f);
	Home->CellPadding = ImVec2(12.0f, 6.0f);
	Home->IndentSpacing = 20.0f;
	Home->ColumnsMinSpacing = 6.0f;
	Home->ScrollbarSize = 12.0f;
	Home->ScrollbarRounding = 0.0f;
	Home->GrabMinSize = 20.0f;
	Home->GrabRounding = 1.0f;
	Home->TabRounding = 0.0f;
	Home->TabBorderSize = 0.0f;
	Home->TabMinWidthForCloseButton = 0.0f;
	Home->ButtonTextAlign = ImVec2(0.5f, 0.5f);
	Home->SelectableTextAlign = ImVec2(0.0f, 0.0f);
    }
    
    if (Config::Home::Style == 4) {
	Home->Alpha			   = 1.0f;
	Home->DisabledAlpha                   = 1.0f;
	Home->WindowPadding                   = ImVec2(8.00f, 8.00f);
	Home->FramePadding                    = ImVec2(5.00f, 2.00f);
	Home->CellPadding                     = ImVec2(6.00f, 6.00f);
	Home->ItemSpacing                     = ImVec2(6.00f, 6.00f);
	Home->ItemInnerSpacing                = ImVec2(6.00f, 6.00f);
	Home->TouchExtraPadding               = ImVec2(0.00f, 0.00f);
	Home->WindowTitleAlign                = ImVec2(0.5f, 0.5f);
	Home->IndentSpacing                      = 25;
	Home->ScrollbarSize                      = 15;
	Home->GrabMinSize                        = 10;
	Home->WindowBorderSize                   = 1;
	Home->ChildBorderSize                    = 1;
	Home->PopupBorderSize                    = 1;
	Home->FrameBorderSize                    = 1;
	Home->TabBorderSize                      = 1;
	Home->WindowRounding                     = 7;
	Home->ChildRounding                      = 4;
	Home->FrameRounding                      = 3;
	Home->PopupRounding                      = 4;
	Home->ScrollbarRounding                  = 9;
	Home->GrabRounding                       = 3;
	Home->LogSliderDeadzone                  = 4;
	Home->TabRounding                        = 4;
    }
    
    if (Config::Home::Style == 5) {
	Home->Alpha = 1.0f;
	Home->DisabledAlpha = 1.0f;
	Home->WindowPadding = ImVec2(12.0f, 12.0f);
	Home->WindowRounding = 11.5f;
	Home->WindowBorderSize = 0.0f;
	Home->WindowMinSize = ImVec2(20.0f, 20.0f);
	Home->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	Home->ChildRounding = 0.0f;
	Home->ChildBorderSize = 1.0f;
	Home->PopupRounding = 0.0f;
	Home->PopupBorderSize = 1.0f;
	Home->FramePadding = ImVec2(20.0f, 3.400000095367432f);
	Home->FrameRounding = 11.89999961853027f;
	Home->FrameBorderSize = 0.0f;
	Home->ItemSpacing = ImVec2(4.300000190734863f, 5.5f);
	Home->ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
	Home->CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
	Home->IndentSpacing = 0.0f;
	Home->ColumnsMinSpacing = 4.900000095367432f;
	Home->ScrollbarSize = 11.60000038146973f;
	Home->ScrollbarRounding = 15.89999961853027f;
	Home->GrabMinSize = 3.700000047683716f;
	Home->GrabRounding = 20.0f;
	Home->TabRounding = 0.0f;
	Home->TabBorderSize = 0.0f;
	Home->TabMinWidthForCloseButton = 0.0f;
	Home->ButtonTextAlign = ImVec2(0.5f, 0.5f);
	Home->SelectableTextAlign = ImVec2(0.0f, 0.0f);
    }
    
    // Colors //
    if (Config::Home::Color == 0) {
	Home->Text                   = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	Home->TextDisabled           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	Home->WindowBg               = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	Home->ChildBg                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Home->PopupBg                = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
	Home->Border                 = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
	Home->BorderShadow           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Home->FrameBg                = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
	Home->FrameBgHovered         = ImVec4(0.47f, 0.47f, 0.69f, 0.40f);
	Home->FrameBgActive          = ImVec4(0.42f, 0.41f, 0.64f, 0.69f);
	Home->TitleBg                = ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
	Home->TitleBgActive          = ImVec4(0.32f, 0.32f, 0.63f, 0.87f);
	Home->TitleBgCollapsed       = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
	Home->MenuBarBg              = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
	Home->ScrollbarBg            = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
	Home->ScrollbarGrab          = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
	Home->ScrollbarGrabHovered   = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
	Home->ScrollbarGrabActive    = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
	Home->CheckMark              = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
	Home->SliderGrab             = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	Home->SliderGrabActive       = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
	Home->Button                 = ImVec4(0.35f, 0.40f, 0.61f, 0.62f);
	Home->ButtonHovered          = ImVec4(0.40f, 0.48f, 0.71f, 0.79f);
	Home->ButtonActive           = ImVec4(0.46f, 0.54f, 0.80f, 1.00f);
	Home->Header                 = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
	Home->HeaderHovered          = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
	Home->HeaderActive           = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
	Home->Separator              = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
	Home->SeparatorHovered       = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
	Home->SeparatorActive        = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);
	Home->ResizeGrip             = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	Home->ResizeGripHovered      = ImVec4(0.78f, 0.82f, 1.00f, 0.60f);
	Home->ResizeGripActive       = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);
	Home->TabHovered             = Home->HeaderHovered;
	Home->PlotLines              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	Home->PlotLinesHovered       = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	Home->PlotHistogram          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	Home->PlotHistogramHovered   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	Home->TableHeaderBg          = ImVec4(0.27f, 0.27f, 0.38f, 1.00f);
	Home->TableBorderStrong      = ImVec4(0.31f, 0.31f, 0.45f, 1.00f);
	Home->TableBorderLight       = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);
	Home->TableRowBg             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Home->TableRowBgAlt          = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
	Home->TextSelectedBg         = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	Home->DragDropTarget         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	Home->NavHighlight           = Home->HeaderHovered;
	Home->NavWindowingHighlight  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	Home->NavWindowingDimBg      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	Home->ModalWindowDimBg       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    }
    if (Config::Home::Color == 1) {
	Home->Text 		= ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	Home->TextDisabled 	= ImVec4(0.27f, 0.31f, 0.45f, 1.0f);
	Home->WindowBg 		= ImVec4(0.07f, 0.08f, 0.10f, 1.00f);
	Home->ChildBg 		= ImVec4(0.078f, 0.08f, 0.10f, 1.0f);
	Home->PopupBg 		= ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->Border 		= ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
	Home->BorderShadow 	= ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->FrameBg 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->FrameBgHovered 	= ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
	Home->FrameBgActive 	= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
	Home->TitleBg 		= ImVec4(0.047f, 0.05f, 0.07f, 1.0f);
	Home->TitleBgActive 	= ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
	Home->TitleBgCollapsed 	= ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->MenuBarBg 		= ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
	Home->ScrollbarBg 		= ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
	Home->ScrollbarGrab 	= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->ScrollbarGrabHovered = ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
	Home->ScrollbarGrabActive 	= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->CheckMark 		= ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
	Home->SliderGrab 		= ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
	Home->SliderGrabActive 	= ImVec4(0.53f, 0.55f, 1.0f, 1.0f);
	Home->Button 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->ButtonHovered 	= ImVec4(0.19f, 0.17f, 0.54f, 1.0f);
	Home->ButtonActive 	= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
	Home->Header 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->HeaderHovered 	= ImVec4(0.19f, 0.17f, 0.54f, 1.0f);
	Home->HeaderActive 	= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
	Home->Separator 		= ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
	Home->SeparatorHovered 	= ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
	Home->SeparatorActive 	= ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
	Home->ResizeGrip 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->ResizeGripHovered 	= ImVec4(0.19f, 0.17f, 0.54f, 1.0f);
	Home->ResizeGripActive 	= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
	Home->Tab 			= ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
	Home->TabHovered 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->TabActive 		= ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
	Home->TabUnfocused 	= ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
	Home->TabUnfocusedActive 	= ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->PlotLines 		= ImVec4(0.52f, 0.60f, 0.70f, 1.0f);
	Home->PlotLinesHovered 	= ImVec4(0.03f, 0.98f, 0.98f, 1.0f);
	Home->PlotHistogram 	= ImVec4(1.0f, 0.29f, 0.59f, 1.0f);
	Home->PlotHistogramHovered = ImVec4(0.99f, 0.47f, 0.69f, 1.0f);
	Home->TableHeaderBg 	= ImVec4(0.047f, 0.05f, 0.07f, 1.0f);
	Home->TableBorderStrong 	= ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
	Home->TableBorderLight 	= ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	Home->TableRowBg 		= ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->TableRowBgAlt 	= ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
	Home->TextSelectedBg 	= ImVec4(0.23f, 0.21f, 0.59f, 1.0f);
	Home->DragDropTarget 	= ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
	Home->NavHighlight 	= ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
	Home->NavWindowingHighlight = ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
	Home->NavWindowingDimBg 	= ImVec4(0.19f, 0.17f, 0.54f, 0.50f);
	Home->ModalWindowDimBg 	= ImVec4(0.19f, 0.17f, 0.54f, 0.50f);
    }
    if (Config::Home::Color == 2) {
	Home->Text                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	Home->TextDisabled           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	Home->WindowBg               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	Home->ChildBg                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Home->PopupBg                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	Home->Border                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	Home->BorderShadow           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	Home->FrameBg                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	Home->FrameBgHovered         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	Home->FrameBgActive          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	Home->TitleBg                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	Home->TitleBgActive          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	Home->TitleBgCollapsed       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	Home->MenuBarBg              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	Home->ScrollbarBg            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	Home->ScrollbarGrab          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	Home->ScrollbarGrabHovered   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	Home->ScrollbarGrabActive    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	Home->CheckMark              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	Home->SliderGrab             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	Home->SliderGrabActive       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	Home->Button                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	Home->ButtonHovered          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	Home->ButtonActive           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	Home->Header                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	Home->HeaderHovered          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	Home->HeaderActive           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	Home->Separator              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	Home->SeparatorHovered       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	Home->SeparatorActive        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	Home->ResizeGrip             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	Home->ResizeGripHovered      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	Home->ResizeGripActive       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	Home->Tab                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	Home->TabHovered             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	Home->TabActive              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
	Home->TabUnfocused           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	Home->TabUnfocusedActive     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	Home->PlotLines              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	Home->PlotLinesHovered       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	Home->PlotHistogram          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	Home->PlotHistogramHovered   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	Home->TableHeaderBg          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	Home->TableBorderStrong      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	Home->TableBorderLight       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	Home->TableRowBg             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Home->TableRowBgAlt          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	Home->TextSelectedBg         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	Home->DragDropTarget         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	Home->NavHighlight           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	Home->NavWindowingHighlight  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	Home->NavWindowingDimBg      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	Home->ModalWindowDimBg       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
    }
    if (Config::Home::Color == 3) {
	Home->Text = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	Home->TextDisabled = ImVec4(0.00f, 0.40f, 0.41f, 1.00f);
	Home->WindowBg = ImVec4(0.00f, 0.00f, 0.00f, 0.7f);
	Home->Border = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
	Home->BorderShadow = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Home->FrameBg = ImVec4(0.00f, 1.00f, 1.00f, 0.18f);
	Home->FrameBgHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
	Home->FrameBgActive = ImVec4(0.00f, 1.00f, 1.00f, 0.66f);
	Home->PlotLines = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
	Home->Tab = ImVec4(0.00f, 1.00f, 1.00f, 0.18f);
	Home->TabHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.60f);
	Home->TabActive = ImVec4(0.00f, 1.00f, 1.00f, 0.60f);
	Home->TitleBg = ImVec4(0.14f, 0.18f, 0.21f, 0.73f);
	Home->TitleBgCollapsed = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
	Home->TitleBgActive = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
	Home->MenuBarBg = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
	Home->ScrollbarBg = ImVec4(0.22f, 0.29f, 0.30f, 0.71f);
	Home->ScrollbarGrab = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
	Home->ScrollbarGrabHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
	Home->ScrollbarGrabActive = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	Home->Separator = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
	Home->CheckMark = ImVec4(0.00f, 1.00f, 1.00f, 0.68f);
	Home->SliderGrab = ImVec4(0.00f, 1.00f, 1.00f, 0.36f);
	Home->SliderGrabActive = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
	Home->Button = ImVec4(0.00f, 0.65f, 0.65f, 0.46f);
	Home->ButtonHovered = ImVec4(0.01f, 1.00f, 1.00f, 0.43f);
	Home->ButtonActive = ImVec4(0.00f, 1.00f, 1.00f, 0.62f);
	Home->Header = ImVec4(0.00f, 1.00f, 1.00f, 0.33f);
	Home->HeaderHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.42f);
	Home->HeaderActive = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
	Home->ResizeGrip = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
	Home->ResizeGripHovered = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
	Home->ResizeGripActive = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	Home->PlotLinesHovered = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	Home->PlotHistogram = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	Home->PlotHistogramHovered = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	Home->TextSelectedBg = ImVec4(0.00f, 1.00f, 1.00f, 0.22f);    
    }
    if (Config::Home::Color == 4) {
	Home->Text                   = ImVec4(0.00f, 0.82f, 1.00f, 1.00f);
	Home->TextDisabled           = ImVec4(0.00f, 0.36f, 0.63f, 1.00f);
	Home->WindowBg               = ImVec4(0.00f, 0.04f, 0.12f, 1.00f);
	Home->ChildBg                = ImVec4(0.03f, 0.04f, 0.22f, 1.00f);
	Home->PopupBg                = ImVec4(0.12f, 0.06f, 0.27f, 1.00f);
	Home->Border                 = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
	Home->FrameBg                = ImVec4(0.00f, 0.75f, 1.00f, 0.20f);
	Home->FrameBgHovered         = ImVec4(0.34f, 0.00f, 1.00f, 1.00f);
	Home->FrameBgActive          = ImVec4(0.08f, 0.00f, 1.00f, 1.00f);
	Home->TitleBg                = ImVec4(0.00f, 0.81f, 0.95f, 1.00f);
	Home->TitleBgActive          = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
	Home->TitleBgCollapsed       = ImVec4(0.25f, 0.00f, 0.54f, 0.81f);
	Home->MenuBarBg              = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
	Home->ScrollbarBg            = ImVec4(0.00f, 0.88f, 1.00f, 1.00f);
	Home->ScrollbarGrab          = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
	Home->ScrollbarGrabHovered   = ImVec4(0.01f, 0.00f, 1.00f, 1.00f);
	Home->ScrollbarGrabActive    = ImVec4(0.95f, 0.19f, 0.67f, 1.00f);
	Home->CheckMark              = ImVec4(0.95f, 0.19f, 0.92f, 1.00f);
	Home->SliderGrab             = ImVec4(0.00f, 1.00f, 0.95f, 1.00f);
	Home->SliderGrabActive       = ImVec4(0.81f, 0.00f, 1.00f, 1.00f);
	Home->Button                 = ImVec4(0.00f, 0.98f, 1.00f, 0.52f);
	Home->ButtonHovered          = ImVec4(0.94f, 0.00f, 1.00f, 0.80f);
	Home->ButtonActive           = ImVec4(0.01f, 0.00f, 1.00f, 1.00f);
	Home->Header                 = ImVec4(0.00f, 0.95f, 1.00f, 0.40f);
	Home->HeaderHovered          = ImVec4(0.94f, 0.00f, 1.00f, 0.80f);
	Home->HeaderActive           = ImVec4(0.01f, 0.00f, 1.00f, 1.00f);
	Home->Separator              = ImVec4(0.74f, 0.00f, 1.00f, 0.50f);
	Home->SeparatorHovered       = ImVec4(0.34f, 0.00f, 1.00f, 0.78f);
	Home->SeparatorActive        = ImVec4(0.00f, 1.00f, 0.85f, 1.00f);
	Home->ResizeGrip             = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
	Home->ResizeGripHovered      = ImVec4(0.89f, 0.26f, 0.98f, 0.67f);
	Home->ResizeGripActive       = ImVec4(0.00f, 0.88f, 1.00f, 0.95f);
	Home->Tab                    = ImVec4(0.36f, 0.00f, 1.00f, 1.00f);
	Home->TabHovered             = ImVec4(0.00f, 0.92f, 1.00f, 0.80f);
	Home->TabActive              = ImVec4(0.62f, 0.00f, 0.80f, 1.00f);
	Home->PlotHistogram          = ImVec4(0.00f, 1.00f, 0.88f, 1.00f);    
    }
    if (Config::Home::Color == 5) {
	Home->Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	Home->TextDisabled = ImVec4(0.27f, 0.31f, 0.45f, 1.0f);
	Home->WindowBg = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->ChildBg = ImVec4(0.09f, 0.10f, 0.11f, 1.0f);
	Home->PopupBg = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->Border = ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
	Home->BorderShadow = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->FrameBg = ImVec4(0.11f, 0.12f, 0.15f, 1.0f);
	Home->FrameBgHovered = ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
	Home->FrameBgActive = ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
	Home->TitleBg = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
	Home->TitleBgActive = ImVec4(0.047f, 0.05f, 0.07f, 1.0f);
	Home->TitleBgCollapsed = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->MenuBarBg = ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
	Home->ScrollbarBg = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
	Home->ScrollbarGrab = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->ScrollbarGrabHovered = ImVec4(0.15f, 0.16f, 0.19f, 1.0f);
	Home->ScrollbarGrabActive = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->CheckMark = ImVec4(0.97f, 1.0f, 0.49f, 1.0f);
	Home->SliderGrab = ImVec4(0.97f, 1.0f, 0.49f, 1.0f);
	Home->SliderGrabActive = ImVec4(1.0f, 0.79f, 0.49f, 1.0f);
	Home->Button = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->ButtonHovered = ImVec4(0.18f, 0.18f, 0.19f, 1.0f);
	Home->ButtonActive = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
	Home->Header = ImVec4(0.14f, 0.16f, 0.20f, 1.0f);
	Home->HeaderHovered = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	Home->HeaderActive = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->Separator = ImVec4(0.12f, 0.14f, 0.19f, 1.0f);
	Home->SeparatorHovered = ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
	Home->SeparatorActive = ImVec4(0.15f, 0.18f, 0.25f, 1.0f);
	Home->ResizeGrip = ImVec4(0.14f, 0.14f, 0.14f, 1.0f);
	Home->ResizeGripHovered = ImVec4(0.97f, 1.0f, 0.49f, 1.0f);
	Home->ResizeGripActive = ImVec4(0.99f, 1.0f, 0.99f, 1.0f);
	Home->Tab = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->TabHovered = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->TabActive = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->TabUnfocused = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
	Home->TabUnfocusedActive = ImVec4(0.12f, 0.27f, 0.57f, 1.0f);
	Home->PlotLines = ImVec4(0.52f, 0.60f, 0.70f, 1.0f);
	Home->PlotLinesHovered = ImVec4(0.03f, 0.98f, 0.98f, 1.0f);
	Home->PlotHistogram = ImVec4(0.88f, 0.79f, 0.56f, 1.0f);
	Home->PlotHistogramHovered = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
	Home->TableHeaderBg = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
	Home->TableBorderStrong = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
	Home->TableBorderLight = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	Home->TableRowBg = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
	Home->TableRowBgAlt = ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
	Home->TextSelectedBg = ImVec4(0.93f, 0.93f, 0.93f, 1.0f);
	Home->DragDropTarget = ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
	Home->NavHighlight = ImVec4(0.26f, 0.28f, 1.0f, 1.0f);
	Home->NavWindowingHighlight = ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
	Home->NavWindowingDimBg = ImVec4(0.19f, 0.17f, 0.54f, 0.50f);
	Home->ModalWindowDimBg = ImVec4(0.19f, 0.17f, 0.54f, 0.50f);
    }
    
    if (Config::Home::Color == 6) {
	Home->Text                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	Home->TextDisabled           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	Home->WindowBg               = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->ChildBg                = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->PopupBg                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	Home->Border                 = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->BorderShadow           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Home->FrameBg                = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
	Home->FrameBgHovered         = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
	Home->FrameBgActive          = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
	Home->TitleBg                = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->TitleBgActive          = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->TitleBgCollapsed       = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->MenuBarBg              = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->ScrollbarBg            = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->ScrollbarGrab          = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	Home->ScrollbarGrabHovered   = ImVec4(0.36f, 0.38f, 0.39f, 1.00f);
	Home->ScrollbarGrabActive    = ImVec4(0.36f, 0.38f, 0.39f, 1.00f);
	Home->CheckMark              = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
	Home->SliderGrab             = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
	Home->SliderGrabActive       = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
	Home->Button                 = ImVec4(0.36f, 0.38f, 0.39f, 1.00f);
	Home->ButtonHovered          = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
	Home->ButtonActive           = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
	Home->Header                 = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->HeaderHovered          = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->HeaderActive           = ImVec4(0.27f, 0.27f, 0.28f, 1.00f);
	Home->Separator              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	Home->SeparatorHovered       = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
	Home->SeparatorActive        = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
	Home->ResizeGrip             = ImVec4(0.36f, 0.38f, 0.39f, 1.00f);
	Home->ResizeGripHovered      = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
	Home->ResizeGripActive       = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
	Home->PlotLines              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	Home->PlotLinesHovered       = ImVec4(0.60f, 0.36f, 0.76f, 0.40f);
	Home->PlotHistogram          = ImVec4(0.61f, 0.35f, 0.71f, 1.00f);
	Home->PlotHistogramHovered   = ImVec4(0.56f, 0.27f, 0.68f, 1.00f);
	Home->TextSelectedBg         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	Home->DragDropTarget         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	Home->NavHighlight           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	Home->NavWindowingHighlight  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    }

}

void SaveConfig() {
    if (!Home->Save()) std::cout << "something went wrong trying to save Home settings" << std::endl;
    if (!AimAssist->Save()) std::cout << "something went wrong trying to save Aimbot settings" << std::endl;
    if (!Recoil->Save()) std::cout << "something went wrong trying to save RCS settings" << std::endl;
    if (!ESP->Save()) std::cout << "something went wrong trying to save ESP settings" << std::endl;
    if (!GlowESP->Save()) std::cout << "something went wrong trying to save Glow settings" << std::endl;
    if (!Trigger->Save()) std::cout << "something went wrong trying to save Triggerbot settings" << std::endl;
    if (!MiscTab->Save()) std::cout << "something went wrong trying to save Misc settings" << std::endl;
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
    ImGui::SetNextWindowSizeConstraints(ImVec2(Home->MenuX, Home->MenuY), ImVec2(Home->MenuX, Home->MenuY));
    ImGui::SetNextWindowSize(ImVec2(Home->MenuX, Home->MenuY), ImGuiCond_FirstUseEver);
    ImGui::Begin("zap-client", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    
    ProcessingTimeColor = OverlayWindow.ProcessingTime > 20 ? ProcessingTimeColor = ImVec4(1, 0.343, 0.475, 1) : ProcessingTimeColor = ImVec4(0.4, 1, 0.343, 1);
    ImGui::TextColored(ProcessingTimeColor, "Processing Time: %02dms ", OverlayWindow.ProcessingTime);
    ImGui::SameLine();

    /*if (OverlayWindow.AlignedButton("Save Config")) {
        SaveConfig();
        std::cout << "config saved" << std::endl;
    }    
    ImGui::SameLine();
    if (OverlayWindow.AlignedButton("Load Config")) {
        LoadConfig();
        std::cout << "config loaded" << std::endl;
    }*/   

    if (ImGui::BeginTabBar("Menus"), ImGuiTabBarFlags_NoCloseWithMiddleMouseButton) {
        // Draw Settings //
        Home->SetUIStyle();
        AimAssist->RenderUI();
        Recoil->RenderUI();
        Trigger->RenderUI();
        GlowESP->RenderUI();
        ESP->RenderUI();
        MiscTab->RenderUI();
        
    	if (ImGui::BeginTabItem("Config", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
    		ImGui::Text("Config Options");
    		if (ImGui::Button("Save Config")) {
    			SaveConfig();
        		std::cout << "Config Saved!" << std::endl;
    		}
    		ImGui::SameLine();
    		if (ImGui::Button("Load Config")) {
    			LoadConfig();
        		std::cout << "Config Loaded!" << std::endl;
        	}
        	ImGui::EndTabItem();
        }
    

        // Draw Credits //
        /*if (ImGui::BeginTabItem("Credits", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
            ImGui::TextColored(ImVec4(0.65, 1, 0.95, 1), "Credits:");
            ImGui::TextColored(ImVec4(0.03, 1, 0.95, 1), "arturzxc: ESP, Triggerbot and X11Display's Move Mouse method");
            ImGui::TextColored(ImVec4(0.3, 1, 0.64, 1), "Koelion: ImGui Menu, AimbotResolver");
            ImGui::TextColored(ImVec4(0.3, 0.6, 0.9, 1), "unknowncheats: Offsets and ton of other things");
            ImGui::TextColored(ImVec4(0.6, 1, 0.64, 1), "Made by Azreol/Nexilist");
            ImGui::TextColored(ImVec4(0.744, 0.0400, 1.00, 1), "Pasted + Updated (With love) by Gerosity <3");
            ImGui::EndTabItem();
        }*/

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
        GlowESP->Update();
        Recoil->Update();
        AimAssist->Update();
        Trigger->Update();
        MiscTab->Update();

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

    std::system("clear"); //Ignore These Warnings
    std::cout << " " << std::endl; //Spacing

    if (AsciiArt == 0) {
	    std::cout << "       _                        " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "       \`*-.                    " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "        )  _`-.                 " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "       .  : `. .                " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "       : _   '  \               " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "       ; *` _.   `*-._          " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "       `-.-'          `-.       " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "         ;       `       `.     " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "         :.       .        \    " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "         . \  .   :   .-'   .   " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "         '  `+.;  ;  '      :   " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "         :  '  |    ;       ;-. " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "         ; '   : :`-:     _.`* ;" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "     .*' /  .*' ; .*`- +'  `*' " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "      `*-*   `*-*  `*-*'" << std::endl;
    }
    
    if (AsciiArt == 1) {
	    std::cout << " ,______________________________________       " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "|_________________,----------._ [____]  ""-,__  __....-----=====" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "               (_(||||||||||||)___________/   ""                |" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "                  `----------'        [ )) -,                   |" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "                                       ""    `,  _,--....___    |" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "                                               `/           """"" << std::endl;
    }
    
    if (AsciiArt == 2) {
	    std::cout << " +--^----------,--------,-----,--------^-," << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << " | |||||||||   `--------'     |          O" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << " `+---------------------------^----------|" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "   `\_,---------,---------,--------------'" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "     / XXXXXX /'|       /'" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "    / XXXXXX /  `\    /'" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "   / XXXXXX /`-------'" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "  / XXXXXX /" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << " / XXXXXX /" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "(________(       " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << " `------'          " << std::endl;
    }
    
    if (AsciiArt == 3) {
    	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⡤⠖⠊⠉⠁⠀⠀⠀⠉⠒⢦⡀⠀⠀⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⢀⠀⠀⠀⢀⡔⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣆⠀⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⢧⣻⣆⠴⠯⣄⣤⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⡄⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⢠⠉⢁⡆⠈⠉⠸⠾⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⡄⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠸⣀⠾⢁⡀⠀⠀⠀⠈⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠿⠻⡄⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⡿⠇⠺⠿⠿⡟⣲⠴⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣃⡶⠿⢿⡀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⣦⣦⢀⣀⣤⡞⠁⠀⠀⠀⠀⠀⡠⢄⠀⠀⠀⠀⠀⡴⠻⣏⣶⠞⠛⠷⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠈⠉⠁⣧⠀⠙⡆⠀⠀⠀⠀⠀⠀⢸⠳⣄⡀⠀⠀⢣⠀⣻⣷⠖⠛⢷⡇" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⡟⠀⢀⡇⠀⠀⢀⢲⠛⢉⣥⠒⠁⠀⣀⡤⠋⣠⣿⡿⠿⢶⣸⠃" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⣀⠤⡴⠁⣠⠎⡇⠀⣆⡼⠛⠀⠛⠷⢶⠴⠛⠁⠀⣴⠿⠿⢷⣦⣀⡟⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠛⠿⠵⠷⣋⡴⠁⢠⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣄⣀⠀⢸⡟⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠰⣷⣄⡤⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⡿⠟⠋⠀⠀⠀" << std::endl;
    }
    
    if (AsciiArt == 4) {
    	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣄⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⢻⠟⠙⣷⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⣰⠿⢿⡲⢦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⣰⠋⠀⠀⢸⡇" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠙⠢⣈⠛⢦⣄⠀⣀⣤⣤⡤⠤⠤⢴⣏⣀⡼⠁⠀⠀⠀⠀⡇" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⢿⠀⠀⠀⠀⠘⢲⡤⠞⠋⠁⠀⢸⡇⠀⠀⠀⠀⠈⠉⠲⣄⡀⠀⢀⡇" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠸⣇⠀⠀⢀⡴⠋⠀⠀⠀⠀⠀⢸⠹⡀⠀⠀⠀⠀⣀⠀⠀⠙⣄⣸⠃" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⢻⡀⢠⠏⠀⣀⡠⠤⣄⡀⠀⡏⠀⠳⣄⣴⣾⣍⡉⠉⠓⣄⠈⣧⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡏⢀⡞⠁⢠⣾⡷⠿⣿⡀⠀⠀⣿⣯⣩⣿⣿⣦⠀⢸⡄⢹⡇" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡁⢸⡄⠀⢿⢿⣿⡾⡿⢻⠀⠀⣏⠻⣏⣛⣡⠏⢀⡞⠀⠀⡇" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣇⠀⠳⣄⡈⠓⠶⣛⣡⠞⠠⡷⠈⠓⠚⠛⠒⠚⠙⠒⠦⢼⠇" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣤⡤⢞⡋⠉⠉⢡⡀⢀⣠⠟⠦⣄⡼⠃⠀⠀⢨⣍⣩⡟⠁" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠿⣞⢉⡥⠀⠀⠀⠈⠉⠀⠀⠀⠀⠀⠀⠀⠀⢲⣴⡏⠙⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⢛⣴⣃⡀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠤⠖⢹⠁⠉⠁⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⠀⠋⢀⡏⠉⠉⠑⠒⠒⠉⠉⠉⠁⠀⠀⠀⢸⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⠀⢠⡾⠉⠀⠀⠀⢀⡞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⠀⠀⢰⠏⠀⠀⠀⠀⢠⠞⠀⡀⠀⠀⠀⠀⠤⢤⡤⠤⠀⠀⠀⠀⣸⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠀⠀⣀⣤⡟⠀⠀⣀⡤⠞⠁⠀⠸⡇⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⡿⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⢀⣴⠞⠋⢠⡟⠒⠋⠁⠀⠀⠀⠀⠀⢷⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⢰⡇⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⢠⡾⠁⠀⢠⡼⣇⠀⠀⠀⠀⣀⡤⠤⢤⣘⣇⣀⠤⠤⢤⣸⣄⡤⠤⠤⣀⡿⠀⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⢸⡇⠀⠀⠻⠤⠼⠧⠤⠤⠼⢧⣠⡀⡄⠈⡟⠀⣤⢠⡄⢸⡁⣠⠀⣆⡈⣳⠀⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠻⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⣹⡗⠛⠒⠛⠒⠛⠛⠓⠛⠓⠛⠚⠛⠛⠋⠀⠀⠀⠀⠀" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "⠀⠀⠉⠛⠒⠶⠶⠶⠶⠶⠶⠾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
    }
    
    if (AsciiArt == 5) {
	    std::cout << "                                                   ████   ███                       █████   " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "                                                  ░░███  ░░░                       ░░███    " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << " █████████  ██████   ████████              ██████  ░███  ████   ██████  ████████   ███████  " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "░█░░░░███  ░░░░░███ ░░███░░███ ██████████ ███░░███ ░███ ░░███  ███░░███░░███░░███ ░░░███░   " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "░   ███░    ███████  ░███ ░███░░░░░░░░░░ ░███ ░░░  ░███  ░███ ░███████  ░███ ░███   ░███    " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "  ███░   █ ███░░███  ░███ ░███           ░███  ███ ░███  ░███ ░███░░░   ░███ ░███   ░███ ███" << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << " █████████░░████████ ░███████            ░░██████  █████ █████░░██████  ████ █████  ░░█████ " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "░░░░░░░░░  ░░░░░░░░  ░███░░░              ░░░░░░  ░░░░░ ░░░░░  ░░░░░░  ░░░░ ░░░░░    ░░░░░  " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "                     ░███                                                                   " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "                     █████                                                                  " << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(AsciiArtSpeed));
	    std::cout << "                    ░░░░░                                                                   " << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "zap client - ver 0.2" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "For Game Version v3.0.55.37" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

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
            
        GlowESP->Initialize();
        
        std::cout << "core initialized" << std::endl;
        std::cout << "-----------------------------" << std::endl;

        LoadConfig();
        LoadOverlaySave();
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
