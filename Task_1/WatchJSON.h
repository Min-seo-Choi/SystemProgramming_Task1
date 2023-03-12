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
	std::map<std::string, WCHAR*> settingFile;	// ini ������ ���� ����
	std::vector<std::string> directoryFiles;	// ������ ���� �ȿ� �ִ� .json ���ϵ�
	bool result;	// ������ ����� �ҷ��� ������

	std::string CharToString(const char* ch);
	WCHAR* CharToWCHAR(const char* ch);
	char* WCHARToChar(const wchar_t* ch);
	char* Combine(const char* ch1, const char* ch2);
};

