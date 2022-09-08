#include "eAchievements.h"
#include "../manhunt/Frontend.h"
#include "../manhunt/Renderer.h"
#include "../manhunt/Collectable.h"
#include "../manhunt/core.h"

bool eAchievements::m_bIsTransitionDone = false;
float eAchievements::m_faStartY = -0.03f;
float eAchievements::m_fStartY = 0.0f;
int	  eAchievements::m_nAlpha = 255;
bool  eAchievements::m_bWantsToPlayUnlock = false;

void eAchievements::Start()
{
	m_fStartY = 0.0f;
	m_nAlpha = 255;
	m_faStartY = -0.03f;
	m_bWantsToPlayUnlock = true;
	m_bIsTransitionDone = false;
}

void eAchievements::PlaySlider()
{
	if (!CFrontend::m_gameIsRunning)
		return;
	float arScale = ((4.0f/ 3.0f) / CFrontend::GetAspectRatio());
	char* atext_str = "ACHIEVEMENT UNLOCKED";
	char* text_str = "ACHIEVEMENT NAME";

	const float achievementSize = 0.6f;
	const float textSize = 0.4f;

	float x_pos = 0.5f;

	if (!m_bIsTransitionDone)
	{
		m_faStartY += 0.001f;
		m_fStartY += 0.001f;
	}


	if (m_fStartY >= 0.07f && m_faStartY >= 0.06f)
	{
		m_bIsTransitionDone = true;
	}

	if (m_bIsTransitionDone)
	{
		m_nAlpha -= 1;
		if (m_nAlpha < 0)
			m_nAlpha = 0;
	}

	{
		float afinal_x = x_pos - CFrontend::CalculateTextLen8(atext_str, achievementSize, 1) * x_pos;
		CFrontend::SetDrawRGBA(0,0,0, m_nAlpha);
		CFrontend::Print8(atext_str, afinal_x + 0.005f, m_faStartY + 0.005f, achievementSize, achievementSize, 0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(160, 160, 255, m_nAlpha);
		CFrontend::Print8(atext_str, afinal_x, m_faStartY, achievementSize, achievementSize, 0, FONT_TYPE_DEFAULT);
	}
	{
		float final_x = x_pos - CFrontend::CalculateTextLen8(text_str, textSize, 1) * x_pos;
		CFrontend::SetDrawRGBA(0,0,0, m_nAlpha);
		CFrontend::Print8(text_str, final_x + 0.005f, m_fStartY + 0.005f, textSize, textSize, 0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, m_nAlpha);
		CFrontend::Print8(text_str, final_x, m_fStartY, textSize, textSize, 0, FONT_TYPE_DEFAULT);
	}

	{

		CRenderer::DrawQuad2d(0.225f * arScale, m_faStartY, 0.06f * arScale, 0.10f, 255, 255, 255, m_nAlpha, *(int*)(CallAndReturn<int, 0x5DF9A0, int, int>(CT_GLOCK, 0)));
	}

	if (m_nAlpha <= 0)
		m_bWantsToPlayUnlock = false;
}
