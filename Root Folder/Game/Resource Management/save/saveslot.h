#pragma once
#include<iostream>
#include<string>
#include"../utils/fileutils.h"
#include"../../Resource Management/utils/BinaryReader.h"
#include"../../Resource Management/utils/BinaryWriter.h"
using namespace std;


class SaveSlot {
public:
	string name;
	string root;
	int number;
	string path;
	FILE *saveFile;
	//private SaveSlotInfo info;
	bool corrupt = false;
	
	SaveSlot() { name = ""; root = ""; number = -1; path = ""; saveFile = NULL; };
	SaveSlot(int number,string root);
	SaveSlot(int number, string name,string root);

	void reName(string name);
	void deletefile();
	void createFile();

	void setCorrupt() {corrupt = true;}
	int getNumber() {return number;}
	bool isCorrupt() {return corrupt;}
	bool isEmpty() {return fopen_s(&saveFile, path.c_str(), "r");}

	void generateDefaultName() {  string a = to_string(number + 1); name = "Save_" + a; }

	BinaryReader getReader()  {
		BinaryReader reader(path);
		//reader.readBoolean();
		//info.load(reader);
		return reader;
	}

	BinaryWriter getWriter(){
		BinaryWriter writer(path);
		//reader.readBoolean();
		//info.load(reader);
		return writer;
	}
};