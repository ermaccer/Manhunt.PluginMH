#include "Filenames.h"
#include "core.h"


CString& CFileNames::ms_filenameAllAnims = *(CString*)0x73957C;
CString& CFileNames::ms_filenameAnimFileType = *(CString*)0x739574;
CString& CFileNames::ms_CurrentLevelPath = *(CString*)0x7394A4;
CString& CFileNames::ms_SceneEpPath = *(CString*)0x73975C;
CString& CFileNames::ms_BonusEpPath = *(CString*)0x73977C;
CString& CFileNames::ms_MainEpPath = *(CString*)0x739754;
CString& CFileNames::ms_MaterialBinary= *(CString*)0x7395B4;
CString& CFileNames::ms_CharPlayerTXDFilename = *(CString*)0x739624;
CString& CFileNames::ms_CharPlayerDFFFilename = *(CString*)0x73961C;
CString& CFileNames::ms_CharBunTXDFilename = *(CString*)0x7395E4;
CString& CFileNames::ms_CharBunDFFFilename = *(CString*)0x7395DC;
CString& CFileNames::ms_CharHelTXDFilename = *(CString*)0x7395F4;
CString& CFileNames::ms_CharHelDFFFilename = *(CString*)0x7395EC;
CString& CFileNames::ms_CharPigTXDFilename = *(CString*)0x739604;
CString& CFileNames::ms_CharPigDFFFilename = *(CString*)0x7395FC;	
CString& CFileNames::ms_pathLevels = *(CString*)0x7394A4;

void CFileNames::init()
{
	_DUMMY
}

char * CFileNames::GetMyDocumentsDirectory()
{
	return CallAndReturn<char*, 0x4BE990>();
}
