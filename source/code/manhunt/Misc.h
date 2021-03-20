#pragma once
// unknown file functions

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


CFile* Rockstar_fopen(int mode, int fMode, char* extraParam);
int    ReadFileBytes(CFile* src, int dst, int size);