#include "Text.h"
#include "..\manhunt\core.h"

wchar_t * CText::GetFromKey16(const char * key)
{
	return CallMethodAndReturn<wchar_t*, 0x4937E0, int, const char*>(0x725A38, key);
}
