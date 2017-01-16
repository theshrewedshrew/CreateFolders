#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <vector>
#include <WinBase.h>
#include <stdio.h>  /* defines FILENAME_MAX */
#include <direct.h>
#define GetCurrentDir _getcwd

using namespace std;
string _getWord();
void dCopyAry(char arr[], string str);
void main(){
	string fileName = "";
	bool isTextDoc = false;
	ifstream File;
	string tempName = "";
	vector<string> nameList; 
	cout << "Enter the file the folders are listed in. ";
	while (fileName.length() < 5 || !isTextDoc){
		fileName = _getWord();
		if (fileName.length() > 4){
			if (fileName.find(".txt") != fileName.npos)
				isTextDoc = true;
		}
		if (!isTextDoc){
			cout << "Please remember to format as a text document (retype the text doc filename) : ";
		}
	}
	File.open(fileName.c_str());
	if (File.is_open()){
		while (getline(File, tempName)){
			nameList.push_back(tempName);
		}
	}

	File.close();
	/*char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return;
	}
	OR 
	DWORD GetCurrentDirectory(
	DWORD nBufferLength,  // size of directory buffer
	LPTSTR lpBuffer       // directory buffer
	);
	DWORD result = 0;
	char currentDir[256];

	result = GetCurrentDirectory(256, currentDir);
	BOOL CreateDirectory(
	LPCTSTR lpPathName,                         // directory name
	LPSECURITY_ATTRIBUTES lpSecurityAttributes  // SD
	);
	CreateDirectory("C:\\Test\\Test1\\Test2", 0);
	*/
	DWORD result = 0;
	BOOL CreateFileNew = true;
	char currentDir[256];
	char copy[256];
	result = GetCurrentDirectory(256, currentDir);
	if (result == 0){
		//return;
	}
	for (int i = 0; i < (int)nameList.size(); i++){
		strcpy_s(copy, currentDir);
		string temp(copy);
		temp += "\\" + nameList.at(i);
		dCopyAry(copy, temp);
		CreateFileNew = CreateDirectory(copy, 0);
		
	}

	
}
void dCopyAry(char arr[], string str){
	for (int i = 0; i < 256; i++)
		if (i < str.length())
			arr[i] = str[i];
		else
		{
			arr[i] = '\0';
			return;
		}
}
string _getWord(){
	string word;
	int temp;
	do
	{
		temp = _getch();
		if (temp != 0 && temp != 13 && temp != 8)
		{
			word += char(temp);
			cout << char(temp);
		}
		else if (temp == 8)
		{
			//I want to erase a "*" and
			//backspace the last key entered into password
			word = word.substr(0, (int)word.length() - 1);
			cout << "\b" << " " << "\b";
		}
	} while (temp != 13);
	return word;
}