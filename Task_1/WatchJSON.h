#pragma once
#include "rapidjson/document.h"

#include <windows.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>

//#include ".\\rapidjson\writer.h"
//#include ".\\rapidjson\stringbuffer.h"*/

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

	std::string originJson;
	std::string newJson;

	void LoadJsonFileNames(std::string folderPath);		// 폴더에 있는 .json 파일을 불러온다
	std::string ShowJsonFile(std::string folderPath);			// 선택한 파일명에 따라 .json의 내용을 보여준다
	void ModifyJsonfile(std::string folderPath);		// 출력된 파일이 수정 되었는지 확인한다

	char* Combine(const char* ch1, const char* ch2);	// 문자열 합체(?)};
};