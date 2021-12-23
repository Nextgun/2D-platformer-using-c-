#pragma once

#include "olcConsoleGameEngineOOP.h"

class cDynamic
{
public:
	cDynamic(string name);
	~cDynamic();

public:
	float px, py;
	float vx, vy;
	bool bSolidVsMap;
	bool bSolidVsDyn;
	bool bFreindly;
	string sName;

public:
	virtual void DrawSelf(olcConsoleGameEngineOOP* gfx, float offsetx, float offsety) {}
	virtual void Update(float fElapsedtime) {}


};

