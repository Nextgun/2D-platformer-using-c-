#include "cDynamic.h"

cDynamic::cDynamic(string name)
{
	sName = name; 
	fPositionX = 0.0f;
	fPositionY = 0.0f;
	fVelocityX = 0.0f;
	fVelocityY = 0.0f;
	bSolidVsMap = true;
	bSolidVsDynamic = true;
	bFreindly = true;
}

cDynamic::~cDynamic()
{

}

//***************************************

cDynamic_Teleport::cDynamic_Teleport(float x, float y, string sMapName, float fTargetX, float fTargetY)
{
	fPositionX = fPositionX;
	fPositionY = fPositionY;
	fMapPositionX = fTargetX;
	fMapPositionY = fTargetY;
	bSolidVsDynamic = false;
	bSolidVsMap = false;
}

void cDynamic_Teleport::DrawSelf(olcConsoleGameEngineOOP* gfx, float fOffsetX, float fOffsetY)
{
	// does nothing
	gfx->DrawCircle(((fPositionX + 0.5f) - fOffsetX) * 16.0f, ((fPositionY + 0.5) - fOffsetY) * 16.0f, 0.5f * 16.0f);
}

void cDynamic_Teleport::Update(float fElapsedTime, cDynamic* player)
{
	// does nothing
}
