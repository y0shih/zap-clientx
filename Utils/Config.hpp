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
        bool ClosestHitbox = false;
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
	bool Wingman = true;
	bool Prowler = true;
	bool Bocek = true;
	bool Kraber = true;
	bool Knife = true;
	
	//---------------Advanced---------------//
	bool AdvancedAim = false;
    
	//Weapons
	//Light
	float P2020Speed = 10;
	float P2020Smooth = 0.9;
	float RE45Speed = 10;
	float RE45Smooth = 0.9;
	float AlternatorSpeed = 10;
	float AlternatorSmooth = 0.9;
	float R99Speed = 10;
	float R99Smooth = 0.9;
	float R301Speed = 10;
	float R301Smooth = 0.9;
	float SpitfireSpeed = 10;
	float SpitfireSmooth = 0.9;
	float G7Speed = 10;
	float G7Smooth = 0.9;
	//Heavy
	float FlatlineSpeed = 10;
	float FlatlineSmooth = 0.9;
	float HemlockSpeed = 10;
	float HemlockSmooth = 0.9;
	float RepeaterSpeed = 10;
	float RepeaterSmooth = 0.9;
	float RampageSpeed = 10;
	float RampageSmooth = 0.9;
	float CARSMGSpeed = 10;
	float CARSMGSmooth = 0.9;
	//Energy
	float HavocSpeed = 10;
	float HavocSmooth = 0.9;
	float DevotionSpeed = 10;
	float DevotionSmooth = 0.9;
	float LSTARSpeed = 10;
	float LSTARSmooth = 0.9;
	float TripleTakeSpeed = 10;
	float TripleTakeSmooth = 0.9;
	float VoltSpeed = 10;
	float VoltSmooth = 0.9;
	float NemesisSpeed = 10;
	float NemesisSmooth = 0.9;
	//Shotguns
	float MozambiqueSpeed = 10;
	float MozambiqueSmooth = 0.9;
	float EVA8Speed = 10;
	float EVA8Smooth = 0.9;
	float PeacekeeperSpeed = 10;
	float PeacekeeperSmooth = 0.9;
	float MastiffSpeed = 10;
	float MastiffSmooth = 0.9;
	//Snipers
	float LongbowSpeed = 10;
	float LongbowSmooth = 0.9;
	float ChargeRifleSpeed = 10;
	float ChargeRifleSmooth = 0.9;
	float SentinelSpeed = 10;
	float SentinelSmooth = 0.9;
	//Legendary
	float WingmanSpeed = 10;
	float WingmanSmooth = 0.9;
	float ProwlerSpeed = 10;
	float ProwlerSmooth = 0.9;
	float BocekSpeed = 10;
	float BocekSmooth = 0.9;
	float KraberSpeed = 10;
	float KraberSmooth = 0.9;
	float ThrowingKnifeSpeed = 10;
	float ThrowingKnifeSmooth = 0.9;
	
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
	
	//---------------Advanced---------------//
	bool AdvancedRCS = false;
	float AdvancedPitchPower = 10;
	float AdvancedYawPower = 10;
    
	//Weapons
	//Light
	float P2020Pitch = 10;
	float P2020Yaw = 10;
	float RE45Pitch = 10;
	float RE45Yaw = 10;
	float AlternatorPitch = 10;
	float AlternatorYaw = 10;
	float R99Pitch = 10;
	float R99Yaw = 10;
	float R301Pitch = 10;
	float R301Yaw = 10;
	float SpitfirePitch = 10;
	float SpitfireYaw = 10;
	float G7Pitch = 10;
	float G7Yaw = 10;
	//Heavy
	float FlatlinePitch = 10;
	float FlatlineYaw = 10;
	float HemlockPitch = 10;
	float HemlockYaw = 10;
	float RepeaterPitch = 10;
	float RepeaterYaw = 10;
	float RampagePitch = 10;
	float RampageYaw = 10;
	float CARSMGPitch = 10;
	float CARSMGYaw = 10;
	//Energy
	float HavocPitch = 10;
	float HavocYaw = 10;
	float DevotionPitch = 10;
	float DevotionYaw = 10;
	float LSTARPitch = 10;
	float LSTARYaw = 10;
	float TripleTakePitch = 10;
	float TripleTakeYaw = 10;
	float VoltPitch = 10;
	float VoltYaw = 10;
	float NemesisPitch = 10;
	float NemesisYaw = 10;
	//Shotguns
	float MozambiquePitch = 10;
	float MozambiqueYaw = 10;
	float EVA8Pitch = 10;
	float EVA8Yaw = 10;
	float PeacekeeperPitch = 10;
	float PeacekeeperYaw = 10;
	float MastiffPitch = 10;
	float MastiffYaw = 10;
	//Snipers
	float LongbowPitch = 10;
	float LongbowYaw = 10;
	float ChargeRiflePitch = 10;
	float ChargeRifleYaw = 10;
	float SentinelPitch = 10;
	float SentinelYaw = 10;
	//Legendary
	float WingmanPitch = 10;
	float WingmanYaw = 10;
	float ProwlerPitch = 10;
	float ProwlerYaw = 10;
	float KraberPitch = 10;
	float KraberYaw = 10;
    };
    
    namespace Glow {
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
        bool ItemGlow = true;
        //Colors
        float InvisibleGlowColor[3] = {1, 0, 0};
        float VisibleGlowColor[3] = {0, 1, 0};
	    
    };

    namespace Sense {
    //Drawings
    bool VisibilityCheck = false;
    bool DrawBox = true;
    bool DrawFilledBox = false;
    float BoxThickness = 1.0;
    bool Skeleton = true;
    float SkeletonThickness = 1.0;
    float ESPMaxDistance = 200;
    bool ShowNear = false;
    bool DrawSeer = false;
    bool DrawStatus = true;
    bool HealthBar = true;
    bool ShieldBar = true;
    bool DrawWeapon = true;
    bool ShowLegend = false;
    bool WeaponColorType = true;
    float BarThickness = 2.0;
    bool ShowMaxStatusValues = true;
    bool DrawDistance = false;
    bool DrawFOVCircle = true;
    bool DrawFilledFOVCircle = false;
    float FOVThickness = 1.0;
    bool DrawNames = false;
    int TracerPos = 0;
    int TracerBone = 0;
    bool DrawTracers = false;
    float TracerThickness = 2.0;
    bool ShowSpectators = true;
    bool DrawCrosshair = true;
    float CrosshairSize = 7.0;
    float CrosshairThickness = 1.0;
    
    //Settings
    float GameFOV = 120;
    bool ShowTeam = false;
    bool TeamNames = false;
    
    //Player Info Positions (0-2 = Top, 3-4 = bottom)
    int LegendPosition = 2;
    int NamePosition = 3;
    int DistancePosition = 4;
    int StatusPosition = 0;
    int WeaponPosition = 1;
        
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
        bool OnADS = true;
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
	bool SkinChanger = false;
	    //Weapon IDs
	    //Light
	    int SkinP2020 = 1;
	    int SkinRE45 = 1;
	    int SkinALTERNATOR = 1;
	    int SkinR99 = 1;
	    int SkinR301 = 1;
	    int SkinSPITFIRE = 1;
	    int SkinG7 = 1;
	    
	    //Heavy
	    int SkinFLATLINE = 1;
	    int SkinHEMLOCK = 1;
	    int SkinREPEATER = 1;
	    int SkinRAMPAGE = 1;
	    int SkinCAR = 1;
	    
	    //Energy
	    int SkinHAVOC = 1;
	    int SkinDEVOTION = 1;
	    int SkinLSTAR = 1;
	    int SkinTRIPLETAKE = 1;
	    int SkinVOLT = 1;
	    int SkinNEMESIS = 1;
	    
	    //Shotgun
	    int SkinMOZAMBIQUE = 1;
	    int SkinEVA8 = 1;
	    int SkinPEACEKEEPER = 1;
	    int SkinMASTIFF = 1;
	    
	    //Snipers
	    int SkinLONGBOW = 1;
	    int SkinCHARGE_RIFLE = 1;
	    int SkinSENTINEL = 1; 
	    
	    //Legendary
	    int SkinWINGMAN = 1;
	    int SkinPROWLER = 1;
	    int SkinBOCEK = 1;
	    int SkinKRABER = 1;
    };
    
    namespace Home {
    	int Layout = 1;
    	bool TeamGamemode = true;
        int AsciiArt = 5; //change the starting ascii art. 0 = cat 1, 1 = shotgun, 2 = glock, 3 = racoon, 4 = cat 2,
        int AsciiArtSpeed = 100; //Speed (in milliseconds) of the ascii art
    	int Style = 5;
    	int Color = 5;
        int MenuX = 754;
        int MenuY = 605;
        bool ErrorLogging = false;
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
};

void UpdateConfig() {
    std::ofstream conf(ConfigFile);
    if (conf.is_open()) {
        WriteSection(Aimbot);
        WritePair(Aimbot, Enabled);
        WritePair(Aimbot, ClosestHitbox);
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
	WritePair(Aimbot, Wingman);
	WritePair(Aimbot, Prowler);
	WritePair(Aimbot, Bocek);
	WritePair(Aimbot, Kraber);
	WritePair(Aimbot, Knife);
	
	//---------------Advanced---------------//
	WritePair(Aimbot, AdvancedAim);
        //Weapons
	//Light
	WritePair(Aimbot, P2020Speed);
	WritePair(Aimbot, P2020Smooth);
	WritePair(Aimbot, RE45Speed);
	WritePair(Aimbot, RE45Smooth);
	WritePair(Aimbot, AlternatorSpeed);
	WritePair(Aimbot, AlternatorSmooth);
	WritePair(Aimbot, R99Speed);
	WritePair(Aimbot, R99Smooth);
	WritePair(Aimbot, R301Speed);
	WritePair(Aimbot, R301Smooth);
	WritePair(Aimbot, SpitfireSpeed);
	WritePair(Aimbot, SpitfireSmooth);
	WritePair(Aimbot, G7Speed); 
	WritePair(Aimbot, G7Smooth);
	//Heavy
	WritePair(Aimbot, FlatlineSpeed);
	WritePair(Aimbot, FlatlineSmooth);
	WritePair(Aimbot, HemlockSpeed);
	WritePair(Aimbot, HemlockSmooth);
	WritePair(Aimbot, RepeaterSpeed);
	WritePair(Aimbot, RepeaterSmooth);
	WritePair(Aimbot, RampageSpeed);
	WritePair(Aimbot, RampageSmooth);
	WritePair(Aimbot, CARSMGSpeed);
	WritePair(Aimbot, CARSMGSmooth);
	//Energy
	WritePair(Aimbot, HavocSpeed);
	WritePair(Aimbot, HavocSmooth);
	WritePair(Aimbot, DevotionSpeed);
	WritePair(Aimbot, DevotionSmooth);
	WritePair(Aimbot, LSTARSpeed);
	WritePair(Aimbot, LSTARSmooth);
	WritePair(Aimbot, TripleTakeSpeed);
	WritePair(Aimbot, TripleTakeSmooth);
	WritePair(Aimbot, VoltSpeed);
	WritePair(Aimbot, VoltSmooth);
	WritePair(Aimbot, NemesisSpeed);
	WritePair(Aimbot, NemesisSmooth);
	//Shotgun
	WritePair(Aimbot, MozambiqueSpeed);
	WritePair(Aimbot, MozambiqueSmooth);
	WritePair(Aimbot, EVA8Speed);
	WritePair(Aimbot, EVA8Smooth);
	WritePair(Aimbot, PeacekeeperSpeed);
	WritePair(Aimbot, PeacekeeperSmooth);
	WritePair(Aimbot, MastiffSpeed);
	WritePair(Aimbot, MastiffSmooth);   
	//Snipers
	WritePair(Aimbot, LongbowSpeed);
	WritePair(Aimbot, LongbowSmooth);
	WritePair(Aimbot, ChargeRifleSpeed);
	WritePair(Aimbot, ChargeRifleSmooth);
	WritePair(Aimbot, SentinelSpeed);    
	WritePair(Aimbot, SentinelSmooth);
	//Legendary
	WritePair(Aimbot, WingmanSpeed);
	WritePair(Aimbot, WingmanSmooth);
	WritePair(Aimbot, ProwlerSpeed);
	WritePair(Aimbot, ProwlerSmooth);
	WritePair(Aimbot, BocekSpeed);
	WritePair(Aimbot, BocekSmooth);
	WritePair(Aimbot, KraberSpeed);
	WritePair(Aimbot, KraberSmooth);
	WritePair(Aimbot, ThrowingKnifeSpeed);
	WritePair(Aimbot, ThrowingKnifeSmooth);
        
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
	
	//---------------Advanced---------------//
	WritePair(RCS, AdvancedRCS);
        //Weapons
	//Light
	WritePair(RCS, P2020Pitch);
	WritePair(RCS, P2020Yaw);
	WritePair(RCS, RE45Pitch);
	WritePair(RCS, RE45Yaw);
	WritePair(RCS, AlternatorPitch);
	WritePair(RCS, AlternatorYaw);
	WritePair(RCS, R99Pitch);
	WritePair(RCS, R99Yaw);
	WritePair(RCS, R301Pitch);
	WritePair(RCS, R301Yaw);
	WritePair(RCS, SpitfirePitch);
	WritePair(RCS, SpitfireYaw);
	WritePair(RCS, G7Pitch); 
	WritePair(RCS, G7Yaw);
	//Heavy
	WritePair(RCS, FlatlinePitch);
	WritePair(RCS, FlatlineYaw);
	WritePair(RCS, HemlockPitch);
	WritePair(RCS, HemlockYaw);
	WritePair(RCS, RepeaterPitch);
	WritePair(RCS, RepeaterYaw);
	WritePair(RCS, RampagePitch);
	WritePair(RCS, RampageYaw);
	WritePair(RCS, CARSMGPitch);
	WritePair(RCS, CARSMGYaw);
	//Energy
	WritePair(RCS, HavocPitch);
	WritePair(RCS, HavocYaw);
	WritePair(RCS, DevotionPitch);
	WritePair(RCS, DevotionYaw);
	WritePair(RCS, LSTARPitch);
	WritePair(RCS, LSTARYaw);
	WritePair(RCS, TripleTakePitch);
	WritePair(RCS, TripleTakeYaw);
	WritePair(RCS, VoltPitch);
	WritePair(RCS, VoltYaw);
	WritePair(RCS, NemesisPitch);
	WritePair(RCS, NemesisYaw);
	//Shotgun
	WritePair(RCS, MozambiquePitch);
	WritePair(RCS, MozambiqueYaw);
	WritePair(RCS, EVA8Pitch);
	WritePair(RCS, EVA8Yaw);
	WritePair(RCS, PeacekeeperPitch);
	WritePair(RCS, PeacekeeperYaw);
	WritePair(RCS, MastiffPitch);
	WritePair(RCS, MastiffYaw);   
	//Snipers
	WritePair(RCS, LongbowPitch);
	WritePair(RCS, LongbowYaw);
	WritePair(RCS, ChargeRiflePitch);
	WritePair(RCS, ChargeRifleYaw);
	WritePair(RCS, SentinelPitch);    
	WritePair(RCS, SentinelYaw);
	//Legendary
	WritePair(RCS, WingmanPitch);
	WritePair(RCS, WingmanYaw);
	WritePair(RCS, ProwlerPitch);
	WritePair(RCS, ProwlerYaw);
	WritePair(RCS, KraberPitch);
	WritePair(RCS, KraberYaw);
        WriteSectionEnd();
        
        WriteSection(Glow);
        WritePair(Glow, GlowEnabled); //
        WritePair(Glow, ItemGlow);
        WritePair(Glow, GlowMaxDistance);
        WritePair(Glow, NewGlow);
        WritePair(Glow, GlowColorMode);
        WritePair(Glow, GlowColorShieldMode);
        WritePair(Glow, GlowRadius);
        WritePair(Glow, InsideFunction);
        WritePair(Glow, OutlineFunction);
        WritePair(Glow, BodyStyle);
        WritePair(Glow, OutlineStyle);
        WritePair(Glow, InvisibleGlowColor[3]);
        WritePair(Glow, VisibleGlowColor[3]);
        
        WriteSection(Sense);
        WritePair(Sense, DrawSeer);
        WritePair(Sense, DrawDistance);
        WritePair(Sense, DrawStatus);
        WritePair(Sense, ShowMaxStatusValues);
        WritePair(Sense, HealthBar);
        WritePair(Sense, ShieldBar);
        WritePair(Sense, DrawWeapon);
        WritePair(Sense, WeaponColorType);
        WritePair(Sense, ShowLegend);
        WritePair(Sense, BarThickness);
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
        //WritePair(Misc, Superglide);
        WritePair(Misc, SkinChanger);
        //Weapons
	//Light
	WritePair(Misc, SkinP2020);
	WritePair(Misc, SkinRE45);
	WritePair(Misc, SkinALTERNATOR);
	WritePair(Misc, SkinR99);
	WritePair(Misc, SkinR301);
	WritePair(Misc, SkinSPITFIRE);
	WritePair(Misc, SkinG7);
	//Heavy
	WritePair(Misc, SkinFLATLINE);
	WritePair(Misc, SkinHEMLOCK);
	WritePair(Misc, SkinREPEATER);
	WritePair(Misc, SkinRAMPAGE);
	WritePair(Misc, SkinCAR);
	//Energy
	WritePair(Misc, SkinHAVOC);
	WritePair(Misc, SkinDEVOTION);
	WritePair(Misc, SkinLSTAR);
	WritePair(Misc, SkinTRIPLETAKE);
	WritePair(Misc, SkinVOLT);
	WritePair(Misc, SkinNEMESIS);
	//Shotgun
	WritePair(Misc, SkinMOZAMBIQUE);
	WritePair(Misc, SkinEVA8);
	WritePair(Misc, SkinPEACEKEEPER);
	WritePair(Misc, SkinMASTIFF);
	//Snipers
	WritePair(Misc, SkinLONGBOW);
	WritePair(Misc, SkinCHARGE_RIFLE);
	WritePair(Misc, SkinSENTINEL);
	//Legendary
	WritePair(Misc, SkinWINGMAN);
	WritePair(Misc, SkinPROWLER);
	WritePair(Misc, SkinKRABER);
	WritePair(Misc, SkinBOCEK);
        WriteSectionEnd();
        
        WriteSection(Home);
        WritePair(Home, AsciiArt);
        WritePair(Home, AsciiArtSpeed);
        WritePair(Home, TeamGamemode);
        WritePair(Home, MenuX);
        WritePair(Home, MenuY);
        WritePair(Home, Style);
        WritePair(Home, Color);
        WritePair(Home, ErrorLogging);
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
    ReadBool(Aimbot, ClosestHitbox);
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
	
	//---------------Advanced---------------//
	ReadBool(Aimbot, AdvancedAim);
        //Weapons
	//Light
	ReadFloat(Aimbot, P2020Speed);
	ReadFloat(Aimbot, P2020Smooth);
	ReadFloat(Aimbot, RE45Speed);
	ReadFloat(Aimbot, RE45Smooth);
	ReadFloat(Aimbot, AlternatorSpeed);
	ReadFloat(Aimbot, AlternatorSmooth);
	ReadFloat(Aimbot, R99Speed);
	ReadFloat(Aimbot, R99Smooth);
	ReadFloat(Aimbot, R301Speed);
	ReadFloat(Aimbot, R301Smooth);
	ReadFloat(Aimbot, SpitfireSpeed);
	ReadFloat(Aimbot, SpitfireSmooth);
	ReadFloat(Aimbot, G7Speed); 
	ReadFloat(Aimbot, G7Smooth);
	//Heavy
	ReadFloat(Aimbot, FlatlineSpeed);
	ReadFloat(Aimbot, FlatlineSmooth);
	ReadFloat(Aimbot, HemlockSpeed);
	ReadFloat(Aimbot, HemlockSmooth);
	ReadFloat(Aimbot, RepeaterSpeed);
	ReadFloat(Aimbot, RepeaterSmooth);
	ReadFloat(Aimbot, RampageSpeed);
	ReadFloat(Aimbot, RampageSmooth);
	ReadFloat(Aimbot, CARSMGSpeed);
	ReadFloat(Aimbot, CARSMGSmooth);
	//Energy
	ReadFloat(Aimbot, HavocSpeed);
	ReadFloat(Aimbot, HavocSmooth);
	ReadFloat(Aimbot, DevotionSpeed);
	ReadFloat(Aimbot, DevotionSmooth);
	ReadFloat(Aimbot, LSTARSpeed);
	ReadFloat(Aimbot, LSTARSmooth);
	ReadFloat(Aimbot, TripleTakeSpeed);
	ReadFloat(Aimbot, TripleTakeSmooth);
	ReadFloat(Aimbot, VoltSpeed);
	ReadFloat(Aimbot, VoltSmooth);
	ReadFloat(Aimbot, NemesisSpeed);
	ReadFloat(Aimbot, NemesisSmooth);
	//Shotgun
	ReadFloat(Aimbot, MozambiqueSpeed);
	ReadFloat(Aimbot, MozambiqueSmooth);
	ReadFloat(Aimbot, EVA8Speed);
	ReadFloat(Aimbot, EVA8Smooth);
	ReadFloat(Aimbot, PeacekeeperSpeed);
	ReadFloat(Aimbot, PeacekeeperSmooth);
	ReadFloat(Aimbot, MastiffSpeed);
	ReadFloat(Aimbot, MastiffSmooth);   
	//Snipers
	ReadFloat(Aimbot, LongbowSpeed);
	ReadFloat(Aimbot, LongbowSmooth);
	ReadFloat(Aimbot, ChargeRifleSpeed);
	ReadFloat(Aimbot, ChargeRifleSmooth);
	ReadFloat(Aimbot, SentinelSpeed);    
	ReadFloat(Aimbot, SentinelSmooth);
	//Legendary
	ReadFloat(Aimbot, WingmanSpeed);
	ReadFloat(Aimbot, WingmanSmooth);
	ReadFloat(Aimbot, ProwlerSpeed);
	ReadFloat(Aimbot, ProwlerSmooth);
	ReadFloat(Aimbot, BocekSpeed);
	ReadFloat(Aimbot, BocekSmooth);
	ReadFloat(Aimbot, KraberSpeed);
	ReadFloat(Aimbot, KraberSmooth);
	ReadFloat(Aimbot, ThrowingKnifeSpeed);
	ReadFloat(Aimbot, ThrowingKnifeSmooth);
    
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
	
	//---------------Advanced---------------//
	ReadBool(RCS, AdvancedRCS);
        //Weapons
	//Light
	ReadFloat(RCS, P2020Pitch);
	ReadFloat(RCS, P2020Yaw);
	ReadFloat(RCS, RE45Pitch);
	ReadFloat(RCS, RE45Yaw);
	ReadFloat(RCS, AlternatorPitch);
	ReadFloat(RCS, AlternatorYaw);
	ReadFloat(RCS, R99Pitch);
	ReadFloat(RCS, R99Yaw);
	ReadFloat(RCS, R301Pitch);
	ReadFloat(RCS, R301Yaw);
	ReadFloat(RCS, SpitfirePitch);
	ReadFloat(RCS, SpitfireYaw);
	ReadFloat(RCS, G7Pitch); 
	ReadFloat(RCS, G7Yaw);
	//Heavy
	ReadFloat(RCS, FlatlinePitch);
	ReadFloat(RCS, FlatlineYaw);
	ReadFloat(RCS, HemlockPitch);
	ReadFloat(RCS, HemlockYaw);
	ReadFloat(RCS, RepeaterPitch);
	ReadFloat(RCS, RepeaterYaw);
	ReadFloat(RCS, RampagePitch);
	ReadFloat(RCS, RampageYaw);
	ReadFloat(RCS, CARSMGPitch);
	ReadFloat(RCS, CARSMGYaw);
	//Energy
	ReadFloat(RCS, HavocPitch);
	ReadFloat(RCS, HavocYaw);
	ReadFloat(RCS, DevotionPitch);
	ReadFloat(RCS, DevotionYaw);
	ReadFloat(RCS, LSTARPitch);
	ReadFloat(RCS, LSTARYaw);
	ReadFloat(RCS, TripleTakePitch);
	ReadFloat(RCS, TripleTakeYaw);
	ReadFloat(RCS, VoltPitch);
	ReadFloat(RCS, VoltYaw);
	ReadFloat(RCS, NemesisPitch);
	ReadFloat(RCS, NemesisYaw);
	//Shotgun
	ReadFloat(RCS, MozambiquePitch);
	ReadFloat(RCS, MozambiqueYaw);
	ReadFloat(RCS, EVA8Pitch);
	ReadFloat(RCS, EVA8Yaw);
	ReadFloat(RCS, PeacekeeperPitch);
	ReadFloat(RCS, PeacekeeperYaw);
	ReadFloat(RCS, MastiffPitch);
	ReadFloat(RCS, MastiffYaw);   
	//Snipers
	ReadFloat(RCS, LongbowPitch);
	ReadFloat(RCS, LongbowYaw);
	ReadFloat(RCS, ChargeRiflePitch);
	ReadFloat(RCS, ChargeRifleYaw);
	ReadFloat(RCS, SentinelPitch);    
	ReadFloat(RCS, SentinelYaw);
	//Legendary
	ReadFloat(RCS, WingmanPitch);
	ReadFloat(RCS, WingmanYaw);
	ReadFloat(RCS, ProwlerPitch);
	ReadFloat(RCS, ProwlerYaw);
	ReadFloat(RCS, KraberPitch);
	ReadFloat(RCS, KraberYaw);
	
    ReadBool(Glow, GlowEnabled);
    ReadBool(Glow, ItemGlow);
    ReadFloat(Glow, GlowMaxDistance);
    ReadBool(Glow, NewGlow);
    ReadInt(Glow, GlowColorMode);
    ReadInt(Glow, GlowColorShieldMode);
    ReadInt(Glow, GlowRadius);
    ReadInt(Glow, InsideFunction);
    ReadInt(Glow, OutlineFunction);
    ReadInt(Glow, BodyStyle);
    ReadInt(Glow, OutlineStyle);
    ReadFloat(Glow, InvisibleGlowColor[3]);
    ReadFloat(Glow, VisibleGlowColor[3]);

    ReadBool(Sense, DrawSeer);
    ReadBool(Sense, DrawStatus);
    ReadBool(Sense, ShowMaxStatusValues);
    ReadBool(Sense, HealthBar);
    ReadBool(Sense, ShieldBar);
    ReadFloat(Sense, BarThickness);
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
    ReadBool(Sense, DrawWeapon);
    ReadBool(Sense, ShowLegend);
    ReadBool(Sense, WeaponColorType);
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
    
    //ReadBool(Misc, Superglide);
    ReadBool(Misc, SkinChanger);
	//Weapons
	//Light
	ReadInt(Misc, SkinP2020);
	ReadInt(Misc, SkinRE45);
	ReadInt(Misc, SkinALTERNATOR);
	ReadInt(Misc, SkinR99);
	ReadInt(Misc, SkinR301);
	ReadInt(Misc, SkinSPITFIRE);
	ReadInt(Misc, SkinG7);
	//Heavy
	ReadInt(Misc, SkinFLATLINE);
	ReadInt(Misc, SkinHEMLOCK);
	ReadInt(Misc, SkinREPEATER);
	ReadInt(Misc, SkinRAMPAGE);
	ReadInt(Misc, SkinCAR);
	//Energy
	ReadInt(Misc, SkinHAVOC);
	ReadInt(Misc, SkinDEVOTION);
	ReadInt(Misc, SkinLSTAR);
	ReadInt(Misc, SkinTRIPLETAKE);
	ReadInt(Misc, SkinVOLT);
	ReadInt(Misc, SkinNEMESIS);
	//Shotgun
	ReadInt(Misc, SkinMOZAMBIQUE);
	ReadInt(Misc, SkinEVA8);
	ReadInt(Misc, SkinPEACEKEEPER);
	ReadInt(Misc, SkinMASTIFF);
	//Snipers
	ReadInt(Misc, SkinLONGBOW);
	ReadInt(Misc, SkinCHARGE_RIFLE);
	ReadInt(Misc, SkinSENTINEL);
	//Legendary
	ReadInt(Misc, SkinWINGMAN);
	ReadInt(Misc, SkinPROWLER);
	ReadInt(Misc, SkinKRABER);
	ReadInt(Misc, SkinBOCEK);
    
    ReadInt(Home, AsciiArt);
    ReadInt(Home, AsciiArtSpeed);
    ReadBool(Home, TeamGamemode);
    ReadInt(Home, MenuX);
    ReadInt(Home, MenuY);
    ReadInt(Home, Style);
    ReadInt(Home, Color);
    ReadBool(Home, ErrorLogging);

    UpdateConfig();
    return true;
}
