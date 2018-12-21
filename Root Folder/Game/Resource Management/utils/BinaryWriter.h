#pragma once
#include<string>
#include"../../Render Engine/toolbox/maths/maths_func.h"
class BinaryWriter {
public:

	FILE *file;

	BinaryWriter(std::string path) { fopen_s(&file, path.c_str(), "w+"); };

	void writeInt(int data) { fprintf(file,"%d\t",data); }
	void writeFloat(float data) { fprintf(file, "%f\t", data); }
	void writeString(string data) {const char *a = data.c_str(); fprintf(file, "%s\n", a); }
	
	void writevec3(vec3 data) { writeFloat(data.x); writeFloat(data.y); writeFloat(data.z); }

	void close() { fclose(file); }
};