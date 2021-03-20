#pragma once
#include <string>
#include <fstream>

std::streampos getSizeToEnd(std::ifstream& is);
bool checkSlash(std::string& str, bool first = false);
bool wcheckSlash(std::wstring& str, bool first = false);
std::string getWideStr(std::ifstream &file, bool f = false);
std::wstring getWideString(std::ifstream &file);
std::string convertWide(std::string& str);
std::string convertWideToChar(std::wstring& str);
std::string splitString(std::string& str, bool file);
std::wstring wsplitString(std::wstring& str, bool file);
int calcOffsetFromPad(int val, int padsize);
std::wstring getExecutablePath();
std::string  getExecutablePath_str();
std::string  getExtension(std::string& str);