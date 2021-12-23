#include "cMap.h"

#include <fstream>

cMap::cMap()
{
	nWidth = 0;
	nHeight = 0;
	pSprite = nullptr;
	m_indices = nullptr;
	m_solids = nullptr;
}

cMap::~cMap()
{
	delete[] m_indices;
	delete[] m_solids;
}

int cMap::GetIndex(int x, int y)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		return m_indices[y * nWidth + x];
	else
		return 0;
}

bool cMap::GetSolid(int x, int y)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		return m_solids[y * nWidth + x];
	else
		return 0;
}

bool cMap::Create(string fileData, olcSprite* sprite, string name)
{
	sName = name;
	pSprite = sprite;

	ifstream data(fileData, ios::in | ios::binary);
	if (data.is_open())
	{
		data >> nWidth >> nHeight;
		m_indices = new int[nWidth * nHeight];
		m_solids = new bool[nWidth * nHeight];
		for (int i = 0; i < nWidth * nHeight; i++)
		{
			data >> m_indices[i];
			data >> m_solids[i];
		}
			return true;
	}
	
	return false;
}

cMap_Village1::cMap_Village1()
{
	Create("rpgdata/map/village1.lvl", RPG_Assets::get().GetSprite("village"), "coder town");
}

cMap_Village2::cMap_Village2()
{
	Create("rpgdata/map/village2.lvl", RPG_Assets::get().GetSprite("village"), R"(bug town)");
}

