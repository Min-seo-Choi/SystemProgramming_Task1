#define _CRT_SECURE_NO_WARNINGS
#include "WatchJSON.h"


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
			cout << "���� ��� ���� ���� ���: " << fs::absolute(settingFile["FileName"]) << endl;
			string folderPath = Combine(".\\", settingContent);

			// ���� �ȿ� ������ �����ϴ��� �������� �ʴ��� �Ǵ�
			if (fs::exists(folderPath) && fs::is_directory(folderPath))
			{
				// setting.ini�� ������ ������ �ִ� json Ȯ���ڸ� ���ϸ��� ����Ѵ�.
				LoadJsonFileNames(folderPath);
				ShowJsonFile(folderPath);
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

void WatchJSON::ShowJsonFile(string folderPath)
{
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
			char jsonFile;
			while (select_file.get(jsonFile))
			{
				cout << jsonFile << endl << endl; 
			}
			select_file.close();

			cout << "���� ������ ���� �� �Դϴ�..." << endl;	
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



char* WatchJSON::Combine(const char* ch1, const char* ch2)
{
	char* combine = new char[strlen(ch1) + strlen(ch2) + 1 + 1];
	strcpy(combine, ch1);
	strcat(combine, ch2);

	return combine;
}


std::string JsonDocToString(Document& doc, bool isPretty = false)
{
	StringBuffer buffer;
	if (isPretty)
	{
		PrettyWriter<StringBuffer> writer(buffer);
		doc.Accept(writer);
	}
	else
	{
		Writer<StringBuffer> writer(buffer);
		doc.Accept(writer);
	}
	return buffer.GetString();
}