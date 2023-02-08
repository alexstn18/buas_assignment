#pragma once
#include "template.h"
#include "Player.h"
#include <Windows.h>
#include <SDL.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

namespace Tmpl8 {

class Surface;
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
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { }
private:
	Sprite bg{ new Surface("assets/bgScroll.png"), 1 };
	int bgX = 0, bgY = 0;
	bool isPlaying = false;
	Surface* screen;
	vec2 mouseAxis{};
};

}; // namespace Tmpl8