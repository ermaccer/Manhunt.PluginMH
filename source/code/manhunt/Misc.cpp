#include "Misc.h"
#include "core.h"

RwTexDictionary * TexDictLoad(const char * path)
{
	return CallAndReturn<RwTexDictionary*, 0x4777D0, const char*>(path);
}
