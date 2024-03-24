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
#include "../Core/Level.hpp"

#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/QAngle.hpp"
#include "../Math/Resolver.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/InputTypes.hpp"
#include "../Utils/Weapons.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

typedef void *PVOID;

struct Misc
{
	/*bool TeamGamemode = true;
	bool SkinChanger = false;

	// Weapon IDs
	// Light
	int SkinP2020 = 1;
	int SkinRE45 = 1;
	int SkinALTERNATOR = 1;
	int SkinR99 = 1;
	int SkinR301 = 1;
	int SkinSPITFIRE = 1;
	int SkinG7 = 1;

	// Heavy
	int SkinFLATLINE = 1;
	int SkinHEMLOCK = 1;
	int SkinREPEATER = 1;
	int SkinRAMPAGE = 1;
	int SkinCAR = 1;

	// Energy
	int SkinHAVOC = 1;
	int SkinDEVOTION = 1;
	int SkinLSTAR = 1;
	int SkinTRIPLETAKE = 1;
	int SkinVOLT = 1;
	int SkinNEMESIS = 1;

	// Shotgun
	int SkinMOZAMBIQUE = 1;
	int SkinEVA8 = 1;
	int SkinPEACEKEEPER = 1;
	int SkinMASTIFF = 1;

	// Snipers
	int SkinLONGBOW = 1;
	int SkinCHARGE_RIFLE = 1;
	int SkinSENTINEL = 1;

	// Legendary
	int SkinWINGMAN = 1;
	int SkinPROWLER = 1;
	int SkinBOCEK = 1;
	int SkinKRABER = 1;*/

	std::set<int> RapidFireList = {};

	XDisplay *X11Display;
	Level *Map;
	LocalPlayer *Myself;
	std::vector<Player *> *Players;

	Misc(XDisplay *X11Display, Level *Map, LocalPlayer *Myself, std::vector<Player *> *GamePlayers)
	{
		this->X11Display = X11Display;
		this->Map = Map;
		this->Myself = Myself;
		this->Players = GamePlayers;
	}

	bool Save()
	{
		try
		{
			Config::Misc::SuperGlide = Features::Misc::SuperGlide;

			Config::Misc::QuickTurn = Features::Misc::QuickTurn;
			Config::Misc::QuickTurnAngle = Features::Misc::QuickTurnAngle;
			Config::Misc::QuickTurnBind = static_cast<int>(Features::Misc::QuickTurnBind);

			Config::Misc::BHop = Features::Misc::BHop;
			Config::Misc::BHopDelay = Features::Misc::BHopDelay;
			Config::Misc::BHopBind = static_cast<int>(Features::Misc::BHopBind);

			Config::Misc::RapidFire = Features::Misc::RapidFire;
			Config::Misc::RapidFireDelay = Features::Misc::RapidFireDelay;
			Config::Misc::RapidFireBind = static_cast<int>(Features::Misc::RapidFireBind);
			// Rapid Fire Weapons
			Config::Misc::RapidP2020 = Features::Misc::RapidP2020;
			Config::Misc::RapidR301 = Features::Misc::RapidR301;
			Config::Misc::RapidG7 = Features::Misc::RapidG7;
			Config::Misc::RapidFlatline = Features::Misc::RapidFlatline;
			Config::Misc::RapidHemlock = Features::Misc::RapidHemlock;
			Config::Misc::RapidProwler = Features::Misc::RapidProwler;
			Config::Misc::RapidNemesis = Features::Misc::RapidNemesis;
			Config::Misc::RapidMozambique = Features::Misc::RapidMozambique;
			Config::Misc::RapidEVA8 = Features::Misc::RapidEVA8;
			Config::Misc::RapidWingman = Features::Misc::RapidWingman;

			Config::Misc::SkinChanger = Features::Misc::SkinChanger;
			// Weapon IDs
			// Light
			Config::Misc::SkinP2020 = Features::Misc::SkinP2020;
			Config::Misc::SkinRE45 = Features::Misc::SkinRE45;
			Config::Misc::SkinALTERNATOR = Features::Misc::SkinALTERNATOR;
			Config::Misc::SkinR99 = Features::Misc::SkinR99;
			Config::Misc::SkinR301 = Features::Misc::SkinR301;
			Config::Misc::SkinSPITFIRE = Features::Misc::SkinSPITFIRE;
			Config::Misc::SkinG7 = Features::Misc::SkinG7;

			// Heavy
			Config::Misc::SkinFLATLINE = Features::Misc::SkinFLATLINE;
			Config::Misc::SkinHEMLOCK = Features::Misc::SkinHEMLOCK;
			Config::Misc::SkinREPEATER = Features::Misc::SkinREPEATER;
			Config::Misc::SkinRAMPAGE = Features::Misc::SkinRAMPAGE;
			Config::Misc::SkinCAR = Features::Misc::SkinCAR;

			// Energy
			Config::Misc::SkinHAVOC = Features::Misc::SkinHAVOC;
			Config::Misc::SkinDEVOTION = Features::Misc::SkinDEVOTION;
			Config::Misc::SkinLSTAR = Features::Misc::SkinLSTAR;
			Config::Misc::SkinTRIPLETAKE = Features::Misc::SkinTRIPLETAKE;
			Config::Misc::SkinVOLT = Features::Misc::SkinVOLT;
			Config::Misc::SkinNEMESIS = Features::Misc::SkinNEMESIS;

			// Shotgun
			Config::Misc::SkinMOZAMBIQUE = Features::Misc::SkinMOZAMBIQUE;
			Config::Misc::SkinEVA8 = Features::Misc::SkinEVA8;
			Config::Misc::SkinPEACEKEEPER = Features::Misc::SkinPEACEKEEPER;
			Config::Misc::SkinMASTIFF = Features::Misc::SkinMASTIFF;

			// Snipers
			Config::Misc::SkinLONGBOW = Features::Misc::SkinLONGBOW;
			Config::Misc::SkinCHARGE_RIFLE = Features::Misc::SkinCHARGE_RIFLE;
			Config::Misc::SkinSENTINEL = Features::Misc::SkinSENTINEL;

			// Legendary
			Config::Misc::SkinWINGMAN = Features::Misc::SkinWINGMAN;
			Config::Misc::SkinPROWLER = Features::Misc::SkinPROWLER;
			Config::Misc::SkinBOCEK = Features::Misc::SkinBOCEK;
			Config::Misc::SkinKRABER = Features::Misc::SkinKRABER;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	void UpdateRapidFireList()
	{
		// Update RapidFireList
		RapidFireList.clear();
		if (Features::Misc::RapidP2020)
			RapidFireList.insert(WeaponIDs::WEAPON_P2020);
		if (Features::Misc::RapidR301)
			RapidFireList.insert(WeaponIDs::WEAPON_R301);
		if (Features::Misc::RapidG7)
			RapidFireList.insert(WeaponIDs::WEAPON_G7);
		if (Features::Misc::RapidFlatline)
			RapidFireList.insert(WeaponIDs::WEAPON_FLATLINE);
		if (Features::Misc::RapidHemlock)
			RapidFireList.insert(WeaponIDs::WEAPON_HEMLOCK);
		if (Features::Misc::RapidProwler)
			RapidFireList.insert(WeaponIDs::WEAPON_PROWLER);
		if (Features::Misc::RapidNemesis)
			RapidFireList.insert(WeaponIDs::WEAPON_NEMESIS);
		if (Features::Misc::RapidMozambique)
			RapidFireList.insert(WeaponIDs::WEAPON_MOZAMBIQUE);
		if (Features::Misc::RapidWingman)
			RapidFireList.insert(WeaponIDs::WEAPON_WINGMAN);
		if (Features::Misc::RapidEVA8)
			RapidFireList.insert(WeaponIDs::WEAPON_EVA8);
	}

	void Update()
	{
		if (!Map->IsPlayable)
			return;
		if (Myself->IsDead)
			return;

		if (Features::Misc::SkinChanger)
		{
			long wephandle = Memory::Read<long>(Myself->BasePointer + OFF_WEAPON_HANDLE);
			wephandle &= 0xffff;
			long wep_entity = Myself->WeaponEntity;
			std::map<int, int> weaponSkinMap;
			// Light ammo weapons
			weaponSkinMap[SkinChangerID::WEAPON_P2020] = Features::Misc::SkinP2020;
			weaponSkinMap[SkinChangerID::WEAPON_RE45] = Features::Misc::SkinRE45;
			weaponSkinMap[SkinChangerID::WEAPON_ALTERNATOR] = Features::Misc::SkinALTERNATOR;
			weaponSkinMap[SkinChangerID::WEAPON_R99] = Features::Misc::SkinR99;
			weaponSkinMap[SkinChangerID::WEAPON_R301] = Features::Misc::SkinR301;
			weaponSkinMap[SkinChangerID::WEAPON_SPITFIRE] = Features::Misc::SkinSPITFIRE;
			weaponSkinMap[SkinChangerID::WEAPON_G7] = Features::Misc::SkinG7;
			// Heavy ammo weapons
			weaponSkinMap[SkinChangerID::WEAPON_CAR] = Features::Misc::SkinCAR;
			weaponSkinMap[SkinChangerID::WEAPON_RAMPAGE] = Features::Misc::SkinRAMPAGE;
			weaponSkinMap[SkinChangerID::WEAPON_REPEATER] = Features::Misc::SkinREPEATER;
			weaponSkinMap[SkinChangerID::WEAPON_HEMLOCK] = Features::Misc::SkinHEMLOCK;
			weaponSkinMap[SkinChangerID::WEAPON_FLATLINE] = Features::Misc::SkinFLATLINE;
			// Energy ammo weapons
			weaponSkinMap[SkinChangerID::WEAPON_NEMESIS] = Features::Misc::SkinNEMESIS;
			weaponSkinMap[SkinChangerID::WEAPON_VOLT] = Features::Misc::SkinVOLT;
			weaponSkinMap[SkinChangerID::WEAPON_TRIPLETAKE] = Features::Misc::SkinTRIPLETAKE;
			weaponSkinMap[SkinChangerID::WEAPON_LSTAR] = Features::Misc::SkinLSTAR;
			weaponSkinMap[SkinChangerID::WEAPON_DEVOTION] = Features::Misc::SkinDEVOTION;
			weaponSkinMap[SkinChangerID::WEAPON_HAVOC] = Features::Misc::SkinHAVOC;
			// Sniper ammo weapons
			weaponSkinMap[SkinChangerID::WEAPON_SENTINEL] = Features::Misc::SkinSENTINEL;
			weaponSkinMap[SkinChangerID::WEAPON_CHARGE_RIFLE] = Features::Misc::SkinCHARGE_RIFLE;
			weaponSkinMap[SkinChangerID::WEAPON_LONGBOW] = Features::Misc::SkinLONGBOW;
			// Shotgun ammo weapons
			weaponSkinMap[SkinChangerID::WEAPON_MOZAMBIQUE] = Features::Misc::SkinMOZAMBIQUE;
			weaponSkinMap[SkinChangerID::WEAPON_EVA8] = Features::Misc::SkinEVA8;
			weaponSkinMap[SkinChangerID::WEAPON_PEACEKEEPER] = Features::Misc::SkinPEACEKEEPER;
			weaponSkinMap[SkinChangerID::WEAPON_MASTIFF] = Features::Misc::SkinMASTIFF;
			// Legendary ammo weapons
			weaponSkinMap[SkinChangerID::WEAPON_WINGMAN] = Features::Misc::SkinWINGMAN;
			weaponSkinMap[SkinChangerID::WEAPON_PROWLER] = Features::Misc::SkinPROWLER;
			weaponSkinMap[SkinChangerID::WEAPON_BOCEK] = Features::Misc::SkinBOCEK;
			weaponSkinMap[SkinChangerID::WEAPON_KRABER] = Features::Misc::SkinKRABER;

			int waponIndex = Memory::Read<int>(wep_entity + OFF_WEAPON_INDEX);
			if (weaponSkinMap.count(waponIndex) == 0)
				return;
			int skinID = weaponSkinMap[waponIndex];
			// printf("Weapon: %s Activated Skin ID: %d \n", WeaponName(waponIndex).c_str(), skinID);
			Memory::Write<int>(wep_entity + OFF_SKIN, skinID);
		}
	} // End of update

	void SuperGlide()
	{
		if (InputManager::isKeyDownOrPress(InputKeyType::KEYBOARD_SPACE))
		{
			static float startjumpTime = 0;
			static bool startSg = false;
			static float traversalProgressTmp = 0.0;

			float worldtime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);						   // Current time
			float traversalStartTime = Memory::Read<float>(Myself->BasePointer + OFFSET_TRAVERSAL_START_TIME); // Time to start wall climbing
			float traversalProgress = Memory::Read<float>(Myself->BasePointer + OFFSET_TRAVERSAL_PROGRESS);	   // Wall climbing, if > 0.87 it is almost over.
			float HangOnWall = -(traversalStartTime - worldtime);

			if (HangOnWall > 0.1 && HangOnWall < 0.12)
			{
				Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
			}
			if (traversalProgress > 0.87f && !startSg && HangOnWall > 0.1f && HangOnWall < 1.5f)
			{
				// start SG
				startjumpTime = worldtime;
				startSg = true;
			}
			if (startSg)
			{
				Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
				while (Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE) - startjumpTime < 0.011)
					;
				{
					Memory::Write<int>(OFF_REGION + OFF_IN_DUCK + 0x8, 6);
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
					Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
					std::this_thread::sleep_for(std::chrono::milliseconds(600));
				}
				startSg = false;
			}
		}
	}

	void BHop()
	{
		if (InputManager::isKeyDownOrPress(Features::Misc::BHopBind) && InputManager::isKeyDownOrPress(InputKeyType::KEYBOARD_SPACE))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(Features::Misc::BHopDelay));
			Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x08, 5);
			std::this_thread::sleep_for(std::chrono::milliseconds(Features::Misc::BHopDelay));
			Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x08, 4);
		}
	}

	void QuickTurn()
	{
		if (Features::Misc::QuickTurn)
		{
			FloatVector2D localYawtoClamp = Myself->viewAngles;
			localYawtoClamp.clamp();
			float localYaw = localYawtoClamp.y;
			// quickTurn
			if (InputManager::isKeyDown(Features::Misc::QuickTurnBind))
			{
				Myself->setYaw((localYaw + Features::Misc::QuickTurnAngle));
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
		}
	}

	void RapidFire()
	{
		if (!Myself->IsCombatReady())
			return;
		if (RapidFireList.find(Myself->WeaponIndex) == RapidFireList.end())
			return;
		if (InputManager::isKeyDownOrPress(Features::Misc::RapidFireBind))
		{
			X11Display->MouseClickLeft();
			std::this_thread::sleep_for(std::chrono::milliseconds(Features::Misc::RapidFireDelay));
		}
	}
};
