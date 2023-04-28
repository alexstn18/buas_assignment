#pragma once
#include "template.h"
#include "surface.h"
#include "Components.h"
#include "Timer.h" // Implementation by Jeremiah van Oosten (@jpvanoosten)
#include <Windows.h>
#include <SDL.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <Audio/Device.hpp> // Audio library from Jeremiah van Oosten (@jpvanoosten)

namespace Tmpl8 {

class Surface;
class UserInterface;
class Game
{
public:
	enum class GameState // game state machine
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
	SFX sfx;

	Level::Stage currentLevel{ Level::Stage::ONE }; // initializes the current level to start at stage 1

	Sprite bg{ new Surface("assets/bgScroll.png"), 1 };
	Sprite opacityBg{ new Surface("assets/halfOpacityBackground.png"), 1 };
	Sprite m_map{ new Surface("assets/tutorialTileMap.png"), 1 };

	int bgX{ 0 };
	int bgY{ 0 };
	int coinCount{ 0 };
	int readyTextTime{ 0 };
	
	vec2 mouseAxis{}; // vec2 variable that helds the x and y values of the mouseAxis => MouseMove function

	bool isPlaying{ false };
	bool hasFinishedGame{ false };
	bool mouseDown{ false };
	bool mouseUp{ false };
};

} // namespace Tmpl8