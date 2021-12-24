#pragma once

#include "olcConsoleGameEngineOOP.h"
#include "RPG_Assets.h"
#include "cDynamic.h"
#include "RPG_Commands.h"
class cMap
{
public:
	cMap();
	~cMap();

public:
	int nWidth;
	int nHeight;
	string sName;
	olcSprite* pSprite;

	int GetIndex(int x, int y);
	bool GetSolid(int x, int y);
	bool Create(string fileData, olcSprite* sprite, string name);

	virtual bool PopulateDynamics(vector<cDynamic*>& vDynamics)
	{
		return false;
	}

private:
	int* m_indices = nullptr;
	bool* m_solids = nullptr;

};

class cMap_Village1 : public cMap
{
public:
	cMap_Village1();

	bool PopulateDynamics(vector<cDynamic*> &vDynamics) override;

};

class cMap_Home1 : public cMap
{
public:
	cMap_Home1();

	bool PopulateDynamics(vector<cDynamic*>& vDynamics) override;

};
