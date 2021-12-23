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
		RPG_Assets::get().LoadSprites();	// load all sprites
		RPG_Assets::get().LoadMaps();		// load all maps
		
		m_sprFont = RPG_Assets::get().GetSprite("Font");
		
		m_pCurrentMap = RPG_Assets::get().GetMap("coder town");

		spriteTiles = new olcSprite(L"../SpriteEditor/mario1.spr");
		spriteMan = new olcSprite(L"../SpriteEditor/miniJario.spr");

		m_pPlayer = new cDynamicCreature("player", RPG_Assets::get().GetSprite("player"));
		m_pPlayer->fPositionX = 5.0f;
		m_pPlayer->fPositionY = 5.0f;


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
					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 15, 15, 3.0f));
					m_script.AddCommand(new cCommand_MoveTo(m_pPlayer, 10, 10, 3.0f));
				}
			}
		}
		
		cDynamic* object = m_pPlayer;

		float fNewObjectPosX = object->fPositionX + object->fVelocityX * fElapsedTime;
		float fNewObjectPosY = object->fPositionY + object->fVelocityY * fElapsedTime;

		//Collision
		if (object->fVelocityX <= 0)
		{
			if (m_pCurrentMap->GetSolid(fNewObjectPosX + 0.0f, object->fPositionY + 0.0f) || m_pCurrentMap->GetSolid(fNewObjectPosX + 0.0f, object->fPositionY + 0.9f) )
			{
				fNewObjectPosX = (int)fNewObjectPosX + 1;
				object->fVelocityX = 0;
			}
				 
		}
		else
		{
			if (m_pCurrentMap->GetSolid(fNewObjectPosX + 1.0f, object->fPositionY + 0.0f) || m_pCurrentMap->GetSolid(fNewObjectPosX + 1.0f, object->fPositionY + 0.9f) )
			{
				fNewObjectPosX = (int)fNewObjectPosX;
				object->fVelocityX = 0;
			}
		}

		if (object->fVelocityY <= 0)
		{
			if (m_pCurrentMap->GetSolid(fNewObjectPosX + 0.0f, fNewObjectPosY) || m_pCurrentMap->GetSolid(fNewObjectPosX + 0.9f, fNewObjectPosY) )
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

		object->fPositionX = fNewObjectPosX;
		object->fPositionY = fNewObjectPosY;

		object->Update(fElapsedTime);

		fCameraPosX = m_pPlayer->fPositionX;
		fCameraPosY = m_pPlayer->fPositionY;

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
		object->DrawSelf(this, fOffsetX, fOffsetY);

		// create a third array storing which layer the tile belongs too
		// create a new draw map loop that only draws tiles that exist in the 3rd layer, 
		//		so that it gets drawn on top of the player character .

		DrawBigText("Hello Everybody!", 30, 30);
		
		return true;
	}
};



int main()
{
	HJ_Platformer game;
	if (game.ConstructConsole(117, 110, 4, 4))
		game.Start();

	return 0;
}

