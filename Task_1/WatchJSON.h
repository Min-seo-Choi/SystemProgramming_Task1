#pragma once
#include <windows.h>
#include <map>
#include <vector>
#include <string>

class WatchJSON
{
public:
	WatchJSON();
	~WatchJSON();

	void Start();
	void Loop();

private:
	std::map<std::string, WCHAR*> settingFile;	// ini 파일의 설정 정보
	std::vector<std::string> directoryFiles;	// 지정된 폴더 안에 있는 .json 파일들
	bool result;	// 파일이 제대로 불러와 졌는지

	std::string CharToString(const char* ch);
	WCHAR* CharToWCHAR(const char* ch);
	char* WCHARToChar(const wchar_t* ch);
	char* Combine(const char* ch1, const char* ch2);
};

