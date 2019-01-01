#pragma once
#include<string>
#include<iostream>
#include"../../Render Engine/toolbox/maths/maths_func.h"
using namespace std;
class BinaryReader {
public:
	
	FILE *file;

	BinaryReader(std::string path) {  fopen_s(&file, path.c_str(), "r"); rewind(file);};

	int readInt() { int data; fscanf(file, "%d", &data); return data; }
	float readFloat() { float data; fscanf(file, "%f", &data); return data; }
	//int readbool() { bool data; fscanf(file, "%d", &data); return data; }
	std::string readString() { char data[100]; fscanf(file, "%s", data);return  data; }

	vec3 readvec3() {
		float x = readFloat();
		float y = readFloat();
		float z = readFloat();
		return vec3(x, y, z);
	}

	void close() { fclose(file); }
};