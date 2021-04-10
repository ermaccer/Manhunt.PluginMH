#pragma once
#include "String.h"

class CFileNames {
public:
	static CString& ms_filenameAllAnims;
	static CString& ms_filenameAnimFileType;
	static CString& ms_CurrentLevelPath;
	static CString& ms_SceneEpPath;
	static CString& ms_BonusEpPath;
	static CString& ms_MainEpPath;
	static CString& ms_MaterialBinary;
	static char*&     ms_pathLevels;
    static void init();

	static char* GetMyDocumentsDirectory();
};