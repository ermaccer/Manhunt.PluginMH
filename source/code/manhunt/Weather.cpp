#include "Weather.h"
#include "core.h"


void CWeather::SetWeatherCloudy()
{
	Call<0x5B0AC0>();
}

void CWeather::SetWeatherWindy()
{
	Call<0x5B0AE0>();
}

void CWeather::SetWeatherRainy()
{
	Call<0x5B0B00>();
}

void CWeather::SetWeatherThunder()
{
	Call<0x5B0B20>();
}

void CWeather::SetWeatherFoggy()
{
	Call<0x5B0B40>();
}

void CWeather::SetWeatherClear()
{
	Call<0x5B0B60>();
}

void CWeather::SetWeatherFree()
{
	Call<0x5B0B80>();
}
