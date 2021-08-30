#pragma once

class CScriptLoader {
public:

	static int LoadScriptFile(const char* file);
};

class CScriptVM {
public:
	int   field0;
	char  pad[28];
	int	  m_returnValue;
	char  _pad[1092];
	int   m_commandID;
	char  __pad[28];
	int   m_hogProcessorValue;

	int		PopInt();
	char*	PopCharStar();
};