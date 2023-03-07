#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	//ofstream file("setting.ini");
	//if (file.is_open()) {
.	//	file << "[Section]" << endl;
	//	file << "DirectoryName=\\JSON" << endl;
	//	file << "LogLevel=2" << endl;
	//	file.close();
	//	cout << "setting.ini file created successfully" << endl;
	//}
	//else {
	//	cerr << "Error: failed to create setting.ini file" << endl;
	//}

	//bool result = WritePrivateProfileString(L"INFO", L"DiretoryName", L"\\JSON", L"setting.ini");

	//if (result)
	//{
	//	wcout << "setting.ini file created successfully" << endl;
	//}

	//wchar_t dirName[256];
	//GetPrivateProfileString(L"Section", L"DiretoryName", L" _ ", dirName, 256, L"setting.ini");
	//wcout << "Directory name: " << dirName << endl;

	WCHAR buffer[MAX_PATH];
	DWORD result = GetPrivateProfileString(L"INFO", L"DiretoryName", L"", buffer, MAX_PATH, L".\\setting.ini");

	if (result != 0)
	{
		wcout << buffer << endl;
	}
	else
	{
		cerr << "Error: Unable to retrieve value from setting.ini" << endl;
	}

	return 0;
}