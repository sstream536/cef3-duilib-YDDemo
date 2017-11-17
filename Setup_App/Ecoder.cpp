#include <Windows.h>
#include "Ecoder.h"
#include <tchar.h>
Ecoder::Ecoder()
{
}


Ecoder::~Ecoder()
{
}


wstring Ecoder::stringToWstring(const string & str)
{
	LPCSTR pszSrc = str.c_str();
	int nLen = MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, NULL, 0);
	if (nLen == 0){
		return wstring(L"");
	}

	wchar_t* pwszDst = new wchar_t[nLen];
	if (!pwszDst){
		return wstring(L"");
	}

	MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pwszDst, nLen);
	std::wstring wstr(pwszDst);
	delete[] pwszDst;
	pwszDst = NULL;
	return wstr;
}

string Ecoder::wstringToString(const wstring & wstr)
{
	LPCWSTR pwszSrc = wstr.c_str();
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen == 0){
		return string("");
	}

	char* pszDst = new char[nLen];
	if (!pszDst){
		return string("");
	}

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	string str(pszDst);
	delete[] pszDst;
	pszDst = NULL;

	return str;
}