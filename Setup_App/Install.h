#pragma once
#include<string>
#include<functional>

class Install
{
public:
	Install();
	virtual ~Install();
	static Install& getInstance(){
		static Install instance;
		return instance;
	}
	void setStop(){
		m_stop = true;
	}
	bool install(const std::string & install_path, bool is_shortcut);
	void setCallBack(const std::function<void(int, const std::string &)>  &fun_1,const std::function<void()> &fun_2){
		process_fun = fun_1;
		process_end = fun_2;
	}
private:
	bool releaseRes(const std::string & file_name, unsigned short res_id, const std::string & file_type);
	bool setShortCutLink(const std::string & path, const std::string & link_name, bool is_desktop);
	bool writeToReg();
	std::string getDesktopPath();
	std::string getStartMenuPath();
private:
	std::function<void(int, const std::string &)> process_fun;
	std::function<void()> process_end;
	std::string m_install_path;
	bool m_stop;

};

