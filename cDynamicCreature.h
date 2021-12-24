/*
#pragma once

#include "RPG_Assets.h"
#include "olcConsoleGameEngineOOP.h"



class cDynamicCreature : public cDynamicCreature
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
	void Update(float fElapsedTime, cDynamic* player = nullptr) override;

};

*/