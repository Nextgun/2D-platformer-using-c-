// 2D Platformer using c++ 
// using olcPixelGameEngine by Javidx9 - OneLoneCoder

#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngineOOP.h"
#include "cMap.h"
#include "RPG_Assets.h"
#include "RPG_Commands.h"
#include <olcConsoleGameEngineOOP.cpp>

class HJ_Platformer : public olcConsoleGameEngineOOP
{
public:
	HJ_Platformer()
	{
		m_sAppName = L"Tile Based Platform Game";
	}
private:
	cMap* m_pCurrentMap = nullptr;
	
	cScriptProcessor m_script;

	float fPlayerPosX = 5.0f;
	float fPlayerPosY = 6.0f;

	float fPlayerVelX = 0.0f;
	float fPlayerVelY = 0.0f;

	bool bPlayerOnGround = false;

	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

	//Sprite Resources
	olcSprite* spriteTiles = nullptr;
	olcSprite* spriteMan = nullptr;

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
		RPG_Assets::get().LoadSprites();
		
		m_sprFont = RPG_Assets::get().GetSprite("Font");
		
		m_pCurrentMap = new cMap_Village1();

		spriteTiles = new olcSprite(L"../SpriteEditor/mario1.spr");
		spriteMan = new olcSprite(L"../SpriteEditor/miniJario.spr");

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		//Update script
		m_script.ProcessCommands(fElapsedTime);
		
		if (m_script.bUserControlEnabled)
		{



			fPlayerVelX = 0.0f;
			fPlayerVelY = 0.0f;

			//Handle Input
			if (IsFocused())
			{
				if (GetKey(VK_UP).bHeld)
				{
					fPlayerVelY = -4.0f;
				}

				if (GetKey(VK_DOWN).bHeld)
				{
					fPlayerVelY = 4.0f;
				}

				if (GetKey(VK_LEFT).bHeld)
				{
					fPlayerVelX = -4.0f;
				}

				if (GetKey(VK_RIGHT).bHeld)
				{
					fPlayerVelX = 4.0f;
				}
				if (GetKey(L'Z').bReleased)
				{
					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 10, 10, 3.0f));
					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 15, 10, 3.0f));
					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 15, 15, 3.0f));
					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 10, 10, 3.0f));
				}
			}
		}

		float fNewPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
		float fNewPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;

		//Collision
		if (fPlayerVelX <= 0)
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.0f) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.9f) )
			{
				fNewPlayerPosX = (int)fNewPlayerPosX + 1;
				fPlayerVelX = 0;
			}
				 
		}
		else
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.0f) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.9f) )
			{
				fNewPlayerPosX = (int)fNewPlayerPosX;
				fPlayerVelX = 0;
			}
		}

		if (fPlayerVelY <= 0)
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fNewPlayerPosY) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.9f, fNewPlayerPosY) )
			{
				fNewPlayerPosY = (int)fNewPlayerPosY + 1;
				fPlayerVelX = 0;
			}

		}
		else
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.9f, fNewPlayerPosY + 1.0f))
			{
				fNewPlayerPosY = (int)fNewPlayerPosY;
				fPlayerVelY = 0;
			}
		}

		fPlayerPosX = fNewPlayerPosX;
		fPlayerPosY = fNewPlayerPosY;


		fCameraPosX = fPlayerPosX;
		fCameraPosY = fPlayerPosY;

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

		//Draw Player
		Fill((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileWidth, (fPlayerPosX - fOffsetX + 1.0f) * nTileWidth, (fPlayerPosY - fOffsetY + 1.0f) * nTileHeight, PIXEL_SOLID, FG_GREEN);

		DrawBigText("Hello Everybody!", 30, 30);

		return true;
	}
};



int main()
{
	HJ_Platformer game;
	if (game.ConstructConsole(256, 240, 4, 4))
		game.Start();

	return 0;
}

