#pragma once

#include <iostream>
#include <string>
#include <memory.h>
#include <algorithm>
using namespace std;

#include "olcConsoleGameEngineOOP.h"

#include "RPG_Assets.h"
#include "cMap.h"
#include "cDynamic.h"
#include "RPG_Commands.h"

#define X(n) m_script.AddCommand(new cCommand_ ## n)


class RPG_Engine : public olcConsoleGameEngineOOP
{
public:
	RPG_Engine();

private:
	cMap* m_pCurrentMap = nullptr;
	cDynamic* m_pPlayer = nullptr;
	vector<cDynamic*> m_vecDynamics;
	cScriptProcessor m_script;

	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

	//Sprite Resources
	olcSprite* m_sprFont = nullptr;

protected:
	virtual bool OnUserCreate() override;
	virtual bool OnUserUpdate(float fElapsedTime) override;
	
protected:
	vector<string> m_vecDialogToShow;
	bool m_bShowDialog = false;
	float m_fDialogX = 0.0f;
	float m_fDialogY = 0.0f;

public:
	void ShowDialog(vector<string> vecLines);
	void DisplayDialog(vector<string> vecText, int x, int y);
	void DrawBigText(string sText, int x, int y);
	void ChangeMap(string sMapName, float x, float y);
	
};
