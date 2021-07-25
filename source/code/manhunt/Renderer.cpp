#include "Renderer.h"
#include "core.h"

void CRenderer::PushRenderStateBlend()
{
	Call<0x5F5CF0>();
}


void CRenderer::PushAndSetRenderState(RwRenderState state, void* value)
{
	Call<0x5F5E60, RwRenderState, void*>(state, value);
}

void CRenderer::RenderStateSetBlend(RwBlendFunction state, RwBlendFunction value)
{
	Call<0x5F5C90, RwBlendFunction, RwBlendFunction>(state, value);
}

void CRenderer::SetIngameInfoRenderStates(int value)
{
	Call<0x5F5A80, int>(value);
}

void CRenderer::PopRenderStateAll()
{
	Call<0x5F5E10>();
}

void CRenderer::PopRenderStateBlend()
{
	Call<0x5F5D30>();
}

void CRenderer::DrawQuad2d(float posX, float posY, float scaleX, float scaleY, int red, int green, int blue, int alpha, int pTexture)
{
	Call<0x5F96F0, float, float, float, float, int, int, int, int, int>(posX, posY, scaleX, scaleY, red, green, blue, alpha, pTexture);
}

void CRenderer::DrawQuad2dSet(float posX, float posY, float scaleX, float scaleY, int r1, int r2, int r3, int r4)
{
	Call<0x5F8470, float, float, float, float, int, int, int, int>(posX, posY, scaleX, scaleY, r1, r2, r3, r4);
}

void CRenderer::DrawRasterLineFX(int a1, int a2, int a3, int a4)
{
	Call<0x5FA6F0, int,int,int,int>(a1,a2,a3,a4);
}
