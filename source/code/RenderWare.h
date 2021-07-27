#pragma once
#include <rwcore.h>
#include <rwplcore.h>
#include <rpworld.h>
#include <math.h>

#define PI       3.14159265358979323846 

#define RwEngineInstance (*(RwGlobals **)0x82279C)
#define DEGTORAD(x) ((x)* PI / 180.0f)

#define SCREEN_VIEWWINDOW (tanf(DEGTORAD(45.0f * 0.5f)))

RpClump* RpClumpRender(RpClump* clump);


void CameraSize(RwCamera * camera, RwRect * rect, RwReal viewWindow, RwReal aspectRatio);