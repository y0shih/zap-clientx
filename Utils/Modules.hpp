#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputTypes.hpp"


namespace Modules {
    namespace Home {
    	bool TeamGamemode = true;
        int MenuX = 1050;
        int MenuY = 655;
        bool IsMenuOpened = true;
    };
    
    namespace Aimbot {
        bool Enabled = true;
        HitboxType Hitbox = HitboxType::UpperChest;
        int BindMethod = 0;
        InputKeyType AimBind = InputKeyType::MOUSE_Left;
        InputKeyType ExtraBind = InputKeyType::MOUSE_Right;
        
        bool PredictMovement = true;
        bool PredictBulletDrop = true;
        float Speed = 20;
        float Smooth = 0.9;
        float FOV = 10;
        float ZoomScale = 3.0;
        float MinDistance = 1;
        float HipfireDistance = 200;
        float ZoomDistance = 200;
        
        //AdvancedHitbox
        HitboxType P2020Hitbox = HitboxType::UpperChest;
        HitboxType RE45Hitbox = HitboxType::UpperChest;
        HitboxType AlternatorHitbox = HitboxType::UpperChest;
        HitboxType R99Hitbox = HitboxType::UpperChest;
        HitboxType R301Hitbox = HitboxType::UpperChest;
        HitboxType SpitfireHitbox = HitboxType::UpperChest;
        HitboxType G7Hitbox = HitboxType::UpperChest;
        HitboxType FlatlineHitbox = HitboxType::UpperChest;
        HitboxType HemlockHitbox = HitboxType::UpperChest;
        HitboxType RepeaterHitbox = HitboxType::UpperChest;
        HitboxType RampageHitbox = HitboxType::UpperChest;
        HitboxType CARSMGHitbox = HitboxType::UpperChest;
        HitboxType HavocHitbox = HitboxType::UpperChest;
        HitboxType DevotionHitbox = HitboxType::UpperChest;
        HitboxType LSTARHitbox = HitboxType::UpperChest;
        HitboxType TripleTakeHitbox = HitboxType::UpperChest;
        HitboxType VoltHitbox = HitboxType::UpperChest;
        HitboxType NemesisHitbox = HitboxType::UpperChest;
        HitboxType MozambiqueHitbox = HitboxType::UpperChest;
        HitboxType EVA8Hitbox = HitboxType::UpperChest;
        HitboxType PeacekeeperHitbox = HitboxType::UpperChest;
        HitboxType MastiffHitbox = HitboxType::UpperChest;
        HitboxType LongbowHitbox = HitboxType::UpperChest;
        HitboxType ChargeRifleHitbox = HitboxType::UpperChest;
        HitboxType SentinelHitbox = HitboxType::UpperChest;
        HitboxType WingmanHitbox = HitboxType::UpperChest;
        HitboxType ProwlerHitbox = HitboxType::UpperChest;
        HitboxType BocekHitbox = HitboxType::UpperChest;
        HitboxType KraberHitbox = HitboxType::UpperChest;
        HitboxType ThrowingKnifeHitbox = HitboxType::UpperChest;

        //AdvancedBinds
        InputKeyType P2020AimBind = InputKeyType::MOUSE_Left;
        InputKeyType P2020ExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType RE45AimBind = InputKeyType::MOUSE_Left;
        InputKeyType RE45ExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType AlternatorAimBind = InputKeyType::MOUSE_Left;
        InputKeyType AlternatorExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType R99AimBind = InputKeyType::MOUSE_Left;
        InputKeyType R99ExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType R301AimBind = InputKeyType::MOUSE_Left;
        InputKeyType R301ExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType SpitfireAimBind = InputKeyType::MOUSE_Left;
        InputKeyType SpitfireExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType G7AimBind = InputKeyType::MOUSE_Left;
        InputKeyType G7ExtraBind = InputKeyType::MOUSE_Right;

        InputKeyType FlatlineAimBind = InputKeyType::MOUSE_Left;
        InputKeyType FlatlineExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType HemlockAimBind = InputKeyType::MOUSE_Left;
        InputKeyType HemlockExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType RepeaterAimBind = InputKeyType::MOUSE_Left;
        InputKeyType RepeaterExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType RampageAimBind = InputKeyType::MOUSE_Left;
        InputKeyType RampageExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType CARSMGAimBind = InputKeyType::MOUSE_Left;
        InputKeyType CARSMGExtraBind = InputKeyType::INPUT_NONE;
        
        InputKeyType HavocAimBind = InputKeyType::MOUSE_Left;
        InputKeyType HavocExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType DevotionAimBind = InputKeyType::MOUSE_Left;
        InputKeyType DevotionExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType LSTARAimBind = InputKeyType::MOUSE_Left;
        InputKeyType LSTARExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType TripleTakeAimBind = InputKeyType::MOUSE_Left;
        InputKeyType TripleTakeExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType VoltAimBind = InputKeyType::MOUSE_Left;
        InputKeyType VoltExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType NemesisAimBind = InputKeyType::MOUSE_Left;
        InputKeyType NemesisExtraBind = InputKeyType::INPUT_NONE;

        InputKeyType MozambiqueAimBind = InputKeyType::MOUSE_Left;
        InputKeyType MozambiqueExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType EVA8AimBind = InputKeyType::MOUSE_Left;
        InputKeyType EVA8ExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType PeacekeeperAimBind = InputKeyType::MOUSE_Left;
        InputKeyType PeacekeeperExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType MastiffAimBind = InputKeyType::MOUSE_Left;
        InputKeyType MastiffExtraBind = InputKeyType::MOUSE_Right;

        InputKeyType LongbowAimBind = InputKeyType::MOUSE_Left;
        InputKeyType LongbowExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType ChargeRifleAimBind = InputKeyType::MOUSE_Left;
        InputKeyType ChargeRifleExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType SentinelAimBind = InputKeyType::MOUSE_Left;
        InputKeyType SentinelExtraBind = InputKeyType::MOUSE_Right;

        InputKeyType WingmanAimBind = InputKeyType::MOUSE_Left;
        InputKeyType WingmanExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType ProwlerAimBind = InputKeyType::MOUSE_Left;
        InputKeyType ProwlerExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType BocekAimBind = InputKeyType::MOUSE_Left;
        InputKeyType BocekExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType KraberAimBind = InputKeyType::MOUSE_Left;
        InputKeyType KraberExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType ThrowingKnifeAimBind = InputKeyType::MOUSE_Left;
        InputKeyType ThrowingKnifeExtraBind = InputKeyType::INPUT_NONE;
    };
    
    namespace RCS {
    
    };
    
    namespace Triggerbot {
        bool Enabled = true;
        bool OnADS = true;
        bool HipfireShotguns = false;
        float Range = 200;
    };
    
    namespace Glow {
    
    };

    namespace Sense {
        //Drawings
        bool DrawBox = true;
        float BoxThickness = 2;

        bool DrawTracers = true;
        int TracerPos = 0;
        int TracerBone = 0;
        
        bool Skeleton = true;
        float SkeletonThickness = 1.5f;
        
        int BarMode = 2;
        int BarColorMode = 0;
        bool BarBackground = false;

        int WeaponColorType = 1;
        
        bool DrawSeer = false;
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

    namespace Radar {
        float CircleColor[4] = { 0.999, 0, 0, 0.999 };
    };
    
    namespace Misc {

    };
    
    namespace Colors {
    	int WeaponColorMode = 0;
	//Advanced
    	float InvisibleBoxColor[4] = { 0.99, 0, 0, 0.99 };
    	float VisibleBoxColor[4] = { 0, 0.99, 0, 0.99 };
    	float InvisibleFilledBoxColor[4] = { 0, 0, 0, 0.11 };
    	float VisibleFilledBoxColor[4] = { 0, 0, 0, 0.11 };
    	float InvisibleTracerColor[4] = { 0.99, 0, 0, 0.99 };
    	float VisibleTracerColor[4] = { 0, 0.99, 0, 0.99 };
    	float InvisibleSkeletonColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float VisibleSkeletonColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float InvisibleNameColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float VisibleNameColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float InvisibleDistanceColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float VisibleDistanceColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float InvisibleLegendColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float VisibleLegendColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float FOVColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float FilledFOVColor[4] = { 0, 0, 0, 0.11 };
    	float NearColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float TeamColor[4] = { 0, 0.99, 0.99, 0.99 };
    	float TeamNameColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float CrosshairColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	
    	//Bar
    	int BarColorMode = 2;
    	float BarBGColor[4] = { 0, 0, 0, 0.28 };
    	
    	//WeaponESP Colors
    	float InvisibleWeaponColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float VisibleWeaponColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	//Multiple
    	float LightWeaponColor[4] = { 0.990, 0.768, 0.039, 0.99 };
    	float HeavyWeaponColor[4] = { 0.00990, 0.990, 0.761 };
    	float EnergyWeaponColor[4] = { 0, 0.99, 0, 0.99 };
    	float ShotgunWeaponColor[4] = { 0.99, 0, 0, 0.99 };
    	float SniperWeaponColor[4] = { 0.00990, 0.337, 0.990, 0.99 };
    	float LegendaryWeaponColor[4] = { 0.99, 0.530, 0.945 };
    	float MeleeWeaponColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float ThrowableWeaponColor[4] = { 0.990, 0.974, 0.0495, 0.99 };
    };
    
    namespace Watermark {
        bool Watermark = true;
	    int WatermarkPosition = 0;
	    bool Name = true;
	    bool ProcessingSpeed = true;
	    bool Spectators = true;
    };
}; //End of namespace Modules
