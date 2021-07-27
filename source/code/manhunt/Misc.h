#pragma once
// unknown file functions
#include <rwcore.h>
#include <rpworld.h>
#include <rwplcore.h>
struct CFile {
	int m_nLastMode;
	int m_nLastFileMode;
	int field8;
	int field12; // unused? in most cases set to 0
	int m_nBufferSize;
	int m_pFilePointer;
	int field24;
	int field28;
	int field32; // always 1?
};


RwTexDictionary* TexDictLoad(const char *path);