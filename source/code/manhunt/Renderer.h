#pragma once
#include <rwcore.h>
#include <rpworld.h>

class CRenderer {
public:
	static void PushRenderStateBlend();
	static void PushAndSetRenderState(RwRenderState state, void* value);
	static void RenderStateSetBlend(RwBlendFunction state, RwBlendFunction value);
	static void SetIngameInfoRenderStates(int value);
	static void PopRenderStateAll();
	static void PopRenderStateBlend();
	static void DrawQuad2d(float posX, float posY, float scaleX, float scaleY, int red, int green, int blue, int alpha, int pTexture);
	static void DrawQuad2dSet(float posX, float posY, float scaleX, float scaleY, int r1,int r2, int r3, int r4);
	static void DrawRasterLineFX(int a1, int a2, int a3, int a4);
};