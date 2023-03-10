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
	std::map<const char*, const char*> settingFile;	// ini 파일의 설정 정보
	char settingContent[MAX_PATH];					// ini 파일에서 불러온 내용

	std::vector<std::string> directoryFiles;	// 지정된 폴더 안에 있는 .json 파일들
	bool result;	// 파일이 제대로 불러와 졌는지

	char* Combine(const char* ch1, const char* ch2);
};

