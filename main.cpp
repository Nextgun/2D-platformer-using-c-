// 2D Platformer using c++ 
// using olcPixelGameEngine by Javidx9 - OneLoneCoder

#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngineOOP.h"
#include "cMap.h"
#include "RPG_Assets.h"
#include "cDynamic.h"
#include "cDynamicCreature.h"
#include "RPG_Commands.h"
//#include <olcConsoleGameEngineOOP.cpp>

class HJ_Platformer : public olcConsoleGameEngineOOP
{
public:
	HJ_Platformer()
	{
		m_sAppName = L"Tile Based Platform Game";
	}
private:
	cMap* m_pCurrentMap = nullptr;

	cDynamic* m_pPlayer = nullptr;
	
	vector<cDynamic*> m_vecDynamics;


	cScriptProcessor m_script;

	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

	//Sprite Resources
	olcSprite* spriteTiles = nullptr;
	olcSprite* spriteMan = nullptr;
	olcSprite* m_sprFont = nullptr;

	//Sprite selection flags
	int nDirModX = 0;
	int nDirModY = 0;
	
	void DrawBigText(string sText, int x, int y)
	{
		int i = 0;
		for (auto c : sText)
		{
			int sx = ((c - 32) % 16) * 8;
			int sy = ((c - 32) / 16) * 8;
			DrawPartialSprite(x + i * 8, y, m_sprFont, sx, sy, 8, 8);
			i++;
		}

	}


protected:
	virtual bool OnUserCreate()
	{
		cCommand::g_engine = this;
		RPG_Assets::get().LoadSprites();	// load all sprites
		RPG_Assets::get().LoadMaps();		// load all maps
		cCommand::g_engine = this;
		RPG_Assets::get().LoadSprites();
		
		m_sprFont = RPG_Assets::get().GetSprite("Font");
		
		m_pCurrentMap = RPG_Assets::get().GetMap("coder town");

		m_pPlayer = new cDynamicCreature("player", RPG_Assets::get().GetSprite("player"));
		m_pPlayer->fPositionX = 5.0f;
		m_pPlayer->fPositionY = 5.0f;
		
		cDynamic* ob1 = new cDynamicCreature("skelly1", RPG_Assets::get().GetSprite("skelly"));
		ob1->fPositionX = 12.0f;
		ob1->fPositionY = 12.0f;
		
		cDynamic* ob2 = new cDynamicCreature("skelly2", RPG_Assets::get().GetSprite("skelly"));
		ob2->fPositionX = 5.0f;
		ob2->fPositionY = 8.0f;

		m_vecDynamics.push_back(m_pPlayer);
		m_vecDynamics.push_back(ob1);
		m_vecDynamics.push_back(ob2);
		

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		//Update script
		m_script.ProcessCommands(fElapsedTime);
		
		if (m_script.bUserControlEnabled)
		{

			m_pPlayer->fVelocityX = 0.0f;
			m_pPlayer->fVelocityY = 0.0f;

			//Handle Input
			if (IsFocused())
			{
				if (GetKey(VK_UP).bHeld)
				{
					m_pPlayer->fVelocityY = -4.0f;
				}

				if (GetKey(VK_DOWN).bHeld)
				{
					m_pPlayer->fVelocityY = 4.0f;
				}

				if (GetKey(VK_LEFT).bHeld)
				{
					m_pPlayer->fVelocityX = -4.0f;
				}

				if (GetKey(VK_RIGHT).bHeld)
				{
					m_pPlayer->fVelocityX = 4.0f;
				}
				if (GetKey(L'Z').bReleased)
				{
					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 10, 10, 3.0f));
					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 15, 10, 3.0f));
					m_script.AddCommand(new cCommand_MoveTo(m_vecDynamics[1], 15, 12, 2.0f));
					m_script.AddCommand(new cCommand_ShowDialog({"Grrrr"}));
					m_script.AddCommand(new cCommand_ShowDialog({"I think OOP", "is really useful!"}));

					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 15, 15, 3.0f));
					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 10, 10, 3.0f));
				}
			}
		}
		else
		{
			//Scripting system is in control
			if (GetKey(VK_SPACE).bReleased)
			{
				m_bShowDialog = false;
				m_script.CompleteCommand();
			}


		}
		
		for (auto& object : m_vecDynamics)
		{


			float fNewObjectPosX = object->fPositionX + object->fVelocityX * fElapsedTime;
			float fNewObjectPosY = object->fPositionY + object->fVelocityY * fElapsedTime;

			//Collision
			if (object->fVelocityX <= 0)
			{
				if (m_pCurrentMap->GetSolid(fNewObjectPosX + 0.0f, object->fPositionY + 0.0f) || m_pCurrentMap->GetSolid(fNewObjectPosX + 0.0f, object->fPositionY + 0.9f))
				{
					fNewObjectPosX = (int)fNewObjectPosX + 1;
					object->fVelocityX = 0;
				}

			}
			else
			{
				if (m_pCurrentMap->GetSolid(fNewObjectPosX + 1.0f, object->fPositionY + 0.0f) || m_pCurrentMap->GetSolid(fNewObjectPosX + 1.0f, object->fPositionY + 0.9f))
				{
					fNewObjectPosX = (int)fNewObjectPosX;
					object->fVelocityX = 0;
				}
			}

			if (object->fVelocityY <= 0)
			{
				if (m_pCurrentMap->GetSolid(fNewObjectPosX + 0.0f, fNewObjectPosY) || m_pCurrentMap->GetSolid(fNewObjectPosX + 0.9f, fNewObjectPosY))
				{
					fNewObjectPosY = (int)fNewObjectPosY + 1;
					object->fVelocityX = 0;
				}

			}
			else
			{
				if (m_pCurrentMap->GetSolid(fNewObjectPosX + 0.0f, fNewObjectPosY + 1.0f) || m_pCurrentMap->GetSolid(fNewObjectPosX + 0.9f, fNewObjectPosY + 1.0f))
				{
					fNewObjectPosY = (int)fNewObjectPosY;
					object->fVelocityY = 0;
				}
			}

			object->px = fNewObjectPosX;
			object->py = fNewObjectPosY;

			object->Update(fElapsedTime);
		}
			fCameraPosX = m_pPlayer->px;
			fCameraPosY = m_pPlayer->py;
		
		// Draw the level
		int nTileWidth = 16;
		int nTileHeight = 16;
		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// calculate top-leftmost visible tile
		//		offset the camera so that it is positioned 
		//		in the middle of the screen.
		float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

		//Clamp camera to game boundaries 
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;
		if (fOffsetX > m_pCurrentMap->nWidth - nVisibleTilesX) fOffsetX = m_pCurrentMap->nWidth - nVisibleTilesX;
		if (fOffsetY > m_pCurrentMap->nHeight - nVisibleTilesY) fOffsetY = m_pCurrentMap->nHeight - nVisibleTilesY;

		//Get offsets for smooth movement
		float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
		float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;	

		//Draw visible tile map
		for (int x = -1; x < nVisibleTilesX + 1; x++)
		{
			for (int y = -1; y < nVisibleTilesY + 1; y++)
			{
				int idx = m_pCurrentMap->GetIndex(x + fOffsetX, y + fOffsetY);
				int sx = idx % 10; // column
				int sy = idx / 10; // row
			
				DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, m_pCurrentMap->pSprite, sx * nTileWidth, sy * nTileHeight, nTileWidth, nTileHeight);
			}
		}

		//Draw object
		// create a third array storing which layer the tile belongs too
		// create a new draw map loop that only draws tiles that exist in the 3rd layer, 
		//		so that it gets drawn on top of the player character .
		for (auto& object : m_vecDynamics)
			object->DrawSelf(this, fOffsetX, fOffsetY);
		
		m_pPlayer->DrawSelf(this, fOffsetX, fOffsetY);

		//Draw any dialog being displayed
		if (m_bShowDialog)
			DisplayDialog(m_vecDialogToShow, 20, 20);



		return true;
	}
	
	vector<string> m_vecDialogToShow;
	bool m_bShowDialog = false;
	float m_fDialogX = 0.0f;
	float m_fDialogY = 0.0f;
	

	void ShowDialog(vector<string> vecLines)
	{
		m_vecDialogToShow = vecLines;
		m_bShowDialog = true;
	}

	void DisplayDialog(vector<string> vecText, int x, int y)
	{
		int nMaxLineLength = 0;
		int nLines = vecText.size();

		for (auto l : vecText) if (l.size() > nMaxLineLength) nMaxLineLength = l.size();

		//Draw box

		Fill(x - 1, y - 1, x + nMaxLineLength * 8 + 1, y + nLines * 8 + 1, PIXEL_SOLID, FG_DARK_BLUE);
		DrawLine(x - 2, y - 2, x - 2, y+nLines * 8 + 1);
		DrawLine(x + nMaxLineLength * 8 + 1, y - 2, x + nMaxLineLength * 8 + 1, y + nLines * 8 + 1);
		DrawLine(x - 2, y - 2, x + nMaxLineLength * 8 + 1, y - 2 );
		DrawLine(x - 2, y + nLines * 8 + 1, x + nMaxLineLength * 8 + 1, y + nLines * 8 +1);

		for (int l = 0; l < vecText.size(); l++)
			DrawBigText(vecText[l], x, y + 1 * 8);
	}

};



int main()
{
	HJ_Platformer game;
	if (game.ConstructConsole(260, 240, 4, 4))
		game.Start();

	return 0;
}

