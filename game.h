#pragma once
#include "template.h"
#include "surface.h"
#include "Components.h"
#include "Level.h"
#include "Timer.h"
#include <Windows.h>
#include <SDL.h>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <string>

namespace Tmpl8 {

class Surface;
class UserInterface;
class Game
{
public:
	enum class GameState
	{
		Menu,
		Playing,
		Paused
	};

	GameState gameState;

	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick(float);
	void CheckLevel();
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y) { mouseAxis.x = sCast<float>(x); mouseAxis.y = sCast<float>(y); }
	bool getState();
	vec2 getMouseAxis();
	Level::Stage getCurrentLevel();
	void KeyUp(int key) { }
	void KeyDown(int key) { }
private:
	Surface* screen;

	Player player;
	Level level;
	Menu menu;
	HUD hud;
	Map map;

	Level::Stage currentLevel{ Level::Stage::ONE };

	Sprite bg{ new Surface("assets/bgScroll.png"), 1 };
	Sprite opacityBg{ new Surface("assets/halfOpacityBackground.png"), 1 };
	Sprite m_map{ new Surface("assets/tutorialTileMap.png"), 1 };
	Surface coinSurface{ "assets/coinSpriteTest.png" };
	Sprite coin{ &coinSurface, 1 };

	int bgX{ 0 };
	int bgY{ 0 };
	int coinHitCount{ 0 };
	int readyTextTime{ 0 };
	
	vec2 mouseAxis{};

	bool isPlaying{ false };
	bool mouseDown{ false };
	bool mouseUp{ false };
	bool readyTextChecker{ false };

};

} // namespace Tmpl8