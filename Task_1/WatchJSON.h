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
	std::map<const char*, const char*> settingFile;	// ini ������ ���� ����
	char settingContent[MAX_PATH];					// ini ���Ͽ��� �ҷ��� ����

	std::vector<std::string> directoryFiles;	// ������ ���� �ȿ� �ִ� .json ���ϵ�
	bool result;	// ������ ����� �ҷ��� ������

	void LoadJsonFileNames(std::string folderPath);		// ������ �ִ� .json ������ �η��´�
	void ShowJsonFile(std::string folderPath);			// ������ ���ϸ� ���� .json�� ������ �����ش�
	char* Combine(const char* ch1, const char* ch2);	// ���ڿ� ��ü(?)};
}