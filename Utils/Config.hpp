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
        //int AimBind = 56;
        //int ExtraBind = 57;
        int HitBox = 2;
        
        bool OnFire = true;
        bool OnADS = true;
             
        bool PredictMovement = true;
        bool PredictBulletDrop = true;
        float Speed = 20;
        float Smooth = 0.9;
        int Delay = 10;
        float FOV = 10;
        float ZoomScale = 3.0;
        float MinDistance = 1;
        float HipfireDistance = 200;
        float ZoomDistance = 200;
        
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
    
    namespace RCS {
        bool RCSEnabled = true;
        bool OnADS = true;
        float PitchPower = 4;
        float YawPower = 4;
        
        //Weapons
	//Light
	bool P2020 = false;
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
	bool Kraber = false;
    };

    namespace Sense {
    bool GlowEnabled = false;
    float GlowMaxDistance = 200;

    bool ItemGlow = true;
    
    //Drawings
    bool VisibilityCheck = false;
    bool DrawBox = true;
    bool DrawFilledBox = false;
    float BoxThickness = 1.0;
    bool Skeleton = true;
    float SkeletonThickness = 1.0;
    float ESPMaxDistance = 200;
    bool ShowNear = true;
    bool DrawSeer = true;
    bool DrawStatus = true;
    bool ShowMaxStatusValues = true;
    bool DrawDistance = false;
    bool DrawFOVCircle = true;
    bool DrawFilledFOVCircle = false;
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
    ImVec4 InvisibleFilledBoxColor = ImColor(0, 0, 0, 30);
    ImVec4 VisibleFilledBoxColor = ImColor(0, 0, 0, 30);
    ImVec4 InvisibleTracerColor = ImColor(255, 0, 0, 255);
    ImVec4 VisibleTracerColor = ImColor(0, 255, 0, 255);
    ImVec4 InvisibleSkeletonColor = ImColor(255, 255, 255, 255);
    ImVec4 VisibleSkeletonColor = ImColor(255, 255, 255, 255);
    ImVec4 InvisibleNameColor = ImColor(255, 255, 255, 255);
    ImVec4 VisibleNameColor = ImColor(255, 255, 255, 255);
    ImVec4 InvisibleDistanceColor = ImColor(255, 255, 255, 255);
    ImVec4 VisibleDistanceColor = ImColor(255, 255, 255, 255);
    ImVec4 FOVColor = ImColor(255, 255, 255, 255);
    ImVec4 FilledFOVColor = ImColor(0, 0, 0, 20);
    ImVec4 NearColor = ImColor(255, 255, 255, 255);
    ImVec4 TeamColor = ImColor(0, 255, 255, 255);
    ImVec4 TeamNameColor = ImColor(255, 255, 255, 255);
    ImVec4 CrosshairColor = ImColor(255, 255, 255, 255);
    };

    namespace Triggerbot {
        bool Enabled = true;
        bool OnADS = false;
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
        //InputKeyType AimBind = InputKeyType::MOUSE_Left;
	//InputKeyType ExtraBind = InputKeyType::MOUSE_Right;
        
        bool OnFire = true;
        bool OnADS = true;
        
        bool PredictMovement = true;
        bool PredictBulletDrop = true;
        float Speed = 20;
        float Smooth = 0.9;
        float FOV = 10;
        float ZoomScale = 3.0;
        float MinDistance = 1;
        float HipfireDistance = 200;
        float ZoomDistance = 200;
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
        bool OnADS = false;
        float Range = 200;
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
        WritePair(Aimbot, OnFire);
        WritePair(Aimbot, OnADS);
        WritePair(Aimbot, PredictMovement);
        WritePair(Aimbot, PredictBulletDrop);
        WritePair(Aimbot, Speed);
        WritePair(Aimbot, Smooth);
        WritePair(Aimbot, Delay);
        WritePair(Aimbot, FOV);
        WritePair(Aimbot, ZoomScale);
        WritePair(Aimbot, MinDistance);
        WritePair(Aimbot, HipfireDistance);
        WritePair(Aimbot, ZoomDistance);
        //Weapons
	//Light
	WritePair(Aimbot, P2020);
	WritePair(Aimbot, RE45);
	WritePair(Aimbot, Alternator);
	WritePair(Aimbot, R99);
	WritePair(Aimbot, R301);
	WritePair(Aimbot, Spitfire);
	WritePair(Aimbot, G7); 
	//Heavy
	WritePair(Aimbot, Flatline);
	WritePair(Aimbot, Hemlock);
	WritePair(Aimbot, Repeater);
	WritePair(Aimbot, Rampage);
	WritePair(Aimbot, CARSMG);  
	//Energy
	WritePair(Aimbot, Havoc);
	WritePair(Aimbot, Devotion);
	WritePair(Aimbot, LSTAR);
	WritePair(Aimbot, TripleTake);
	WritePair(Aimbot, Volt);
	WritePair(Aimbot, Nemesis);
	//Shotgun
	WritePair(Aimbot, Mozambique);
	WritePair(Aimbot, EVA8);
	WritePair(Aimbot, Peacekeeper);
	WritePair(Aimbot, Mastiff);   
	//Snipers
	WritePair(Aimbot, Longbow);
	WritePair(Aimbot, ChargeRifle);
	WritePair(Aimbot, Sentinel);    
	//Legendary
	WritePair(Aimbot, Wingman); //Emotional damage!
	WritePair(Aimbot, Prowler);
	WritePair(Aimbot, Bocek);
	WritePair(Aimbot, Kraber);
	WritePair(Aimbot, Knife);
        
        WriteSection(RCS);
        WritePair(RCS, RCSEnabled);
        WritePair(RCS, OnADS);
	WritePair(RCS, PitchPower);
        WritePair(RCS, YawPower);
        //Weapons
	//Light
	WritePair(RCS, P2020);
	WritePair(RCS, RE45);
	WritePair(RCS, Alternator);
	WritePair(RCS, R99);
	WritePair(RCS, R301);
	WritePair(RCS, Spitfire);
	WritePair(RCS, G7); 
	//Heavy
	WritePair(RCS, Flatline);
	WritePair(RCS, Hemlock);
	WritePair(RCS, Repeater);
	WritePair(RCS, Rampage);
	WritePair(RCS, CARSMG);  
	//Energy
	WritePair(RCS, Havoc);
	WritePair(RCS, Devotion);
	WritePair(RCS, LSTAR);
	WritePair(RCS, TripleTake);
	WritePair(RCS, Volt);
	WritePair(RCS, Nemesis);
	//Shotgun
	WritePair(RCS, Mozambique);
	WritePair(RCS, EVA8);
	WritePair(RCS, Peacekeeper);
	WritePair(RCS, Mastiff);   
	//Snipers
	WritePair(RCS, Longbow);
	WritePair(RCS, ChargeRifle);
	WritePair(RCS, Sentinel);    
	//Legendary
	WritePair(RCS, Wingman); //Emotional damage!
	WritePair(RCS, Prowler);
	WritePair(RCS, Kraber);
        WriteSectionEnd();

        WriteSection(Sense);
        WritePair(Sense, GlowEnabled);
        WritePair(Sense, ItemGlow);
        WritePair(Sense, DrawSeer);
        WritePair(Sense, DrawDistance);
        WritePair(Sense, DrawStatus);
        WritePair(Sense, ShowMaxStatusValues);
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
        WritePair(Triggerbot, OnADS);
        WritePair(Triggerbot, Range);
        //Weapons
	//Light
	WritePair(Triggerbot, P2020);
	WritePair(Triggerbot, RE45);
	WritePair(Triggerbot, Alternator);
	WritePair(Triggerbot, R99);
	WritePair(Triggerbot, R301);
	WritePair(Triggerbot, Spitfire);
	WritePair(Triggerbot, G7); 
	//Heavy
	WritePair(Triggerbot, Flatline);
	WritePair(Triggerbot, Hemlock);
	WritePair(Triggerbot, Repeater);
	WritePair(Triggerbot, Rampage);
	WritePair(Triggerbot, CARSMG);  
	//Energy
	WritePair(Triggerbot, Havoc);
	WritePair(Triggerbot, Devotion);
	WritePair(Triggerbot, LSTAR);
	WritePair(Triggerbot, TripleTake);
	WritePair(Triggerbot, Volt);
	WritePair(Triggerbot, Nemesis);
	//Shotgun
	WritePair(Triggerbot, Mozambique);
	WritePair(Triggerbot, EVA8);
	WritePair(Triggerbot, Peacekeeper);
	WritePair(Triggerbot, Mastiff);   
	//Snipers
	WritePair(Triggerbot, Longbow);
	WritePair(Triggerbot, ChargeRifle);
	WritePair(Triggerbot, Sentinel);    
	//Legendary
	WritePair(Triggerbot, Wingman); //Emotional damage!
	WritePair(Triggerbot, Prowler);
	WritePair(Triggerbot, Bocek);
	WritePair(Triggerbot, Kraber);
	WritePair(Triggerbot, Knife);
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
    ReadBool(Aimbot, OnFire);
    ReadBool(Aimbot, OnADS);
    ReadBool(Aimbot, PredictMovement);
    ReadBool(Aimbot, PredictBulletDrop);
    ReadFloat(Aimbot, Speed);
    ReadFloat(Aimbot, Smooth);
    ReadInt(Aimbot, Delay);
    ReadFloat(Aimbot, FOV);
    ReadFloat(Aimbot, ZoomScale);
    ReadFloat(Aimbot, MinDistance);
    ReadFloat(Aimbot, HipfireDistance);
    ReadFloat(Aimbot, ZoomDistance);
        //Weapons
	//Light
	ReadBool(Aimbot, P2020);
	ReadBool(Aimbot, RE45);
	ReadBool(Aimbot, Alternator);
	ReadBool(Aimbot, R99);
	ReadBool(Aimbot, R301);
	ReadBool(Aimbot, Spitfire);
	ReadBool(Aimbot, G7); 
	//Heavy
	ReadBool(Aimbot, Flatline);
	ReadBool(Aimbot, Hemlock);
	ReadBool(Aimbot, Repeater);
	ReadBool(Aimbot, Rampage);
	ReadBool(Aimbot, CARSMG);  
	//Energy
	ReadBool(Aimbot, Havoc);
	ReadBool(Aimbot, Devotion);
	ReadBool(Aimbot, LSTAR);
	ReadBool(Aimbot, TripleTake);
	ReadBool(Aimbot, Volt);
	ReadBool(Aimbot, Nemesis);
	//Shotgun
	ReadBool(Aimbot, Mozambique);
	ReadBool(Aimbot, EVA8);
	ReadBool(Aimbot, Peacekeeper);
	ReadBool(Aimbot, Mastiff);   
	//Snipers
	ReadBool(Aimbot, Longbow);
	ReadBool(Aimbot, ChargeRifle);
	ReadBool(Aimbot, Sentinel);    
	//Legendary
	ReadBool(Aimbot, Wingman); //Emotional damage!
	ReadBool(Aimbot, Prowler);
	ReadBool(Aimbot, Bocek);
	ReadBool(Aimbot, Kraber);
	ReadBool(Aimbot, Knife);
    
    ReadBool(RCS, RCSEnabled);
    ReadBool(RCS, OnADS);
    ReadFloat(RCS, PitchPower);
    ReadFloat(RCS, YawPower);
        //Weapons
	//Light
	ReadBool(RCS, P2020);
	ReadBool(RCS, RE45);
	ReadBool(RCS, Alternator);
	ReadBool(RCS, R99);
	ReadBool(RCS, R301);
	ReadBool(RCS, Spitfire);
	ReadBool(RCS, G7); 
	//Heavy
	ReadBool(RCS, Flatline);
	ReadBool(RCS, Hemlock);
	ReadBool(RCS, Repeater);
	ReadBool(RCS, Rampage);
	ReadBool(RCS, CARSMG);  
	//Energy
	ReadBool(RCS, Havoc);
	ReadBool(RCS, Devotion);
	ReadBool(RCS, LSTAR);
	ReadBool(RCS, TripleTake);
	ReadBool(RCS, Volt);
	ReadBool(RCS, Nemesis);
	//Shotgun
	ReadBool(RCS, Mozambique);
	ReadBool(RCS, EVA8);
	ReadBool(RCS, Peacekeeper);
	ReadBool(RCS, Mastiff);   
	//Snipers
	ReadBool(RCS, Longbow);
	ReadBool(RCS, ChargeRifle);
	ReadBool(RCS, Sentinel);    
	//Legendary
	ReadBool(RCS, Wingman); //Emotional damage!
	ReadBool(RCS, Prowler);
	ReadBool(RCS, Kraber);

    ReadBool(Sense, GlowEnabled);
    ReadBool(Sense, ItemGlow);
    ReadBool(Sense, DrawSeer);
    ReadBool(Sense, DrawStatus);
    ReadBool(Sense, ShowMaxStatusValues);
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
    ReadBool(Sense, DrawDistance);
    ReadInt(Sense, TracerPos);
    ReadInt(Sense, TracerBone);
    ReadBool(Sense, DrawTracers);
    ReadBool(Sense, ShowTeam);
    ReadBool(Sense, TeamNames);

    ReadBool(Triggerbot, Enabled);
    ReadFloat(Triggerbot, Range);
    ReadBool(Triggerbot, OnADS);
        //Weapons
	//Light
	ReadBool(Triggerbot, P2020);
	ReadBool(Triggerbot, RE45);
	ReadBool(Triggerbot, Alternator);
	ReadBool(Triggerbot, R99);
	ReadBool(Triggerbot, R301);
	ReadBool(Triggerbot, Spitfire);
	ReadBool(Triggerbot, G7); 
	//Heavy
	ReadBool(Triggerbot, Flatline);
	ReadBool(Triggerbot, Hemlock);
	ReadBool(Triggerbot, Repeater);
	ReadBool(Triggerbot, Rampage);
	ReadBool(Triggerbot, CARSMG);  
	//Energy
	ReadBool(Triggerbot, Havoc);
	ReadBool(Triggerbot, Devotion);
	ReadBool(Triggerbot, LSTAR);
	ReadBool(Triggerbot, TripleTake);
	ReadBool(Triggerbot, Volt);
	ReadBool(Triggerbot, Nemesis);
	//Shotgun
	ReadBool(Triggerbot, Mozambique);
	ReadBool(Triggerbot, EVA8);
	ReadBool(Triggerbot, Peacekeeper);
	ReadBool(Triggerbot, Mastiff);   
	//Snipers
	ReadBool(Triggerbot, Longbow);
	ReadBool(Triggerbot, ChargeRifle);
	ReadBool(Triggerbot, Sentinel);    
	//Legendary
	ReadBool(Triggerbot, Wingman); //Emotional damage!
	ReadBool(Triggerbot, Prowler);
	ReadBool(Triggerbot, Bocek);
	ReadBool(Triggerbot, Kraber);
	ReadBool(Triggerbot, Knife);
    
    ReadBool(Misc, TeamGamemode);
    ReadBool(Misc, Superglide);

    ReadInt(Menu, Layout);

    UpdateConfig();
    return true;
}
