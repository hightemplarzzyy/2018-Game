#pragma once
#include <string>


class GameText {
public:
	void init(int langId) {
		return;
	}
	int getLanguageId() {
		return 0;
	}
	//ComplexString getComplexText(int id);
	static std::string getText(int id) {
		std::string s = "nothing";
		return s;
	}
};