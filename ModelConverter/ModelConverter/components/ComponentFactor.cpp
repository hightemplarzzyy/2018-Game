#include "ComponentFactor.h"



map<int, string> ComponentFactor::componentsMap  = {
	{ 0, "Info" },
	{ 1, "Growing" },
	{ 2, "Life" },
	{ 3, "Spreader" },
	{ 4, "DynamicGrowing" },
	{ 5, "FoodComp" },
	{ 6, "Eating" }
};


Component* ComponentFactor::createComponent(int type)
{
	Component* component(nullptr);
	switch (type)
	{
	case 0:
		component = new InfoComp("Info", 0);
		component->getInfo();
		break;
	case 1:
		component = new GrowingComp("Growing", 1);
		component->getInfo();
		break;
	case 2:
		component = new LifeComp("Life", 2);
		component->getInfo();
		break;
	case 3:
		component = new SpreaderComp("Spreader", 3);
		component->getInfo();
		break;
	case 4:
		component = new DynamicGrowingComp("DynamicGrowing", 4);
		component->getInfo();
		break;
	case 5:
		component = new FoodComp("Food", 5);
		component->getInfo();
		break;
	case 6:
		component = new EatingComp("Eating", 6);
		component->getInfo();
		break;
	default:
		cout << "ÊäÈë±àºÅ´íÎó" << endl;
		break;
	}
	return component;
}

ComponentFactor::ComponentFactor()
{
}

ComponentFactor::~ComponentFactor()
{
}
