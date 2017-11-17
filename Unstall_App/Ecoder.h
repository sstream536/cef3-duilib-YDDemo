#pragma once
#include<string>
using std::string;
using std::wstring;

class Ecoder
{
public:
	Ecoder();
	~Ecoder();
	static wstring stringToWstring(const string & str);
	static string wstringToString(const wstring & wstr);
};


