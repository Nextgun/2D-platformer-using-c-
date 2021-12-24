
/*
#include "cDynamicCreature.h"
#include "RPG_Assets.h"
#include "olcConsoleGameEngineOOP.h"

class RPG_Engine;

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

void cDynamicCreature::Update(float fElapsedTime)
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

void cDynamicCreature::DrawSelf(olcConsoleGameEngineOOP *gfx, float offsetx, float offsety)
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
	gfx->DrawPartialSprite((fPositionX - offsetx) * 16.0f, (fPositionY - offsety) * 16.0f, m_pSprite, nSheetOffsetX, nSheetOffsetY, 16, 16);
}
*/