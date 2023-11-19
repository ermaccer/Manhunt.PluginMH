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
	static CString& ms_CharPlayerTXDFilename;
	static CString& ms_CharPlayerDFFFilename;
	static CString& ms_CharBunTXDFilename;
	static CString& ms_CharBunDFFFilename;
	static CString& ms_CharHelTXDFilename;
	static CString& ms_CharHelDFFFilename;
	static CString& ms_CharPigTXDFilename;
	static CString& ms_CharPigDFFFilename;
	static CString& ms_pathLevels;
    static void init();

	static char* GetMyDocumentsDirectory();
};