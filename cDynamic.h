#pragma once

#include "olcConsoleGameEngineOOP.h"

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
	virtual void DrawSelf(olcConsoleGameEngineOOP* gfx, float offsetx, float offsety) {}
	virtual void Update(float fElapsedtime) {}


};

//************************************************

class cDynamic_Teleport : public cDynamic
{
public:
	cDynamic_Teleport(float x, float y, string sMapName, float fTargetX, float fTargetY);
	void DrawSelf(olcConsoleGameEngineOOP* gfx, float fOffsetX, float fOffsetY) override;
	void Update(float fElapsedTime, cDynamic* player = nullptr) override;

public:
	string sMapName;
	float fMapPositionX;
	float fMapPositionY;
};