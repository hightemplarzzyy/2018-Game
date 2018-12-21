#pragma once
#include<vector>
#include<io.h>
#include<list>
#include"saveslot.h"
const string SAVES_FOLDER = "E:\\Data_Saves2\\";
 class Saves {
 public:
	 vector<SaveSlot> slots;
	 
	 Saves(int slotCount);

	 SaveSlot createNewSave();
	 SaveSlot getSaveSlot(int number);

	 list<SaveSlot> getCorruptSaves();

	 SaveSlot getFirstWorld();

	  int getSlotCount() {return slots.size();}

	 void initSavesFolder() {string command;command = "mkdir  " + SAVES_FOLDER;system(command.c_str());}

	 void deleteSave(int i) {
		SaveSlot slot = slots[i];
		slots.erase(slots.begin()+i);
		cout<<remove("E:\\Data_Saves2\\Save_1.save");
		//remove(slot.path.c_str());
	 }

	 void getJustCurrentFile(string path, vector<string>& files) {
		 long long hFile = 0;
		 struct _finddata_t fileinfo;
		 string p;
		 if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
			do {
				if ((fileinfo.attrib & _A_SUBDIR)) {; }
				 else {
					files.push_back(fileinfo.name);
				 }
			 } while (_findnext(hFile, &fileinfo) == 0);
				          _findclose(hFile);
		 }
	 }
 };