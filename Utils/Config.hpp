#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "IniReader.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputTypes.hpp"

constexpr char ConfigFile[] = "config.ini";

#define WriteSection(key) \
    conf << "[" #key "]" << "\n";
#define WritePair(section, key) \
    conf << #key " = " << Config::section::key << "\n";
#define WriteSectionEnd() conf << "\n";
#define WriteComment(msg) conf << "; " << msg << '\n';

#define ReadBool(section, key) \
    Config::section::key = reader.GetBoolean(#section, #key, Config::section::key);
#define ReadFloat(section, key) \
    Config::section::key = reader.GetFloat(#section, #key, Config::section::key);
#define ReadInt(section, key) \
    Config::section::key = reader.GetInteger(#section, #key, Config::section::key);

namespace Config {
    namespace Aimbot {
        bool Enabled = true;
        int AimBind = 56;
        int ExtraBind = 57;
        int HitBox = 2;
        
        bool VisibilityCheck = true;
        
        bool PredictMovement = true;
        bool PredictBulletDrop = true;
        bool RecoilControl = false;
        float Speed = 20;
        float Smooth = 0.9;
        float FOV = 10;
        float ZoomScale = 3.0;
        float MinDistance = 1;
        float HipfireDistance = 200;
        float ZoomDistance = 200;
        float PitchPower = 1;
        float YawPower = 1;
        
        //Weapons
	//Light
	bool P2020 = true;
	bool RE45 = true;
	bool Alternator = true;
	bool R99 = true;
	bool R301 = true;
	bool Spitfire = true;
	bool G7 = true; 
	//Heavy
	bool Flatline = true;
	bool Hemlock = true;
	bool Repeater = true;
	bool Rampage = true;
	bool CARSMG = true;  
	//Energy
	bool Havoc = true;
	bool Devotion = true;
	bool LSTAR = true;
	bool TripleTake = true;
	bool Volt = true;
	bool Nemesis = true;
	//Shotgun
	bool Mozambique = true;
	bool EVA8 = true;
	bool Peacekeeper = true;
	bool Mastiff = true;   
	//Snipers
	bool Longbow = true;
	bool ChargeRifle = true;
	bool Sentinel = true;    
	//Legendary
	bool Wingman = true; //Emotional damage!
	bool Prowler = true;
	bool Bocek = true;
	bool Kraber = true;
	bool Knife = true;
    };

    namespace Sense {
    bool GlowEnabled = false;
    float GlowMaxDistance = 200;

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
    };

    namespace Triggerbot {
        bool Enabled = true;
        bool AlwaysOn = false;
        int TriggerBind = 57;
        float Range = 200;
        
        //Weapons
	//Light
	bool P2020 = false;
	bool RE45 = false;
	bool Alternator = false;
	bool R99 = false;
	bool R301 = false;
	bool Spitfire = false;
	bool G7 = false; 
	//Heavy
	bool Flatline = false;
	bool Hemlock = false;
	bool Repeater = false;
	bool Rampage = false;
	bool CARSMG = false;  
	//Energy
	bool Havoc = false;
	bool Devotion = false;
	bool LSTAR = false;
	bool TripleTake = false;
	bool Volt = false;
	bool Nemesis = false;
	//Shotgun
	bool Mozambique = false;
	bool EVA8 = false;
	bool Peacekeeper = false;
	bool Mastiff = false;   
	//Snipers
	bool Longbow = false;
	bool ChargeRifle = false;
	bool Sentinel = false;    
	//Legendary
	bool Wingman = false; //Emotional damage!
	bool Prowler = false;
	bool Bocek = false;
	bool Kraber = false;
	bool Knife = false;
    };
    
    namespace Misc {
        bool Superglide = false;
	bool TeamGamemode = true;
    };
    
    namespace Menu {
        int Layout = 1;
    };
};

namespace Modules {
    namespace Aimbot {
        bool Enabled = true;
        HitboxType Hitbox = HitboxType::UpperChest;
        InputKeyType AimBind = InputKeyType::MOUSE_Left;
	InputKeyType ExtraBind = InputKeyType::MOUSE_Right;
        
        bool VisibilityCheck = true;
        bool TeamCheck = false;
        
        bool PredictMovement = true;
        bool PredictBulletDrop = true;
        bool RecoilControl = true;
        float Speed = 20;
        float Smooth = 0.9;
        float FOV = 10;
        float ZoomScale = 3.0;
        float MinDistance = 1;
        float HipfireDistance = 200;
        float ZoomDistance = 200;
        float PitchPower = 4;
        float YawPower = 4;
    };

    namespace Sense {
        //Glow
        bool Enabled = false;
        bool ItemGlow = true;
        float MaxDistance = 200;
        
        //Drawings
        bool DrawBox = true;
        float BoxThickness = 2;

        bool DrawTracers = true;
        int TracerPos = 0;
        int TracerBone = 0;
        
        bool Skeleton = true;
        float SkeletonThickness = 1.5f;
        
        bool DrawSeer = true;
        bool ShowNear = true;
        bool DrawNames = true; 
        
        float ESPMaxDistance = 200;
        
        //Misc
        bool ShowSpectators = true;
        
        //FOV
        bool DrawFOVCircle = true;
        float GameFOV = 120;
        
        //Settings
        bool AimedAtOnly = false;
        bool ShowTeam = false;
        bool TeamNames = false;
    };

    namespace Triggerbot {
        bool Enabled = true;
        bool AlwaysOn = false;
        float Range = 200;
        InputKeyType TriggerBind = InputKeyType::MOUSE_Right;
    };
    
    namespace Misc {
        bool Superglide = false;
	bool TeamGamemode = true;
    };
    
    namespace Menu {
        int Layout = 1;
    	
    };
};

void UpdateConfig() {
    std::ofstream conf(ConfigFile);
    if (conf.is_open()) {
        WriteSection(Aimbot);
        WritePair(Aimbot, Enabled);
        WritePair(Aimbot, HitBox);
        WritePair(Aimbot, AimBind);
        WritePair(Aimbot, ExtraBind);
        WritePair(Aimbot, PredictMovement);
        WritePair(Aimbot, PredictBulletDrop);
        WritePair(Aimbot, Speed);
        WritePair(Aimbot, Smooth);
        WritePair(Aimbot, FOV);
        WritePair(Aimbot, ZoomScale);
        WritePair(Aimbot, MinDistance);
        WritePair(Aimbot, HipfireDistance);
        WritePair(Aimbot, ZoomDistance);
        WritePair(Aimbot, RecoilControl);
        WritePair(Aimbot, PitchPower);
        WritePair(Aimbot, YawPower);
        WriteSectionEnd();

        WriteSection(Sense);
        WritePair(Sense, GlowEnabled);
        WritePair(Sense, ItemGlow);
        WritePair(Sense, DrawSeer);
        WritePair(Sense, GlowMaxDistance);
        WritePair(Sense, ShowSpectators);
        WritePair(Sense, DrawFOVCircle);
        WritePair(Sense, GameFOV);
        WritePair(Sense, DrawBox);
        WritePair(Sense, BoxThickness);
        WritePair(Sense, Skeleton);
        WritePair(Sense, SkeletonThickness);
        WritePair(Sense, ESPMaxDistance);
        WritePair(Sense, ShowNear);
        WritePair(Sense, DrawNames);
        WritePair(Sense, TracerPos);
        WritePair(Sense, TracerBone);
        WritePair(Sense, DrawTracers);
        WritePair(Sense, ShowTeam);
        WritePair(Sense, TeamNames);
        WriteSectionEnd();

        WriteSection(Triggerbot);
        WritePair(Triggerbot, Enabled);
        WritePair(Triggerbot, AlwaysOn);
        WritePair(Triggerbot, TriggerBind);
        WritePair(Triggerbot, Range);
        WriteSectionEnd();
        
        WriteSection(Misc);
        WritePair(Misc, TeamGamemode);
        WritePair(Misc, Superglide);
        WriteSectionEnd();
        
        WriteSection(Menu);
        WritePair(Menu, Layout);
        WriteSectionEnd();
        conf.close();
    }
}

bool ReadConfig(const std::string &configFile) {
    INIReader reader(configFile);
    if (reader.ParseError() < 0) {
        UpdateConfig();
        return false;
    }
    
    ReadBool(Aimbot, Enabled);
    ReadInt(Aimbot, HitBox);
    ReadInt(Aimbot, AimBind);
    ReadInt(Aimbot, ExtraBind);
    ReadBool(Aimbot, PredictMovement);
    ReadBool(Aimbot, PredictBulletDrop);
    ReadFloat(Aimbot, Speed);
    ReadFloat(Aimbot, Smooth);
    ReadFloat(Aimbot, FOV);
    ReadFloat(Aimbot, ZoomScale);
    ReadFloat(Aimbot, MinDistance);
    ReadFloat(Aimbot, HipfireDistance);
    ReadFloat(Aimbot, ZoomDistance);

    ReadBool(Sense, GlowEnabled);
    ReadBool(Sense, ItemGlow);
    ReadBool(Sense, DrawSeer);
    ReadFloat(Sense, GlowMaxDistance);
    ReadBool(Sense, ShowSpectators);
    ReadBool(Sense, DrawFOVCircle);
    ReadFloat(Sense, GameFOV);
    ReadBool(Sense, DrawBox);
    ReadFloat(Sense, BoxThickness);
    ReadBool(Sense, Skeleton);
    ReadFloat(Sense, SkeletonThickness);
    ReadFloat(Sense, ESPMaxDistance);
    ReadBool(Sense, ShowNear);
    ReadBool(Sense, DrawNames);
    ReadInt(Sense, TracerPos);
    ReadInt(Sense, TracerBone);
    ReadBool(Sense, DrawTracers);
    ReadBool(Sense, ShowTeam);
    ReadBool(Sense, TeamNames);

    ReadBool(Triggerbot, Enabled);
    ReadBool(Triggerbot, AlwaysOn);
    ReadFloat(Triggerbot, Range);
    ReadInt(Triggerbot, TriggerBind);

    ReadBool(Aimbot, RecoilControl);
    ReadFloat(Aimbot, PitchPower);
    ReadFloat(Aimbot, YawPower);
    
    ReadBool(Misc, TeamGamemode);
    ReadBool(Misc, Superglide);

    ReadInt(Menu, Layout);

    UpdateConfig();
    return true;
}
