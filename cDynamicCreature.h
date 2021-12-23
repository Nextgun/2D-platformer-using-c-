#pragma once

#include "cDynamic.h"

class cDynamicCreature : public cDynamic
{
public:
	cDynamicCreature(string name, olcSprite* sprite);

protected:
	olcSprite* m_pSprite;
	float m_fTimer;
	int m_nGraphicCounter = 0;
	enum { SOUTH = 0, WEST = 1, NORTH = 2, EAST = 3 } m_nFacingDirection;
	enum { STANDING, WALKING, CELEBRATING, DEAD } m_nGraphicState;

public:
	int nHealth;
	int nHealthMax;
	

public:
	void DrawSelf(olcConsoleGameEngineOOP* gfx, float offsetx, float offsety) override;
	void Update(float fElapsedtime) override;

};

