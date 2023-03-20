#define _CRT_SECURE_NO_WARNINGS
#include "WatchJSON.h"
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

WatchJSON::WatchJSON()
	:settingFile(), result(false), originJson(), newJson()
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
			originJson = "";

			cout << "현재 경로 설정 파일 경로: " << fs::absolute(settingFile["FileName"]) << endl;
			string folderPath = Combine(".\\", settingContent);

			// 폴더 안에 파일이 존재하는지 존재하지 않는지 판단
			if (fs::exists(folderPath) && fs::is_directory(folderPath))
			{
				// setting.ini에 설정된 폴더에 있는 json 확장자만 파일명을 출력한다.
				LoadJsonFileNames(folderPath);
				string filePath = ShowJsonFile(folderPath);
				ModifyJsonfile(filePath);
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

			originJson = "";
			newJson = "";
		}
	}
}

void WatchJSON::LoadJsonFileNames(string folderPath)
{
	int count = 0;
	for (const auto& entry : fs::directory_iterator(folderPath))
	{
		if (entry.path().extension() == ".json")
		{
			cout << count + 1 << "." << entry.path().filename() << endl;
			directoryFiles.push_back(entry.path().filename().string());
			count++;
		}
	}
}

string WatchJSON::ShowJsonFile(string folderPath)
{
	if (!directoryFiles.empty())
	{
		cout << "읽어올 파일명 : ";
		string fileName = "";
		cin >> fileName;

		// 파일 읽어오기
		string filePath = folderPath.append("\\").append(fileName.append(".json"));
		ifstream select_file(filePath);
		
		char charJson;

		// 선택한 파일 한번 출력
		if (select_file.is_open())
		{
			while (select_file.get(charJson))
			{
				originJson += charJson;
			}
			cout << originJson << endl;
			select_file.close();

			return filePath;
		}
		else
		{
			cout << "찾는 파일이 없습니다" << endl << endl;
			return "";
		}
	}
	else
	{
		cout << ".json 확장자 파일이 없습니다." << endl << endl;
		return "";
	}
}

void WatchJSON::ModifyJsonfile(string filePath)
{
	if (!originJson.empty() && !filePath.empty())
	{
		cout << "파일 수정을 감지 중 입니다..." << endl;

		char charJson;

		while (true)
		{
			if (newJson == "" || originJson == newJson)
			{
				newJson = "";
				ifstream select_file(filePath);

				if (select_file.is_open())
				{
					while (select_file.get(charJson))
					{
						newJson += charJson;
					}
					select_file.close();
				}
			}
			else
			{
				cout << "현재 파일 변경이 감지 되었습니다. 스페이스를 누르면 다시 로드합니다." << endl;
				while (true)
				{
					if (GetAsyncKeyState(' '))
					{
						originJson = newJson;
						newJson = "";
						cout << originJson << endl;
						break;
					}
				}
				cout << endl;
				break;
			}
		}
		Sleep(500);
		cout << "." << endl;
		Sleep(500);
		cout << "." << endl;
		Sleep(500);
		cout << ".";
		system("cls");
	}
}



char* WatchJSON::Combine(const char* ch1, const char* ch2)
{
	char* combine = new char[strlen(ch1) + strlen(ch2) + 1 + 1];
	strcpy(combine, ch1);
	strcat(combine, ch2);

	return combine;
}