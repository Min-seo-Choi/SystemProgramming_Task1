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
	settingFile.insert({ "FileName", "setting.ini" });
	settingFile.insert({ "FilePath", ".\\setting.ini" });
	settingFile.insert({ "Section", "INFO" });
	settingFile.insert({ "Key", "DiretoryName" });
	settingFile.insert({ "Default", "No Data" });


	result = GetPrivateProfileStringA(settingFile["Section"], settingFile["Key"], "", settingContent, MAX_PATH, settingFile["FilePath"]);
}

void WatchJSON::Loop()
{
	while (true)
	{
		if (result)
		{
			cout << "현재 경로 설정 파일 경로: " << fs::absolute(settingFile["FileName"]) << endl;
			string folderPath = Combine(".\\", settingContent);

			// 폴더 안에 파일이 존재하는지 존재하지 않는지 판단
			if (fs::exists(folderPath) && fs::is_directory(folderPath))
			{
				int count = 0;
				// setting.ini에 설정된 폴더에 있는 json 확장자만 파일명을 출력한다.
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
					cout << "읽어올 파일명 : ";
					string fileName = "";
					cin >> fileName;

					// 파일 읽어오기
					string filePath = folderPath.append("\\").append(fileName.append(".json"));

					ifstream select_file(filePath);
					if (select_file.is_open())
					{
						cout << select_file.rdbuf() << endl << endl;
						select_file.close();
					}
					else
					{
						cout << "찾는 파일이 없습니다" << endl << endl;
					}
				}
				else
				{
					cout << ".json 확장자 파일이 없습니다." << endl << endl;
				}
			}
			else
			{
				cout << "설정된 폴더 안에 파일이 없습니다." << endl << endl;
			}
		}
		else
		{
			cout << "설정 파일이 로드되지 않았습니다. 다시 한번 확인해 주시기 바랍니다." << endl;
			cout << "현재 경로 설정 파일 경로: " << fs::absolute(settingFile["FileName"]) << endl;
			cout << "파일 명 : " << settingFile["FileName"] << endl;
			cout << "Section : " << settingFile["Section"] << endl;
			cout << "Key : " << settingFile["Key"] << endl;
		}
	}
}


char* WatchJSON::Combine(const char* ch1, const char* ch2)
{
	char* combine = new char[strlen(ch1) + strlen(ch2) + 1 + 1];
	strcpy(combine, ch1);
	strcat(combine, ch2);

	return combine;
}
