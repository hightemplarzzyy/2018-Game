#pragma once
#include <iostream>
#include <string>
using std::string;
class Material
{
public:
	class Colour
	{
	public:
		Colour(float flag, float code, float offset);
		Colour() {};
		void SetFlag(float flag) {
			this->flag = flag;
		}
		void SetCode(float code) {
			this->code = code;
		}
		void SetOffset(float offset) {
			this->offset = offset;
		}
		string toString() {
			return "flag:"  + std::to_string(flag) + "	" + "code:" + std::to_string(code) + "	" + "offset:" + std::to_string(offset);
		}
	private:
		float flag, code, offset;
	};

	Material(string name, Colour colour);
	Material();
	~Material();
	string name;
	Colour colour;
};



