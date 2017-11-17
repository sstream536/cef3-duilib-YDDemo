#pragma once
#include<string>
#include<functional>

class UnInstall
{
public:
	UnInstall();
	virtual ~UnInstall();
	static UnInstall& getInstance(){
		static UnInstall instance;
		return instance;
	}
	void setCallBack(const std::function<void(int, const std::string &)>  &fun_1, const std::function<void()> &fun_2){
		process_fun = fun_1;
		process_end = fun_2;
	}
	bool unInstall();
	bool deleteRegKey();
	bool deleteDirFile(const std::string & path);
	bool deleteApplicationSelf();
private:
	std::function<void(int, const std::string &)> process_fun;
	std::function<void()> process_end;
};

