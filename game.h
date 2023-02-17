#pragma once
#include "template.h"
#include "Components.h"
#include <Windows.h>
#include <SDL.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

namespace Tmpl8 {

class Surface;
class UserInterface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int button) { }
	void MouseMove(int x, int y) { mouseAxis.x = x; mouseAxis.y = y; }
	void KeyUp(int key) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { }
	void Update();
private:
	Sprite bg{ new Surface("assets/bgScroll.png"), 1 };
	Sprite opacityBg{ new Surface("assets/halfOpacityBackground.png"), 1 };
	// Surface tiles("assets/rogueDBtiles.png");
	int bgX = 0, bgY = 0;
	int coinHitCount = 0;
	bool isPlaying = false;
	Surface* screen;
	vec2 mouseAxis{};

	Player player;
	UserInterface hud;
	Entity entity;
	Map map;
	// Collider col;
};

} // namespace Tmpl8