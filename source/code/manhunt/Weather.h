#pragma once


enum eWeatherTypes {
	CLOUDY,
	WINDY,
	RAINY,
	THUNDER,
	FOGGY,
	CLEAR,
	FREE = -1
};



class CWeather {
public:
	static void	SetWeatherCloudy();
	static void	SetWeatherWindy();
	static void	SetWeatherRainy();
	static void	SetWeatherThunder();
	static void	SetWeatherFoggy();
	static void	SetWeatherClear();
	static void	SetWeatherFree();
};