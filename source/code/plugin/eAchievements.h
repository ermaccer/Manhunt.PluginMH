#pragma once

enum eAchivementID
{
	ACHIEVEMENT_HE_NEVER_SAW_IT_COMING,
	ACHIEVEMENT_5_STAR_KILLER,
	ACHIEVEMENT_DRUG_FREE_IS_THE_WAY_TO_BE,
	ACHIEVEMENT_BANG_BANG_BOOM,
	ACHIEVEMENT_NO_CRANE_NO_GAIN
};

class eAchievements
{
public:
	static bool m_bIsTransitionDone;
	static bool m_bWantsToPlayUnlock;
	static float m_faStartY;
	static float m_fStartY;
	static int   m_nAlpha;

	static void Start();
	static void PlaySlider();
};

