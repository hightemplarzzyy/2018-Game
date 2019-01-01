#include "OBJLoader.h"
#include "InputStream.h"
#include <iostream>
#include <fstream>

using namespace std;

SubBlueprint* OBJLoader::loadOBJFiles(map<string, Material>* materialsCache)
{
	ifstream read_file;
	read_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	SubBlueprint* subBlueprint(nullptr);
	
	vector<Vec3> positions;
	vector<Vec3> normals;
	Vec3 max(-100, -100, -100);
	Vec3 min(100, 100, 100);
	try
	{
		string file = "res/" + InputStream::getString("请输入obj文件名");
		read_file.open(file, ios::binary);
	}
	catch (std::ios_base::failure& e) {
		std::cerr << e.what() << '\n';
		return subBlueprint;
	}
	try
	{
		string line;
		while (getline(read_file, line))
		{
			subBlueprint = new SubBlueprint();
			if (strncmp(line.c_str(), "mtllib", 6) == 0)
			{
				loadMaterials(line, materialsCache);
			}
			else if (strncmp(line.c_str(), "v ", 2) == 0)
			{
				vector<string> points = split(line, ' ');
				Vec3 position = Vec3(atof(points[1].c_str()), atof(points[2].c_str()), atof(points[3].c_str()));
				positions.push_back(position);
				checkMaxMin(max, min, position);
			}
			else if (strncmp(line.c_str(), "vn ", 3) == 0)
			{
				vector<string> points = split(line, ' ');
				normals.push_back(Vec3(atof(points[1].c_str()), atof(points[2].c_str()), atof(points[3].c_str())));
			}
			else if (strncmp(line.c_str(), "g", 1) == 0)
			{
				ModelSection* modelSction(nullptr);
				while (getline(read_file, line))
				{
					//ModelSection* modelSction(nullptr);
					if (strncmp(line.c_str(), "usemtl", 6) == 0)
					{
						modelSction = new ModelSection(&(*materialsCache).at(split(line, ' ')[1]));
						(*subBlueprint).addSection(modelSction);
					}
					else if (strncmp(line.c_str(), "f ", 2) == 0)
					{
						vector<string> points = split(line, ' ');
						Vertex a1 = Vertex(positions.at(stoi(split(points[1], '/')[0]) - 1), normals.at(stoi(split(points[1], '/')[2]) - 1));
						Vertex a2 = Vertex(positions.at(stoi(split(points[2], '/')[0]) - 1), normals.at(stoi(split(points[2], '/')[2]) - 1));
						Vertex a3 = Vertex(positions.at(stoi(split(points[3], '/')[0]) - 1), normals.at(stoi(split(points[3], '/')[2]) - 1));
						modelSction->addTriangle(Triangle(a1, a2, a3));
					}
				}
			}


		}
	}
	catch (const std::exception&)
	{
	}
	subBlueprint->setMax(max);
	subBlueprint->setMin(min);
	return subBlueprint;
}

void OBJLoader::loadMaterials(string fileline, map<string, Material>* materialscache)
{
	ifstream read_file;
	string file = "res/" + split(fileline, ' ')[1];
	read_file.open(file, ios::binary);
	string line;
	string key;
	while (getline(read_file, line)) {
		if (strncmp(line.c_str(), "newmtl", 6) == 0)
		{
			key = split(line, ' ')[1];
			getline(read_file, line);
			getline(read_file, line);
			getline(read_file, line);
			vector<string> values = split(line, ' ');
			(*materialscache)[key] = Material(key, Material::Colour(stof(values[1]), stof(values[2]), stof(values[3])));
		}
	}
	read_file.close();
}

OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}

void OBJLoader::checkMaxMin(Vec3 & max, Vec3 & min, Vec3 normal)
{
	max.setX(std::fmax(max.getX(), normal.getX()));
	max.setY(std::fmax(max.getY(), normal.getY()));
	max.setZ(std::fmax(max.getZ(), normal.getZ()));

	min.setX(std::fmin(min.getX(), normal.getX()));
	min.setY(std::fmin(min.getY(), normal.getY()));
	min.setZ(std::fmin(min.getZ(), normal.getZ()));
}
