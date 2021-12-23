#include "cDynamic.h"

cDynamic::cDynamic(string name)
{
	sName = name; 
	px = 0.0f;
	py = 0.0f;
	vx = 0.0f;
	vy = 0.0f;
	bSolidVsMap = true;
	bSolidVsDyn = true;
	bFreindly = true;
}

cDynamic::~cDynamic()
{

}