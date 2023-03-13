#define _CRT_SECURE_NO_WARNINGS
#include "WatchJSON.h"
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

WatchJSON::WatchJSON()
	:settingFile(), result(false)
{
}

WatchJSON::~WatchJSON()
{
}

void WatchJSON::Start()
{
	settingFile.insert({ CharToString("FileName"), CharToWCHAR("setting.ini") });
	settingFile.insert({ CharToString("FilePath"), CharToWCHAR(".\\setting.ini") });
	settingFile.insert({ CharToString("Section"), CharToWCHAR("INFO") });
	settingFile.insert({ CharToString("Key"), CharToWCHAR("DiretoryName") });
	settingFile.insert({ CharToString("Content"), new WCHAR[MAX_PATH] });
	settingFile.insert({ CharToString("Default"), CharToWCHAR("No Data") });

	result = GetPrivateProfileString(settingFile["Section"], settingFile["Key"], L"", settingFile["Content"], MAX_PATH, settingFile["FilePath"]);
}

void WatchJSON::Loop()
{
	while (true)
	{
		if (result)
		{
			cout << "���� ��� ���� ���� ���: " << fs::absolute(settingFile["FileName"]) << endl;
			string folderPath = Combine(".\\", WCHARToChar(settingFile["Content"]));

			if (fs::exists(folderPath) && fs::is_directory(folderPath))
			{
				int count = 0;
				// setting.ini�� ������ ������ �ִ� json Ȯ���ڸ� ���ϸ��� ����Ѵ�.
				for (const auto& entry : fs::directory_iterator(folderPath))
				{
					if (entry.path().extension() == ".json")
					{
						cout << count + 1 << "." << entry.path().filename() << endl;
						directoryFiles.push_back(entry.path().filename().string());
						count++;
					}
				}

				if (!directoryFiles.empty())
				{
					cout << "�о�� ���ϸ� : ";
					string fileName = "";
					cin >> fileName;

					// ���� �о����
					string filePath = folderPath.append("\\").append(fileName.append(".json"));

					ifstream select_file(filePath);
					if (select_file.is_open())
					{
						cout << select_file.rdbuf() << endl << endl;
						select_file.close();
					}
					else
					{
						cout << "ã�� ������ �����ϴ�" << endl << endl;
					}


				}
				else
				{
					cout << ".json Ȯ���� ������ �����ϴ�." << endl << endl;
				}
			}
			else
			{
				cout << "������ ���� �ȿ� ������ �����ϴ�." << endl << endl;
			}
		}
		else
		{
			cout << "���� ������ �ε���� �ʾҽ��ϴ�. �ٽ� �ѹ� Ȯ���� �ֽñ� �ٶ��ϴ�." << endl;
			cout << "���� ��� ���� ���� ���: " << fs::absolute(settingFile["FileName"]) << endl;
			cout << "���� �� : " << settingFile["FileName"] << endl;
			cout << "Section : " << settingFile["Section"] << endl;
			cout << "Key : " << settingFile["Key"] << endl;
		}
	}
}

string WatchJSON::CharToString(const char* ch)
{
	string str = ch;

	return str;
}

WCHAR* WatchJSON::CharToWCHAR(const char* ch)
{
	WCHAR* wchar;
	int charSize = MultiByteToWideChar(CP_UTF8, 0, ch, -1, NULL, NULL);

	wchar = new WCHAR[charSize];
	MultiByteToWideChar(CP_UTF8, 0, ch, strlen(ch) + 1, wchar, charSize);

	return wchar;
}

char* WatchJSON::WCHARToChar(const wchar_t* ch)
{
	char* chr;
	int chrSize = WideCharToMultiByte(CP_UTF8, 0, ch, -1, NULL, 0, NULL, NULL);

	chr = new char[chrSize];
	WideCharToMultiByte(CP_UTF8, 0, ch, -1, chr, chrSize, 0, 0);

	return chr;
}

char* WatchJSON::Combine(const char* ch1, const char* ch2)
{
	char* combine = new char[strlen(ch1) + strlen(ch2) + 1 + 1];
	strcpy(combine, ch1);
	strcat(combine, ch2);

	return combine;
}
