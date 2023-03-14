#pragma once
#include "Surface.h"
#include "template.h"
#include "Entity.h"

using namespace Tmpl8;

class Entity;
class Map
{
public:
	void Init();
	void Render(Surface& screen);
private:
	void DrawTile(int tilex, int tiley, Surface& screen, int x, int y);
	Surface m_tiles{ "assets/myTiles.png" };

	enum Levels
	{
		level1,
		level2,
		level3
	};

	Levels levels;

	// this is just for a test
	char map[5][30] = {
	 "aa aa aa aa aa aa aa aa aa aa",
	 "aa fb fb fb aa aa aa aa aa aa",
	 "aa fb fb fb fb fb aa aa aa aa",
	 "aa lc lc fb fb fb aa aa aa aa",
	 "aa aa aa lc lc lc aa aa aa aa"
	};
};