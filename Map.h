#pragma once
#include "Surface.h"
#include "template.h"
#include "Entity.h"

using namespace Tmpl8;

class Entity;
class Map
{
public:
	Map();
	~Map();
	void Init();
	void Draw(Surface* screen);
private:
};

