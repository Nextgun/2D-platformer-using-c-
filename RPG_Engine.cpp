
#include "RPG_Engine.h"
#define X(n) m_script.AddCommand(new cCommand_ ## n)

	RPG_Engine::RPG_Engine()
	{
		m_sAppName = L"Top Down Role Playing Game";
	}


	bool RPG_Engine::OnUserCreate()
	{
		cCommand::g_engine = this;
		RPG_Assets::get().LoadSprites();	// load all sprites
		RPG_Assets::get().LoadMaps();		// load all maps

		m_sprFont = RPG_Assets::get().GetSprite("font");


		m_pPlayer = new cDynamicCreature("player", RPG_Assets::get().GetSprite("player"));
		ChangeMap("coder town", 5, 5);


		return true;
	}

	bool RPG_Engine::OnUserUpdate(float fElapsedTime)
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
					m_script.AddCommand(new cCommand_ShowDialog({ "Grrrr" }));
					m_script.AddCommand(new cCommand_ShowDialog({ "I think OOP", "is really useful!" }));

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

		for (auto &object : m_vecDynamics)
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

			object->fPositionX = fNewObjectPosX;
			object->fPositionY = fNewObjectPosY;

			object->Update(fElapsedTime);
		}

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

	void RPG_Engine::ShowDialog(vector<string> vecLines)
	{
		m_vecDialogToShow = vecLines;
		m_bShowDialog = true;
	}

	void RPG_Engine::DisplayDialog(vector<string> vecText, int x, int y)
	{
		int nMaxLineLength = 0;
		int nLines = vecText.size();

		for (auto l : vecText) if (l.size() > nMaxLineLength) nMaxLineLength = l.size();

		//Draw box

		Fill(x - 1, y - 1, x + nMaxLineLength * 8 + 1, y + nLines * 8 + 1, PIXEL_SOLID, FG_DARK_BLUE);
		DrawLine(x - 2, y - 2, x - 2, y + nLines * 8 + 1);
		DrawLine(x + nMaxLineLength * 8 + 1, y - 2, x + nMaxLineLength * 8 + 1, y + nLines * 8 + 1);
		DrawLine(x - 2, y - 2, x + nMaxLineLength * 8 + 1, y - 2);
		DrawLine(x - 2, y + nLines * 8 + 1, x + nMaxLineLength * 8 + 1, y + nLines * 8 + 1);

		for (int l = 0; l < vecText.size(); l++)
			DrawBigText(vecText[l], x, y + 1 * 8);
	}

	void RPG_Engine::DrawBigText(string sText, int x, int y)
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

	void RPG_Engine::ChangeMap(string sMapName, float x, float y)
	{
		//Destroy all dynamics
		m_vecDynamics.clear();
		m_vecDynamics.push_back(m_pPlayer);

		//Set current map
		m_pCurrentMap = RPG_Assets::get().GetMap(sMapName);

		//Update player location
		m_pPlayer->fPositionX = x;
		m_pPlayer->fPositionY = y;

		//Create new dynamics from map
		m_pCurrentMap->PopulateDynamics(m_vecDynamics);

	}