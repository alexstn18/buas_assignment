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
	void DrawTile(int tilex, int tiley, Surface& screen, int x, int y);
	void Draw(Surface& screen);
private:
	Surface m_tiles{ "assets/myTiles.png" };

	// this is just for a test
	char map[5][30] = {
	 "kc kc kc kc kc kc kc kc kc kc",
	 "kc fb fb fb kc kc kc kc kc kc",
	 "kc fb fb fb fb fb kc kc kc kc",
	 "kc lc lc fb fb fb kc kc kc kc",
	 "kc kc kc lc lc lc kc kc kc kc"
	};
};