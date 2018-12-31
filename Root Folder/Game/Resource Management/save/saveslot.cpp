#include"saveslot.h"


SaveSlot::SaveSlot(int number,string root) {
	this->number = number;
	generateDefaultName();
	this->root=root;
	path= root + name + ".save";
	//string PATH = root + name + ".save";
	const char *c_s = path.c_str();

	//fopen_s(&saveFile, c_s, "r");
	//loadInfo(); ÔØÈë±êÇ©
	//UserConfigs.checkCorruption(this); ÓÃ»§ÉèÖÃ
}

void SaveSlot::createFile(){
	if (isEmpty())
	{
		fopen_s(&saveFile, path.c_str(), "w+");
		fclose(saveFile);
	}
}

SaveSlot::SaveSlot(int number, string name,string root) {
	this->number = number;
	this->root = root;
	this->name = name;
	path = root + name;
	const char *c_s=path.c_str();

	//fopen_s(&saveFile, c_s, "r");
	//loadInfo();
	//UserConfigs.checkCorruption(this);
}

void SaveSlot::reName(string name) {
	string oldpath = path;
	string newpath = root + name + ".save";
	if (oldpath != "")
	{
		rename(oldpath.c_str(), newpath.c_str());
		path = newpath;
		//fopen_s(&saveFile, path.c_str(), "w+");
		//fclose(saveFile);
	}
	else
	{
		cout << "´æµµ²»´æÔÚ";
	}
}
void SaveSlot::deletefile() {
	
	name = "";
	root = "";
	number = -1;
	const char *c_s = path.c_str();
	if (remove(c_s) == 0)
	{
		cout << "É¾³ý³É¹¦"<<endl;
	}
	else
	{
		cout << "É¾³ý´æµµÊ§°Ü"<<endl;
	};

	path = "";
}