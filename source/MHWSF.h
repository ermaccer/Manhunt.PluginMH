#pragma once

#define DEFAULT_SCREEN_WIDTH  ((float)(640))
#define DEFAULT_SCREEN_HEIGHT ((float)(480))
#define DEFAULT_ASPECT_RATIO  (4.0f/3.0f)
#define SCREEN_WIDTH          (GetScrn().fWidth)
#define SCREEN_HEIGHT         (GetScrn().fHeight)
#define SCREEN_ASPECT_RATIO   GetScrnAspectRatio()

#define SCREEN_SCALE_AR(a)    ((a) * DEFAULT_ASPECT_RATIO / SCREEN_ASPECT_RATIO)
#define SCREEN_STRETCH_X(a)   ((a) * GetScrn().fWidthScale)
#define SCREEN_STRETCH_Y(a)   ((a) * GetScrn().fHeightScale)
#define SCREEN_SCALE_X(a)     SCREEN_SCALE_AR(SCREEN_STRETCH_X(a))
#define SCREEN_SCALE_Y(a)     SCREEN_STRETCH_Y(a)

#define SCREEN_SCLX(x) ( SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH * (x)) / SCREEN_WIDTH )

#define SCREEN_WIDTH_4_3 SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH)

#define SCREEN_FC(x)           ( (SCREEN_WIDTH/2 - SCREEN_WIDTH_4_3/2) + SCREEN_SCALE_X((x)) )
#define SCREEN_FR(x)           ( (SCREEN_WIDTH   - SCREEN_WIDTH_4_3  ) + SCREEN_SCALE_X((x)) )
#define SCREEN_FL(x)           (                                         SCREEN_SCALE_X((x)) )
#define SCREEN_FROM_RIGHT(x)   ( SCREEN_FR(DEFAULT_SCREEN_WIDTH * (x)) / SCREEN_WIDTH )
#define SCREEN_FROM_LEFT(x)    ( SCREEN_FL(DEFAULT_SCREEN_WIDTH * (x)) / SCREEN_WIDTH )
#define SCREEN_FROM_CENTER(x)  ( SCREEN_FC(DEFAULT_SCREEN_WIDTH * (x)) / SCREEN_WIDTH )

struct SCRN_T { float fWidth, fHeight, fInvWidth, fInvHeight, fWidthScale, fHeightScale, HudStretch; };

inline SCRN_T &GetScrn()
{
	return *(SCRN_T *)0x7D3440;
}

static float GetScrnAspectRatio()
{
	float stretch = (GetScrn().fHeight / GetScrn().fWidth) / (GetScrn().fHeightScale / GetScrn().fWidthScale);
	return stretch * DEFAULT_ASPECT_RATIO / GetScrn().HudStretch;
}