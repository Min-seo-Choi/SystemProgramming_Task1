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

			cout << "���� ��� ���� ���� ���: " << fs::absolute(settingFile["FileName"]) << endl;
			string folderPath = Combine(".\\", settingContent);

			// ���� �ȿ� ������ �����ϴ��� �������� �ʴ��� �Ǵ�
			if (fs::exists(folderPath) && fs::is_directory(folderPath))
			{
				// setting.ini�� ������ ������ �ִ� json Ȯ���ڸ� ���ϸ��� ����Ѵ�.
				LoadJsonFileNames(folderPath);
				string filePath = ShowJsonFile(folderPath);
				ModifyJsonfile(filePath);
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
		cout << "�о�� ���ϸ� : ";
		string fileName = "";
		cin >> fileName;

		// ���� �о����
		string filePath = folderPath.append("\\").append(fileName.append(".json"));
		ifstream select_file(filePath);
		
		char charJson;

		// ������ ���� �ѹ� ���
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
			cout << "ã�� ������ �����ϴ�" << endl << endl;
			return "";
		}
	}
	else
	{
		cout << ".json Ȯ���� ������ �����ϴ�." << endl << endl;
		return "";
	}
}

void WatchJSON::ModifyJsonfile(string filePath)
{
	if (!originJson.empty() && !filePath.empty())
	{
		cout << "���� ������ ���� �� �Դϴ�..." << endl;

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
				cout << "���� ���� ������ ���� �Ǿ����ϴ�. �����̽��� ������ �ٽ� �ε��մϴ�." << endl;
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