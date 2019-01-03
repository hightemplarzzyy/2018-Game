#include "fileutils.h"

std::string FileUtils::read_file(const char * filepath)
{
	FILE* file;
	fopen_s(&file, filepath, "rt");
	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);
	char* data = new char[length + 1];
	memset(data, 0, length + 1);
	fseek(file, 0, SEEK_SET);
	fread(data, 1, length, file);
	fclose(file);
	std::string result(data);
	delete[] data;
	return result;
}

void FileUtils::write_file_a(const char * filepath, const char * content)
{
	FILE* file;
	fopen_s(&file, filepath, "a+");
	fwrite(content, sizeof(char), sizeof(content), file);
	fclose(file);
}

void FileUtils::write_file_w(const char * filepath, const char * content)
{
	FILE* file;
	fopen_s(&file, filepath, "w+");
	fwrite(content, sizeof(char), sizeof(content), file);
	fclose(file);
}



