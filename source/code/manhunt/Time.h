#pragma once

class CGameTime {
public:
	static int& ms_startRealTime;
	static int& ms_realTimeOffset;
	static int& ms_currGameTime;
	static int& ms_currGameTimePaused;
	static int& ms_timeStep;
	static int& ms_currFrame;
	static void Update();
};