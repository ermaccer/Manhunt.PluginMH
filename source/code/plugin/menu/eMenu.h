#pragma once
#include <vector>
#include <functional>
#include "..\..\manhunt\Vector.h"

struct eMenuPage {
	int         iStart;
	int         iEnd;
};

struct eMenuItem {
	std::string                      name;
	std::string                      strEntity;
	bool                             bIsWeapon;
	bool                             bIsEntity;
	bool                             bIsFunction;
	bool                             bIsCharToggle;
	bool                             bIsShortToggle;
	bool                             bIsIntegerToggle;
	bool                             bIsAdjustable;
	bool                             bIsAdjustableFloat;
	int                              iWeaponID;
	char*                            ptrCharValue;
	short*                           ptrShortValue;
	int*                             ptrIntValue;

	// GEN2: Adjustables
	int                              iStep;
	int                              iAdjustMax;
	int                              iAdjustMin;

	float                            fStep;
	float                            fAdjustMax;
	float                            fAdjustMin;
	float*							 ptrFloatValue;

	std::function<void()>            fFunc;
	// todo: add value items
};

struct eMenuCategory {
	std::string            strName;
	int                    iID;
	bool                   bHasItems;
	bool                   bIsWeapon;
	bool                   bIsEntities;
	std::vector<eMenuItem> vItems;
	std::vector<eMenuItem> vWeapons;
	std::vector<eMenuItem> vEntities;
	std::vector<eMenuPage> vPages;
	bool                   bHasBeenWeaponsPopulated;
	bool                   bHasBeenEntitiesPopulated;
	bool                   bHaveBeenPagesCalculated;
	int                    iPages;
};

class eMenu {
private:
	bool m_bCategoryOpen;
	bool m_bNavigatingCategory;
	bool m_bPressedEnter;
	bool m_bIsHolding;
	bool m_bSelectedOption;

	int  iCurrentItem;
	int  iActualItemID;
	int  iCurrentPage;
	int  iCurrentCategory;
	int  iBaseCategoryID;
	int  iTotalItems;

	std::vector<eMenuItem>     vTempItems;
	std::vector<eMenuPage>     vTempPages;
	std::vector<eMenuItem>     vTempWeapons;
	std::vector<eMenuItem>     vTempEntities;
	std::vector<eMenuCategory> vCategories;
public:

	int m_displayCoords = 0;
	int m_displayRealCoords = 0;
	int m_controllerDebug = 0;
	int m_materialManagerDebug = 0;
	int m_disableLockOnTriangles = 0;
	int m_displayPositionMarker = 0;
	int m_godMode = 0;
	int m_infiniteHealth = 0;
	int m_hideMoon = 0;
	int m_hideStars = 0;
	int m_fallDamage = 1;
	int m_levelTimer = 0;
	int m_silenceWeapons = 0;
	int m_obstructTest = 0;
	int m_displayHunter = 0;

	int m_enableKillCounter = 0;
	int m_infiniteAmmo = 0;


	bool m_active;
	CVector savedPosition;


	// settings
	int  KeyEnableMenu;
	int  KeyMenuExecute;
	int  KeyMenuGoBack;
	int  KeyMenuItemUP;
	int  KeyMenuItemDOWN;
	int  KeyMenuItemLEFT;
	int  KeyMenuItemRIGHT;



	void PreInitialize();
	void Initialize();
	void ProcessMenu();
	void ProcessControls();

	// events

	void OnKeyLeft();
	void OnKeyRight();
	void OnKeyDown();
	void OnKeyUp();
	void OnKeyExecute();
	void OnKeyGoBack();
	void OnKeyToggle();

	void DrawMenu();
	void Clear();


	// menu stuff
	void AddCategory(std::string name, bool isWeapon = false);
	void AddEntitiesCategory(std::string name);
	void AddItem(std::string name, bool isChar, bool isShort, bool isInt, bool isFunc, bool isWeapon, int weapID, char* ptrChar, short* ptrShort, int* ptrInt, std::function<void()> func,
		bool adjInt, int adjStep, int adjMin, int adjMax, bool adjFloat, float fAdjStep, float fAdjMin, float fAdjMax, bool isAnim, std::string strAnim, float* ptrFloat = nullptr); // gen 2 menu

	void AddWeaponEntry(int weaponID);
	void AddEntityEntry(std::string name);
	void AddToggleCharEntry(std::string name, char* ptr);
	void AddToggleIntEntry(std::string name, int* ptr);
	void AddFunctionEntry(std::string name, std::function<void()> func);

	// GEN2

	void AddSliderIntEntry(std::string name, int* ptr, int min, int max, int step = 1);
	void AddSliderFloatEntry(std::string name, float* ptr, float min, float max, float step = 0.1f);
};



std::string GetStatusAsString(int value);
std::string GetAnimationName(int id);
void		SavePosition();
void		LoadPosition();
void        SetDifficultyEasy();
void		SetDifficultyHard();
void		PutBagOnPlayerHead();
void		PlayerDropAllWeapons();
void		PrintEntities();
void		PrintExecuteHunter();


extern eMenu TheMenu;


bool KeyHit(unsigned int keyCode);
bool KeyHitOnce(unsigned int keyCode);