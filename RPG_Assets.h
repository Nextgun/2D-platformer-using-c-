#pragma once

#include "olcConsoleGameEngineOOP.h"

#include<map>
class RPG_Assets
{
public:
	static RPG_Assets& get()
	{
		static RPG_Assets me;
		return me;
	}
	
	RPG_Assets(RPG_Assets const&) = delete;
	void operator=(RPG_Assets const&) = delete;

	olcSprite* GetSprite(string name)
	{
		return m_mapSprites[name];
	}
	
	void LoadSprites();

private:
	RPG_Assets();
	~RPG_Assets();
	
	map<string, olcSprite*> m_mapSprites;
}; 
