#include "UnInstall.h"
#include <Windows.h>
#include "Ecoder.h"
#include "resource.h"
#include <direct.h> 
#include <Shobjidl.h>
#include <Shlobj.h>
#include <TCHAR.H>
#include <stdlib.h>
#include <shellapi.h>


#pragma comment(lib, "shell32.lib")

UnInstall::UnInstall()
{
}


UnInstall::~UnInstall()
{
}

bool UnInstall::unInstall(){

	if (!deleteRegKey()){
	//	return false;
	}
	wchar_t buf[512];
	GetModuleFileName(NULL, buf, 512);
	process_fun(20, "");
	Sleep(500);
	std::string exe_path = Ecoder::wstringToString(buf);
	int pos = exe_path.rfind("\\");
	exe_path = exe_path.substr(0, exe_path.length() - (exe_path.length() - pos));
	//
	process_fun(40, "");
	Sleep(500);
	if (!deleteDirFile(exe_path.c_str())){
	//	return false;
	}
	process_fun(55, "");
	Sleep(300);
	wchar_t sz_path[1024];
	std::wstring str;
	if (::SHGetSpecialFolderPath(NULL, sz_path, CSIDL_DESKTOPDIRECTORY, FALSE)){
		str = sz_path;
		str += Ecoder::stringToWstring("\\YDDemo.lnk");
	}
	process_fun(60, "");
	Sleep(300);
	if (!DeleteFile(str.c_str())){
		//return false;
	}
	wchar_t sz_path_[1024];
	process_fun(70, "");
	Sleep(300);
	if (::SHGetSpecialFolderPath(NULL, sz_path_, CSIDL_STARTMENU, FALSE)){
		str.clear(); 
		str = sz_path_;
		str += Ecoder::stringToWstring("\\³ÌÐò\\YDDemo");
	}
	process_fun(80, "");
	Sleep(300);
	if (!deleteDirFile(Ecoder::wstringToString(str).c_str())){
		//return false;
	}
	process_fun(85, "");
	Sleep(300);
	process_fun(90, "");
	Sleep(300);

	deleteApplicationSelf();
	return true;
}

bool UnInstall::deleteRegKey(){
	HKEY hKey = HKEY_LOCAL_MACHINE;
	wchar_t szSubKey[] = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\YDDemo";

	if (ERROR_SUCCESS == RegDeleteKey(hKey, szSubKey)){
		return TRUE;
	}
	HKEY hSubKey;
	if (RegOpenKeyEx(hKey, szSubKey, 0, KEY_WRITE | KEY_READ, &hSubKey) != ERROR_SUCCESS){
		return false;
	}
	DWORD dwIndex = 0;
	long lResult;
	wchar_t szName[100];
	DWORD cbName = 100;
	lResult = RegEnumKeyEx(hSubKey, dwIndex, szName, &cbName, 0, NULL, NULL, NULL);

	while (lResult == ERROR_SUCCESS && lResult != ERROR_MORE_DATA){
		RegDeleteKey(hSubKey, szName);
		cbName = 100; 
		lResult = RegEnumKeyEx(hSubKey, dwIndex, szName, &cbName, 0, NULL, NULL, NULL);
	}
	RegCloseKey(hSubKey);
	RegDeleteKey(hKey, szSubKey);

	return true;
}

bool UnInstall::deleteDirFile(const std::string & path)
{
	std::string strDir = path;
	if (strDir.at(strDir.length() - 1) != '\\');
	strDir += '\\';
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(Ecoder::stringToWstring((strDir + "*.*")).c_str(), &wfd);
	if (hFind == INVALID_HANDLE_VALUE){
		return false;
	}	
	do{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			if (stricmp(Ecoder::wstringToString(wfd.cFileName).c_str(), ".") != 0 &&
				stricmp(Ecoder::wstringToString(wfd.cFileName).c_str(), "..") != 0)
				deleteDirFile((strDir + Ecoder::wstringToString(wfd.cFileName).c_str()).c_str());
		}
		else{
			DeleteFile((Ecoder::stringToWstring(strDir) + wfd.cFileName).c_str());
		}
	} while (FindNextFile(hFind, &wfd));
	FindClose(hFind);
	RemoveDirectory(Ecoder::stringToWstring(path).c_str());
	
	return true;
}

bool UnInstall::deleteApplicationSelf()
{
	char szCommandLine[MAX_PATH + 10];
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, _pgmptr, NULL);
	sprintf(szCommandLine, "/c del /q %s", _pgmptr);

	ShellExecute(NULL, L"open", L"cmd.exe", Ecoder::stringToWstring(szCommandLine).c_str(), NULL, SW_HIDE);
	ExitProcess(0);
	return true;
}