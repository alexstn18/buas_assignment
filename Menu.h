#pragma once
#include "template.h"
#include "surface.h"
#include "HUD.h"
#include <string>
#include <Windows.h>
#include <SDL.h>

namespace Tmpl8
{
	class Menu
	{
	public:
		void Render(Surface* screen, HUD& hud);
		void Update(const vec2& mouseAxis, bool& finished, bool& gameOver);
		void ButtonChecker(const vec2& mouseAxis, bool& playing);
	private:
		Sprite logo{ new Surface("assets/logoInvert.png"), 1 };
		Sprite winImage{ new Surface("assets/winImage.png"), 1};

		Pixel textColor{ 0x0 };
		Pixel exitColor{ 0x0 };

		int menuTextX{ ScreenWidth / 2 };
		int menuTextY{ ScreenHeight / 2 };

		bool isHoveringPlay{ false };
		bool isHoveringExit{ false };
		bool finished{ false };
		bool gameOver{ false };
	};
}
