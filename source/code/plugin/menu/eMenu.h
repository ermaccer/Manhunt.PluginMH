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
	std::string                      strAnim;
	bool                             bIsWeapon;
	bool                             bIsAnim;
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

	std::function<void()>            fFunc;
	// todo: add value items
};

struct eMenuCategory {
	std::string            strName;
	int                    iID;
	bool                   bHasItems;
	bool                   bIsWeapon;
	bool                   bIsAnims;
	std::vector<eMenuItem> vItems;
	std::vector<eMenuItem> vWeapons;
	std::vector<eMenuItem> vAnims;
	std::vector<eMenuPage> vPages;
	bool                   bHasBeenWeaponsPopulated;
	bool                   bHasBeenAnimsPopulated;
	bool                   bHaveBeenPagesCalculated;
	int                    iPages;
};

class eMenu {
private:
	bool bCategoryOpen;
	bool bNavigatingInCategory;
	bool bPressedEnter;
	bool bIsHoldingMenu;

	int  iCurrentItem;
	int  iActualItemID;
	int  iCurrentPage;
	int  iCurrentCategory;
	int  iBaseCategoryID;
	int  iTotalItems;

	std::vector<eMenuItem>     vTempItems;
	std::vector<eMenuPage>     vTempPages;
	std::vector<eMenuItem>     vTempWeapons;
	std::vector<eMenuItem>     vTempAnims;
	std::vector<eMenuCategory> vCategories;
public:
	bool bDisplayMenu;
	CVector savedPosition;


	// settings
	int  KeyEnableMenu;
	int  KeyQuickCameraMain;
	int  KeyQuickCameraSub;
	int  KeyQuickCameraTeleport;
	int  KeyMenuExecute;
	int  KeyMenuGoBack;
	int  KeyMenuItemUP;
	int  KeyMenuItemDOWN;
	int  KeyMenuItemLEFT;
	int  KeyMenuItemRIGHT;



	void PreInitialize();
	void Initialize();
	void ProcessMenu();
	void ProcessToggle();
	void ProcessControls();

	void DrawMenu();
	void ProcessEnter();
	void Clear();


	// menu stuff
	void AddCategory(std::string name, bool isWeapon = false);
	void AddAnimsCategory(std::string name);
	void AddItem(std::string name, bool isChar, bool isShort, bool isInt, bool isFunc, bool isWeapon, int weapID, char* ptrChar, short* ptrShort, int* ptrInt, std::function<void()> func,
		bool adjInt, int adjStep, int adjMin, int adjMax, bool adjFloat, float fAdjStep, float fAdjMin, float fAdjMax, bool isAnim, std::string strAnim); // gen 2 menu

	void AddWeaponEntry(int weaponID);
	void AddAnimEntry(std::string name);
	void AddToggleCharEntry(std::string name, char* ptr);
	void AddToggleIntEntry(std::string name, int* ptr);
	void AddFunctionEntry(std::string name, std::function<void()> func);

	// GEN2

	void AddSliderIntEntry(std::string name, int* ptr, int min, int max, int step = 1);

};



std::string GetStatusAsString(int value);
std::string GetAnimationName(int id);
void		SavePosition();
void		LoadPosition();
void        SetDifficultyEasy();
void		SetDifficultyHard();


extern eMenu TheMenu;


bool KeyHit(unsigned int keyCode);
