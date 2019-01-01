#include "Material.h"
#include <map>

using namespace std;

class MaterialCache
{
public:
	MaterialCache();
	~MaterialCache();
	map<string, Material> materialsCache;
private:

};

MaterialCache::MaterialCache()
{
}

MaterialCache::~MaterialCache()
{
}