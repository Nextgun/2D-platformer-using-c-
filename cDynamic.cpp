#include "cDynamic.h"
#include "RPG_Engine.h"

cDynamic::cDynamic(string name)
{
	sName = name; 
	fPositionX = 0.0f;
	fPositionY = 0.0f;
	fVelocityX = 0.0f;
	fVelocityY = 0.0f;
	bSolidVsMap = true;
	bSolidVsDynamic = true;
	bFreindly = true;
}

cDynamic::~cDynamic()
{

}

//***************************************

cDynamicCreature::cDynamicCreature(string name, olcSprite* sprite) : cDynamic(name)
{
	m_pSprite = sprite;
	nHealth = 10;
	nHealthMax = 10;
	m_nFacingDirection = SOUTH;
	m_nGraphicState = STANDING;
	m_fTimer = 0.0f;
	m_nGraphicCounter = 0;
}

void cDynamicCreature::Update(float fElapsedTime, cDynamic* player)
{
	m_fTimer += fElapsedTime;

	if (m_fTimer >= 0.2f)
	{
		m_fTimer -= 0.2f;
		m_nGraphicCounter++;
		m_nGraphicCounter %= 2;
	}
	if (fabs(fVelocityX) > 0 || fabs(fVelocityY) > 0)
		m_nGraphicState = WALKING;
	else
		m_nGraphicState = STANDING;

	if (nHealth <= 0)
		m_nGraphicState = DEAD;

	if (fVelocityX < 0.0f) m_nFacingDirection = WEST;
	if (fVelocityX > 0.0f) m_nFacingDirection = EAST;
	if (fVelocityY < -0.0f) m_nFacingDirection = NORTH;
	if (fVelocityY > 0.0f) m_nFacingDirection = SOUTH;
}

	void cDynamicCreature::DrawSelf(olcConsoleGameEngineOOP * gfx, float offsetX, float offsetY)
	{
		int nSheetOffsetX = 0;
		int nSheetOffsetY = 0;

		switch (m_nGraphicState)
		{
		case STANDING:
			nSheetOffsetX = m_nFacingDirection * 16;
			break;

		case WALKING:
			nSheetOffsetX = m_nFacingDirection * 16;
			nSheetOffsetY = m_nGraphicCounter * 16;
			break;

		case CELEBRATING:
			nSheetOffsetX = 4 * 16;
			break;

		case DEAD:
			nSheetOffsetX = 4 * 16;
			nSheetOffsetY = 1 * 16;
			break;
		}
		// uses pointer variable to allow the 
		// dynamic creature to draw itself onto 
		// the screen
		gfx->DrawPartialSprite((fPositionX - offsetX) * 16.0f, (fPositionY - offsetY) * 16.0f, m_pSprite, nSheetOffsetX, nSheetOffsetY, 16, 16);
	}


//**************************************
cDynamic_Teleport::cDynamic_Teleport(float x, float y, string mapName, float fTargetPosX, float fTargetPosY) : cDynamic("Teleport")
{
	fPositionX = x;
	fPositionY = y;
	fMapPositionX = fTargetPosX;
	fMapPositionY = fTargetPosY;
	bSolidVsDynamic = false;
	bSolidVsMap = false;
}

void cDynamic_Teleport::DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy)
{
	// Does Nothing
	gfx->DrawCircle(((fPositionX + 0.5f) - ox) * 16.0f, ((fPositionY + 0.5f) - oy) * 16.0f, 0.5f * 16.0f); // For debugging
}


void cDynamic_Teleport::Update(float fElapsedTime, cDynamic* player)
{
	// does nothing
}
