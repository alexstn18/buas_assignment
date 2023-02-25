#pragma once
#include "template.h"
#include "Components.h"
#include "Timer.h"
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
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y) { mouseAxis.x = sCast<float>(x); mouseAxis.y = sCast<float>(y); }
	vec2 getMouseAxis();
	void KeyUp(int key) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { }
	void Update(float);
private:
	Surface* screen;

	Timer* timer{ nullptr };

	Player player;
	UserInterface hud;
	Entity entity;
	Map map;

	Sprite bg{ new Surface("assets/bgScroll.png"), 1 };
	Sprite opacityBg{ new Surface("assets/halfOpacityBackground.png"), 1 };
	Sprite m_map{ new Surface("assets/tutorialTileMap.png"), 1 };

	int bgX{ 0 };
	int bgY{ 0 };
	int coinHitCount{ 0 };
	
	vec2 mouseAxis{};

	bool isPlaying{ false };
	bool mouseDown{ false };

};

} // namespace Tmpl8