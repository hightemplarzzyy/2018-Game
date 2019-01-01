#pragma once
#include "Component.h"
#include "InfoComp.h"
#include "GrowingComp.h"
#include "LifeComp.h"
#include "SpreaderComp.h"
#include "DynamicGrowingComp.h"
#include "FoodComp.h"
#include "EatingComp.h"
#include <map>
class ComponentFactor
{
public:
	static map<int, string> componentsMap;
	static Component* createComponent(int type);
	ComponentFactor();
	~ComponentFactor();
};

