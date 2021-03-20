#include "Filenames.h"
#include "core.h"


CString& CFileNames::ms_filenameAllAnims = *(CString*)0x73957C;
CString& CFileNames::ms_filenameAnimFileType = *(CString*)0x739574;
CString& CFileNames::ms_CurrentLevelPath = *(CString*)0x7394A4;
CString& CFileNames::ms_SceneEpPath = *(CString*)0x73975C;
CString& CFileNames::ms_BonusEpPath = *(CString*)0x73977C;
CString& CFileNames::ms_MainEpPath = *(CString*)0x739754;
char*& CFileNames::ms_pathLevels = *(char**)0x756034;
void CFileNames::init()
{
	_DUMMY
}

char * CFileNames::GetMyDocumentsDirectory()
{
	return CallAndReturn<char*, 0x4BE990>();
}
