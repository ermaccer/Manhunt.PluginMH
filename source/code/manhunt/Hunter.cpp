#include "Hunter.h"
#include "core.h"

bool CHunter::AmIRamirez()
{
	return CallMethodAndReturn<bool, 0x4B2F40, CHunter*>(this);
}

bool CHunter::AmIPiggsy()
{
	return CallMethodAndReturn<bool, 0x4B2F20, CHunter*>(this);
}

bool CHunter::AmIStarkweather()
{
	return CallMethodAndReturn<bool, 0x4B2F60, CHunter*>(this);
}
