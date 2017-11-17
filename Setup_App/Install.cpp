#include "Install.h"
#include <Windows.h>
#include "Ecoder.h"
#include "resource.h"
#include <direct.h> 
#include <Shobjidl.h>
#include <Shlobj.h>
#include <TCHAR.H>
#include "SysFileWrapper.h"

Install::Install():
m_stop(false){
}


Install::~Install(){
}

bool Install::install(const std::string & install_path, bool is_shortcut){
	bool res;
	std::string file_tmp_path;
	size_t all_file_size = 85136949, inc = 0;
	m_install_path = install_path;
	file_tmp_path = install_path + "\\YDDemo.exe";
	res = releaseRes(file_tmp_path, (WORD)IDR_YDDemo, "EXE");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc)/ all_file_size * 100), "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path + "\\Unstall_App.exe";
	res = releaseRes(file_tmp_path, (WORD)IDR_Unstall_App, "EXE");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path + "\\debug.log";
	res = releaseRes(file_tmp_path, (WORD)IDR_debug, "LOG");
	if (!res){
		return FALSE;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path + "\\icudtl.dat";
	res = releaseRes(file_tmp_path, (WORD)IDR_icudtl, "DAT");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path + "\\natives_blob.bin";
	res = releaseRes(file_tmp_path, (WORD)IDR_natives_blob, "BIN");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path + "\\snapshot_blob.bin";
	res = releaseRes(file_tmp_path, (WORD)IDR_snapshot_blob, "BIN");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path + "\\cef.pak";
	res = releaseRes(file_tmp_path, (WORD)IDR_cef, "APK");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path + "\\cef_100_percent.pak";
	res = releaseRes(file_tmp_path, (WORD)IDR_cef_100_percent, "APK");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path + "\\cef_200_percent.pak";
	res = releaseRes(file_tmp_path, (WORD)IDR_cef_200_percent, "APK");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	file_tmp_path = install_path + "\\cef_extensions.pak";
	res = releaseRes(file_tmp_path, (WORD)IDR_cef_extensions, "APK");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	file_tmp_path = install_path + "\\devtools_resources.pak";
	res = releaseRes(file_tmp_path, (WORD)IDR_devtools_resources, "APK");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}


	std::string install_path_skin = install_path + "\\locales";
	mkdir(install_path_skin.c_str());
	Sleep(300);
	process_fun(50, "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path_skin + "\\en-US.pak";
	res = releaseRes(file_tmp_path, (WORD)IDR_en_US, "APK");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}
	file_tmp_path = install_path_skin + "\\zh-CN.pak";
	res = releaseRes(file_tmp_path, (WORD)IDR_zh_CN, "APK");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	file_tmp_path = install_path + "\\d3dcompiler_43.dll";
	res = releaseRes(file_tmp_path, (WORD)IDR_d3dcompiler_43, "DLL");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	file_tmp_path = install_path + "\\d3dcompiler_47.dll";
	res = releaseRes(file_tmp_path, (WORD)IDR_d3dcompiler_47, "DLL");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	file_tmp_path = install_path + "\\DuiLib_u.dll";
	res = releaseRes(file_tmp_path, (WORD)IDR_DuiLib_u, "DLL");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	file_tmp_path = install_path + "\\libcef.dll";
	res = releaseRes(file_tmp_path, (WORD)IDR_libcef, "DLL");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	file_tmp_path = install_path + "\\libEGL.dll";
	res = releaseRes(file_tmp_path, (WORD)IDR_libEGL, "DLL");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	file_tmp_path = install_path + "\\libGLESv2.dll";
	res = releaseRes(file_tmp_path, (WORD)IDR_libGLESv2, "DLL");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	file_tmp_path = install_path + "\\widevinecdmadapter.dll";
	res = releaseRes(file_tmp_path, (WORD)IDR_widevinecdmadapter, "DLL");
	if (!res){
		return false;
	}
	inc += SysFileWrapper::getFileSize(Ecoder::stringToWstring(file_tmp_path));
	process_fun(static_cast<int>(static_cast<double>(inc) / all_file_size * 100), "");
	if (m_stop){
		return true;
	}

	if (!writeToReg()){
		return false;
	}
	file_tmp_path = install_path + "\\YDDemo.exe";
	setShortCutLink(file_tmp_path, "YDDemo.lnk", is_shortcut);
	Sleep(300);
	file_tmp_path = install_path + "\\Unstall.exe";
	setShortCutLink(file_tmp_path, "Ð¶ÔØYDDemo.lnk", FALSE);
	process_fun(100, "");
	Sleep(1000);
	//
	if (m_stop){
		return true;
	}
	process_end();
	return true;
}

bool Install::releaseRes(const std::string & file_name, unsigned short res_id, const std::string & file_type){
	DWORD   dwWrite = 0; 
	HANDLE  hFile = CreateFile(Ecoder::stringToWstring(file_name).c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE){
		return FALSE;
	}
	HRSRC   hrsc = FindResource(NULL, MAKEINTRESOURCE(res_id), Ecoder::stringToWstring(file_type).c_str());
	HGLOBAL hG = LoadResource(NULL, hrsc);
	DWORD   dwSize = SizeofResource(NULL, hrsc);  
	WriteFile(hFile, hG, dwSize, &dwWrite, NULL);
	CloseHandle(hFile);
	return true;
}

bool Install::writeToReg(){
	wchar_t strDisplayIcon[512], strDisplayName[32] = L"YDDemo", strInstallLocation[512], strPublisher[32] = L"YDDemo", strUninstallString[512];
	_stprintf(strDisplayIcon, L"%s\\YDDemo.exe", Ecoder::stringToWstring(m_install_path).c_str());
	_stprintf(strInstallLocation, L"%s", Ecoder::stringToWstring(m_install_path).c_str());
	_stprintf(strUninstallString, L"%s\\Unstall.exe", Ecoder::stringToWstring(m_install_path).c_str());
	HKEY   key;
	DWORD  lpdw;
	char   SubKey[255] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\YDDemo";

	if (ERROR_SUCCESS == RegCreateKeyEx(HKEY_LOCAL_MACHINE,Ecoder::stringToWstring(SubKey).c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &lpdw)){
		if (ERROR_SUCCESS != RegSetValueEx(key, Ecoder::stringToWstring("DisplayIcon").c_str(), NULL, REG_SZ, (LPBYTE)strDisplayIcon, (lstrlen(strDisplayIcon) + 1)*sizeof(TCHAR)))
			return false;
		if (ERROR_SUCCESS != RegSetValueEx(key, Ecoder::stringToWstring("DisplayName").c_str(), NULL, REG_SZ, (LPBYTE)strDisplayName, (lstrlen(strDisplayName) + 1)*sizeof(TCHAR)))
			return false;
		if (ERROR_SUCCESS != RegSetValueEx(key, Ecoder::stringToWstring("InstallLocation").c_str(), NULL, REG_SZ, (LPBYTE)strInstallLocation, (lstrlen(strInstallLocation) + 1)*sizeof(TCHAR)))
			return false;
		process_fun(80, "");
		if (ERROR_SUCCESS != RegSetValueEx(key, Ecoder::stringToWstring("Publisher").c_str(), NULL, REG_SZ, (LPBYTE)strPublisher, (lstrlen(strPublisher) + 1)*sizeof(TCHAR)))
			return false;
		if (ERROR_SUCCESS != RegSetValueEx(key, Ecoder::stringToWstring("UninstallString").c_str(), NULL, REG_SZ, (LPBYTE)strUninstallString, (lstrlen(strUninstallString) + 1)*sizeof(TCHAR)))
			return false;
		RegCloseKey(key);
		return true;
	}
	else{
		return false;
	}
}


bool Install::setShortCutLink(const std::string & path, const std::string & link_name, bool is_desktop){	
	HRESULT hRet;
	IShellLink *pLink;	
	IPersistFile *ppf;	

	hRet = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
	if (hRet != S_OK){
		return false;
	}
	else{
		hRet = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
		if (hRet == S_OK){
			std::string strDirStartMenu = getStartMenuPath();		
			std::string strDirDesktop = getDesktopPath();			
			std::string strPath;
			strPath = strDirStartMenu + "YDDemo";
			CreateDirectory(Ecoder::stringToWstring(strPath).c_str(), NULL);
			pLink->SetPath(Ecoder::stringToWstring(path).c_str());
			strPath = strPath + "\\";
			strPath += link_name;
			ppf->Save(Ecoder::stringToWstring(strPath).c_str(), TRUE);
			if (is_desktop){
				strPath= strDirDesktop+"\\"+ link_name;
				ppf->Save(Ecoder::stringToWstring(strPath).c_str(), TRUE);
			}
		}
		else{
			pLink->Release();
			return false;
		}
	}
	ppf->Release();
	pLink->Release();

	return true;
}

std::string Install::getDesktopPath(){
	std::string  strPath;
	wchar_t szPath[1024];

	::ZeroMemory(szPath, sizeof(szPath));
	if (::SHGetSpecialFolderPath(NULL, szPath, CSIDL_DESKTOPDIRECTORY, FALSE)){		
		strPath = Ecoder::wstringToString(szPath) + "\\";
	}
	return strPath;
}


std::string Install::getStartMenuPath(){
	std::string strPath;
	wchar_t szPath[1024];

	::ZeroMemory(szPath, sizeof(szPath));
	if (::SHGetSpecialFolderPath(NULL, szPath, CSIDL_STARTMENU, FALSE)){
		strPath = Ecoder::wstringToString(szPath) + "\\³ÌÐò\\";
	}
	return strPath;
}