#pragma once

struct CString
{
	char *str;
	short len;
	short cap;

	CString();
	CString(const char* text);
	~CString();

	void __as(CString* src, CString* dest);

	bool Identical(const char* text);
};
