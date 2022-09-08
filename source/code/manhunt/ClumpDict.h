#pragma once
#include "Clump.h"

class CClumpDict {
private:
	char data[1024];
public:
	void Initialise(const char* texture, const char* name);

	CClump* FindClump(const char* name);
	CClump* FindClumpDescription(const char* name);
	void	Destroy();

	int CheckDict();

	int sub_59B860(const char* name);

};