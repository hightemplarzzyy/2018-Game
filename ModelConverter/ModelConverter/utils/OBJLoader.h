#pragma once
#include "../structures/SubBlueprint.h"
#include "../structures/Material.h"
#include "../structures/Vertex.h"
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
class OBJLoader
{
public:
	static SubBlueprint* loadOBJFiles(map<string, Material>* materialsCache);
	static void loadMaterials(string line, map<string, Material>* materialscache);
	OBJLoader();
	~OBJLoader();

	static std::vector<std::string> split(const std::string &s, char delim) {
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> elems;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

private:
	static void checkMaxMin(Vec3& max, Vec3& min, Vec3 normal);
};



