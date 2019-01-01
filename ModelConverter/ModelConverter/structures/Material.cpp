#include "Material.h"
Material::Material(string name, Colour colour)
{
	this->name = name;
	this->colour = colour;
}

Material::Material()
{
}


Material::~Material()
{
}

Material::Colour::Colour(float flag, float code, float offset)
{
	this->flag = flag;
	this->code = code;
	this->offset = offset;
}