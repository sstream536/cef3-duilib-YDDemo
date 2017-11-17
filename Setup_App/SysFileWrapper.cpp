#include "SysFileWrapper.h"
#include <Windows.h>

SysFileWrapper::SysFileWrapper(void)
{
}


SysFileWrapper::~SysFileWrapper(void)
{
}


size_t SysFileWrapper::getFileSize(const wstring & file){
	HANDLE h_file = CreateFile(file.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
	if (INVALID_HANDLE_VALUE == h_file){  
		return 0;
	}
	LARGE_INTEGER size;  
	if (::GetFileSizeEx(h_file, &size)){  
		CloseHandle(h_file);  
		return size.QuadPart;  
	}  
	else{
		return 0;
	}
}

size_t SysFileWrapper::getFolderSize(const wstring & dir){  
	size_t all_file_size = 0;  
	wstring root_path = dir + L"\\";  
	wstring root = root_path + L"*.*";  
	WIN32_FIND_DATA fd;  
	HANDLE h_find = FindFirstFile(root.c_str(), &fd);  
	if (INVALID_HANDLE_VALUE == h_find){
		return all_file_size;
	}  
	while (FindNextFile(h_find, &fd)){  
		if (wcscmp(fd.cFileName, L".") == 0 || wcscmp(fd.cFileName, L"..") == 0){  
			continue;  
		}
		wstring str_path_or_file = root_path + fd.cFileName;  
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){  
			all_file_size += getFolderSize(str_path_or_file);  
		}
		else{  
			size_t size;
			if((size =getFileSize(str_path_or_file))!=0){
				all_file_size += size;
			}
			else{
				continue;
			}
		}  
	}  
	FindClose(h_find);  
	return all_file_size;  
}  
