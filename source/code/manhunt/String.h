#pragma once

struct CString
{
	char *str;
	short len;
	short cap;

	CString();
	void __as(CString* src, CString* dest);
};
