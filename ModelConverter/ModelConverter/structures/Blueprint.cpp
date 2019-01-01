#include "Blueprint.h"
#include "../utils/InputStream.h"
#include "../utils/OBJLoader.h"
Blueprint::Blueprint()
{
}


Blueprint::~Blueprint()
{
}

void Blueprint::loadModelInfo()
{
	overWater = InputStream::getBool("bulePrint 的overWater属性:");
	underWater = InputStream::getBool("bulePrint 的underWater属性:");
	do
	{
		SubBlueprint* subBlueprint = OBJLoader::loadOBJFiles(&materialsCache);
		if (subBlueprint != NULL)
		{
			subBlueprints.push_back(subBlueprint);
		}
	} while (InputStream::getBool("是否继续加载obj文件，加载的obj的个数为" + std::to_string(subBlueprints.size())));

	if (InputStream::getBool("是否要修改material文件"))
	{
		map<string, Material>::iterator iter;
		for (iter = materialsCache.begin(); iter != materialsCache.end(); iter++) {
			cout << iter->first << " : " << iter->second.colour.toString() << endl;
		}
		while (true)
		{
			string name = InputStream::getString("请输入修改的material的名称");
			try
			{
				materialsCache.at(name).colour.SetFlag(-1);
				string rgb = InputStream::getString("设置material的rgb格式");
				materialsCache.at(name).colour.SetCode(rgbToFloat(rgb));
				materialsCache.at(name).colour.SetOffset(InputStream::getFloat("设置material的offset"));
				isCostomMaterial = true;
			}
			catch (const std::exception&)
			{
				cout << "输入文件错误，请重新输入" << endl;
			}
			if (!InputStream::getBool("是否继续修改"))
			{
				break;
			}
		}
	}
	if (isCostomMaterial)
	{
		baseColour1.setX(InputStream::getFloat("输入base颜色1的x"));
		baseColour1.setY(InputStream::getFloat("输入base颜色1的y"));
		baseColour1.setZ(InputStream::getFloat("输入base颜色1的z"));
		if (InputStream::getBool("是否输入base颜色2"))
		{
			baseColour2.setX(InputStream::getFloat("输入base颜色1的x"));
			baseColour2.setY(InputStream::getFloat("输入base颜色1的y"));
			baseColour2.setZ(InputStream::getFloat("输入base颜色1的z"));
		}
		else {
			baseColour2 = baseColour1;
		}
	}
}

void Blueprint::getComponents()
{

	while (InputStream::getBool("是否继续加载component文件，目前已加载的obj的个数为" + std::to_string(components.size())))
	{
		map<int, string>::iterator iter;
		for (iter = ComponentFactor::componentsMap.begin(); iter != ComponentFactor::componentsMap.end(); iter++) {
			cout << iter->first << " : " << iter->second << endl;
		}
		cout << "-1" << " : " << "退出" << endl;
		Component* component = ComponentFactor::createComponent(InputStream::getInt("请输入要添加的component的编号(数字)"));
		if (component != nullptr)
		{
			components.push_back(component);
		}
	} 
}

void Blueprint::exportBlueprint()
{
	string filename = InputStream::getString("请输入输出文件的文件名(不包含.txt后缀)");
	ofstream outfile("out/" +  filename + ".txt", fstream::out);
	if (outfile)
	{
		outfile << "underwater :" << this->underWater << "	" << "overwater :" << this->overWater << endl;
		outfile << "subBlueprint的数量为：" << this->subBlueprints.size() << endl;
		for (int i = 0; i < subBlueprints.size(); i++)
		{
			outfile << "第" << i << "个subBlueprint" << endl;
			outfile << "	" << "subBlueprint的顶点的个数为:" << subBlueprints[i]->getVertexCount() << endl;
			outfile << "	" << "subBlueprint的positions点中，最大的position坐标为:"
				<< "x:" << subBlueprints[i]->getMax().getX() << " "
				<< "y:" << subBlueprints[i]->getMax().getY() << " "
				<< "z:" << subBlueprints[i]->getMax().getZ() << " " << endl;
			outfile << "	" << "subBlueprint的positions点中，最小的position坐标为:"
				<< "x:" << subBlueprints[i]->getMin().getX() << " "
				<< "y:" << subBlueprints[i]->getMin().getY() << " "
				<< "z:" << subBlueprints[i]->getMin().getZ() << " " << endl;
			outfile << "	" << "sections的数量为：" << subBlueprints[i]->getSections().size() << endl;
			for (int j = 0; j < subBlueprints[i]->getSections().size(); j++)
			{
				outfile <<  "	" << "第" << j << "个section" << endl;
				outfile << "	" << "		" << "顶点的个数为：" << (subBlueprints[i]->getSections())[j]->getVertexCount() << endl;
				outfile << "	" << "		" << "section材质的编码：" << (subBlueprints[i]->getSections())[j]->getMaterial()->colour.toString() << endl;
				vector<Triangle> triangles = (subBlueprints[i]->getSections())[j]->getTriangles();
				for (int k = 0; k < triangles.size(); k++)
				{
					outfile << "	" << "		" << "第" << k << "个三角形" << endl;
					outfile << "	" << "		" <<  "		" << triangles[k].toString() << endl;
				}
			}
		}

		outfile << endl;
		outfile << endl;

		if (isCostomMaterial)
		{
			outfile << "component的baseColour1: " << baseColour1.getX() << "," << baseColour1.getY() << "," <<baseColour1.getZ() << endl;
			outfile << "component的baseColour2: " << baseColour2.getX() << "," << baseColour2.getY() << "," << baseColour2.getZ() << endl;
		}
		outfile << "component的数量为：" << this->components.size() << endl;
		for (int i = 0; i < components.size(); i++)
		{
			outfile << "第" << i << "个component" << endl;
			outfile << components[i]->toString() << endl;
		}
		outfile.close();
	}
}

int Blueprint::rgbToFloat(string rgb)
{
	float code = 0;
	bool r = false, g = false, b = false;
	for (int i = 0; i < rgb.size(); i++)
	{
		if (rgb[i] == 'r' || rgb[i] == 'R')
		{
			r = true;
		}
		else if (rgb[i] == 'g' || rgb[i] == 'G') {
			g = true;
		}
		else if (rgb[i] == 'b' || rgb[i] == 'B') {
			b = true;
		}
	}
	if (r == true) {
		code += 1;
	}
	if (g == true)
	{
		code += 2;
	}
	if (b == true) 
	{
		code += 4;
	}
	
	return code;
}




