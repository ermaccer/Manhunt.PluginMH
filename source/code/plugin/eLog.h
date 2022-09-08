#pragma once


class eLog {
public:
	static wchar_t path[260];

	static void Initialise();
	static void Message(char* function, char* format, ...);
	static void ErrorMsg(char* function, char* format, ...);
};