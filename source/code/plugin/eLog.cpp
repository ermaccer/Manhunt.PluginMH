#include "eLog.h"
#include "..\core\eSettingsManager.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

wchar_t eLog::path[260];

void eLog::Initialise()
{
	if (!eSettingsManager::bEnableLog)
		return;


	GetModuleFileNameW(NULL, path, sizeof(path));

	wchar_t* end = wcsrchr(path, L'\\');
	if (end) 
		end[1] = 0x00;
	wcscat(path, L"pluginmh_log.txt");

	FILE* cls = _wfopen(path, L"w");
	fclose(cls);
	FILE* log = _wfopen(path, L"a+");
	time_t ttime = time(0);
	fprintf(log, "Logging Started - %s", ctime(&ttime));
	fclose(log);

}

void eLog::Message(char* function, char* format, ...)
{
	if (!eSettingsManager::bEnableLog)
		return;

	char msg[2048];

	va_list args;
	va_start(args, format);
	wvsprintf(msg, format, args);
	va_end(args);

	FILE* log = _wfopen(path, L"a+");

	if (log)
	{
		fprintf(log, "%s | %s\n",function,  msg);
		fclose(log);
	}

}

void eLog::ErrorMsg(char* function, char* format, ...)
{
	char msg[2048];

	va_list args;
	va_start(args, format);
	wvsprintf(msg, format, args);
	va_end(args);

	MessageBoxA(0, msg, 0, MB_ICONERROR);
}
