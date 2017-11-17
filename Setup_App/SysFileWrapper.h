#pragma once
#include <string>

using std::string;
using std::wstring;

class SysFileWrapper
{
public:
	SysFileWrapper(void);
	~SysFileWrapper(void);
	static size_t SysFileWrapper::getFileSize(const wstring & file);
	static size_t SysFileWrapper::getFolderSize(const wstring & dir);
};

