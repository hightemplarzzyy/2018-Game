// ModelConverter.cpp : 定义控制台应用程序的入口点。
//

#include "structures/Blueprint.h"
#include "utils/InputStream.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	Blueprint blueprint;
	blueprint.loadModelInfo();
	blueprint.getComponents();
	blueprint.exportBlueprint();
}

