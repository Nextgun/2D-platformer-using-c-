#pragma once

#include "RPG_Assets.h"
#include "olcConsoleGameEngineOOP.h"

class RPG_Engine;


class cDynamic
{
public:
	cDynamic(string name);
	~cDynamic();

public:
	float fPositionX, fPositionY;
	float fVelocityX, fVelocityY;
	bool bSolidVsMap;
	bool bSolidVsDynamic;
	bool bFreindly;
	string sName;

public:
	virtual void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) {}
	virtual void Update(float fElapsedTime, cDynamic* player = nullptr) {}
	

};


//************************************************

class cDynamicCreature : public cDynamic
{
public:
	cDynamicCreature(string n, olcSprite* sprite);

protected:
	olcSprite* m_pSprite;
	float m_fTimer;
	int m_nGraphicCounter;
	enum { SOUTH = 0, WEST = 1, NORTH = 2, EAST = 3 } m_nFacingDirection;
	enum { STANDING, WALKING, CELEBRATING, DEAD } m_nGraphicState;

public:
	int nHealth;
	int nHealthMax;

public:
	void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;
	void Update(float fElapsedTime, cDynamic* player = nullptr) override;
};


class cDynamic_Teleport : public cDynamic
{
public:
	cDynamic_Teleport(float x, float y, string sMapName, float targetX, float targetY);
	void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;
	void Update(float fElapsedTime, cDynamic* player = nullptr) override;

public:
	string sMapName;
	float fMapPositionX;
	float fMapPositionY;
};