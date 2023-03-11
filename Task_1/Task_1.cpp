#include <iostream>
#include <string>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

string wstringToString(const wstring& wstr);

int main()
{
	//ofstream file("Test_2.json");
	//if (file.is_open()) {
	//	//file << "[Section]" << endl;
	//	//file << "DirectoryName=\\JSON" << endl;
	//	//file << "LogLevel=2" << endl;
	//	//file.close();
	//	cout << "setting.ini file created successfully" << endl;
	//}
	//else {
	//	cerr << "Error: failed to create setting.ini file" << endl;
	//}

	WCHAR buffer[MAX_PATH];
	bool result = GetPrivateProfileString(L"INFO", L"DiretoryName", L"", buffer, MAX_PATH, L".\\setting.ini");

	if (result)
	{
		string folder_path = wstringToString(buffer);
		folder_path.insert(0, ".\\");

		if (fs::exists(folder_path) && fs::is_directory(folder_path))
		{
			// setting.ini에 설정된 폴더에 있는 json 확장자만 파일명을 출력한다.
			for (const auto& entry : fs::directory_iterator(folder_path))
			{
				if (entry.path().extension() == ".json")
				{
					cout << "File name : " << entry.path().filename() << endl;
				}
			}

			cout << "읽어올 파일명 : ";
			string file_name = " ";
			cin >> file_name;

			// 파일 읽어오기
			string file_path = folder_path.append("\\").append(file_name.append(".json"));

			ifstream select_file(file_path);
			if (!select_file.bad())
			{
				cout << select_file.rdbuf();
				select_file.close();
			}
			else
			{

			}
		}
		else
		{
			// 코드 푸시 테스트
			// 해당 디렉토리가 없으면 만들건지, 나갈건지(?) 선택
			// cout << "Folder does not exist" << endl;
		}
	}
	return 0;
}

string wstringToString(const wstring& wstr) {
	int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	string str(size - 1, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, nullptr, nullptr);
	return str;
}

//for (fs::directory_iterator iter(folder_path); iter != fs::directory_iterator(fs::path(folder_path).parent_path().string() + "\\"); ++iter) {
//	if (iter->path().extension() == ".json") {
//		std::cout << "File name: " << iter->path().filename() << std::endl;
//	}
//}