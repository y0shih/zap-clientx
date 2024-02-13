#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <vector>

#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"

#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/QAngle.hpp"
#include "../Math/Resolver.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Modules.hpp"
#include "../Utils/HitboxType.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"

// Geometry
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI / 180.f) )

struct Radar {
    
    bool MiniMap = false;
    float MiniMapRange = 100;
    int MiniMapScaleX = 218;
    int MiniMapScaleY = 218;
    int MiniMapDotSize = 5;
    int MiniMapBlackBGSize = 0;
    bool MiniMapGuides = false;
    
    bool BigMap = false;

    XDisplay* X11Display;
    Camera* GameCamera;
    Level* m_level;
    LocalPlayer* Myself;
    std::vector<Player*>* Players;
    std::chrono::milliseconds LastUpdateTime;
 
    Radar(XDisplay* X11Display, std::vector<Player*>* Players, Camera* GameCamera, Level* level, LocalPlayer* localplayer) {
        this->X11Display = X11Display;
        this->Players = Players;
        this->GameCamera = GameCamera;
        this->m_level = level;
        this->Myself = localplayer;
    }

	void ActivateBigMap() {
		int localPlayerTeamID = Myself->Team;
		if (localPlayerTeamID != 1) {
			float curTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
			double continueTime = 0.2;
			float endTime = curTime + continueTime;
			while (curTime < endTime)
			{
				Memory::Write<int>(Myself->BasePointer + OFF_TEAM_NUMBER, 1);
				curTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
			}
			curTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
			endTime = curTime + continueTime;
			while (curTime < endTime)
			{
				Memory::Write<int>(Myself->BasePointer + OFF_TEAM_NUMBER, localPlayerTeamID);
				curTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
			}
		}
	}

    void RenderUI() {
        if (ImGui::BeginTabItem("Radar", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton | ImGuiTabItemFlags_NoReorder)) {
		ImVec2 TabSize;
		TabSize = ImGui::GetWindowSize();
		//Radar
		ImGui::Text("Mini Map");
		if (ImGui::BeginChild("Mini Map", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 270), true)) {
			ImGui::Text("Mini Map");
			ImGui::Checkbox("Enabled", &MiniMap);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Toggle the mini map radar on the top left of the screen");
			if (MiniMap) {
				ImGui::TextColored(ImVec4(0.99, 0, 0, 0.99), "May not be on-point.");
				ImGui::Separator();
				ImGui::Text("Range");
				ImGui::SliderFloat("Mini Map Radar Range", &MiniMapRange, 0, 180, "%.0f");
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Mini Map range from 0 to 200.");
				
				ImGui::Checkbox("Mini Map Guides", &MiniMapGuides);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Toggle the mini map guides.");

				ImGui::Text("Position");
				ImGui::TextColored(ImVec4(0.99, 0, 0, 0.99), "Turn on Mini Map Guides and allign with your player's arrow on the in-game minimap.");
				ImGui::SliderInt("Mini Map Position X", &MiniMapScaleX, 0, 2560);	
				ImGui::SliderInt("Mini Map Position Y", &MiniMapScaleY, 0, 1440);	

				ImGui::Text("Enemy Identifier");
				ImGui::SliderInt("Mini Map Radar Dot Size", &MiniMapDotSize, 0, 10);
				ImGui::ColorEdit4("Circle Color##Radar", Modules::Radar::CircleColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
			}
			ImGui::EndChild();
		}

		ImGui::Text("Full Map Radar");

		if (ImGui::BeginChild("ALGS Style Map", ImVec2(TabSize.x - TabSize.x , (TabSize.y - TabSize.y) + 285), true)) {
			ImGui::Text("ALGS Style Map");
			ImGui::Checkbox("Enabled", &BigMap);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Toggle the ALGS Style Map.");
			if (BigMap) {
				if (ImGui::Button("Active")) {
					ActivateBigMap();
				}
				ImGui::TextColored(ImVec4(0.99, 0, 0, 0.99), "Make sure to close out of the in-game map before activating or you will crash!");
			}
			ImGui::EndChild();
		}
            ImGui::EndTabItem();
            }
	}

	bool Save() {
        try {
			Config::Radar::MiniMap = MiniMap;
			Config::Radar::MiniMapRange = MiniMapRange;
			Config::Radar::MiniMapScaleX = MiniMapScaleX;
			Config::Radar::MiniMapScaleY = MiniMapScaleY;
			Config::Radar::MiniMapDotSize = MiniMapDotSize;
			Config::Radar::MiniMapGuides = MiniMapGuides;
			Config::Radar::BigMap = BigMap;
            return true;
        } catch (...) {
            return false;
        }
    }

    void RenderDrawings(ImDrawList* Canvas, LocalPlayer* Myself, Overlay OverlayWindow) {
        int ScreenWidth;
        int ScreenHeight;
        OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
        if (!m_level->IsPlayable) return;
		
        if(MiniMap){
			ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
			
			ImGui::Begin(("Radar"), (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);

			for (auto i = 0; i < Players->size(); i++)
			{
				Player *p = Players->at(i);
				if (!p->IsHostile || !p->IsValid() || Myself->BasePointer == p->BasePointer) continue;

				float radardistance = (int)((Myself->LocalOrigin, p->Distance2DToLocalPlayer) / 39.62);

				MiniMapRadar(p->LocalOrigin, Myself->LocalOrigin, p->ViewAngles.y, radardistance, p->Team, p->ViewYaw);
			} 
			ImGui::End();                   
        }
      }
      
	// DRAW RADAR POINT mini Map
      void DrawRadarPointMiniMap(Vector3D EnemyPos, Vector3D LocalPos, float targetY, float enemyDist, int TeamID, int xAxis, int yAxis, int width, int height, ImColor color, float targetyaw)
	{
		bool out = false;
		Vector3D siz;
		siz.x = width;
		siz.y = height;
		Vector3D pos;
		pos.x = xAxis;
		pos.y = yAxis;
		bool ck = false;

		Vector3D single = Renderer::RotatePoint(EnemyPos, LocalPos, pos.x, pos.y, siz.x, siz.y, targetY, 0.3f, &ck);
		if (enemyDist >= 0.f && enemyDist < MiniMapRange)
		{
			for (int i = 1; i <= 30; i++)
			{
				Renderer::TeamMiniMap(single.x, single.y, MiniMapDotSize, TeamID, targetyaw, MiniMapDotSize, MiniMapBlackBGSize, ImColor(Modules::Radar::CircleColor[0], Modules::Radar::CircleColor[1], Modules::Radar::CircleColor[2], Modules::Radar::CircleColor[3]));
			}
		}
	}

	//MINI MAP RADAR IMPLEMENTATION
	void MiniMapRadar(Vector3D EnemyPos, Vector3D LocalPos, float targetY, float eneamyDist, int TeamId, float targetyaw)
	{
		/*ImGuiStyle* style = &ImGui::GetStyle();
		style->WindowRounding = 0.2f;
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13529413f, 0.14705884f, 0.15490198f, 0.82f));*/
		ImGuiWindowFlags TargetFlags;
		TargetFlags = ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar;	
		if (MiniMap)
		{
			// 1920*1080: 215 x 215
			// 2560*1440: 335 x 335
			ImGui::SetNextWindowSize({ MiniMapScaleX, MiniMapScaleY });
			ImGui::Begin(("##Radar"), 0, TargetFlags);
			{
				ImDrawList* Draw = ImGui::GetWindowDrawList();
				ImVec2 DrawPos = ImGui::GetCursorScreenPos();
				ImVec2 DrawSize = ImGui::GetContentRegionAvail();
				ImVec2 midRadar = ImVec2(DrawPos.x + (DrawSize.x / 2), DrawPos.y + (DrawSize.y / 2));
				if (MiniMapGuides)
				{
					ImVec2 startHorizontal(midRadar.x - DrawSize.x / 2.f, midRadar.y);
					ImVec2 endHorizontal(midRadar.x + DrawSize.x / 2.f, midRadar.y);
					ImVec2 startVertical(midRadar.x, midRadar.y - DrawSize.y / 2.f);
					ImVec2 endVertical(midRadar.x, midRadar.y + DrawSize.y / 2.f);
					float extension = -500000.f;
					
					ImGui::GetWindowDrawList()->AddLine(startHorizontal, ImVec2(startHorizontal.x - extension, endHorizontal.y), IM_COL32(255, 255, 255, 255));
					ImGui::GetWindowDrawList()->AddLine(endHorizontal, ImVec2(endHorizontal.x + extension, endHorizontal.y), IM_COL32(255, 255, 255, 255));

		
					ImGui::GetWindowDrawList()->AddLine(startVertical, ImVec2(startVertical.x, startVertical.y - extension), IM_COL32(255, 255, 255, 255));
					ImGui::GetWindowDrawList()->AddLine(endVertical, ImVec2(endVertical.x, endVertical.y + extension), IM_COL32(255, 255, 255, 255));		}
								
				DrawRadarPointMiniMap(EnemyPos, LocalPos, targetY, eneamyDist, TeamId, DrawPos.x, DrawPos.y, DrawSize.x, DrawSize.y, { 255, 255, 255, 255 }, targetyaw);
			}
			ImGui::End();
		}
	}



};
