#pragma once

#include <string>

class FileUtils {
public:
	static std::string read_file(const char *filepath);

	void write_file_a(const char * filepath, const char * content);
	void write_file_w(const char * filepath, const char * content);
};