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
			cout << "현재 경로 설정 파일 경로: " << fs::absolute(settingFile["FileName"]) << endl;
			string folderPath = Combine(".\\", settingContent);

			// 폴더 안에 파일이 존재하는지 존재하지 않는지 판단
			if (fs::exists(folderPath) && fs::is_directory(folderPath))
			{
				// setting.ini에 설정된 폴더에 있는 json 확장자만 파일명을 출력한다.
				LoadJsonFileNames(folderPath);
				ShowJsonFile(folderPath);
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
		cout << "읽어올 파일명 : ";
		string fileName = "";
		cin >> fileName;

		// 파일 읽어오기
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

			cout << "파일 수정을 감지 중 입니다..." << endl;	
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