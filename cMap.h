#pragma once

#include "olcConsoleGameEngineOOP.h"

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


private:
	int* m_indices = nullptr;
	bool* m_solids = nullptr;

};
