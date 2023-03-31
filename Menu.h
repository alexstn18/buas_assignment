#pragma once
#include "template.h"
#include "surface.h"
#include <Windows.h>
#include <SDL.h>

namespace Tmpl8
{
	class Menu
	{
	public:
		void Render(Surface* screen);
		void Update(const vec2& mouseAxis, bool& playing);
	private:
		void ButtonChecker(const vec2& mouseAxis, bool& playing);

		Sprite logo{ new Surface("assets/logo.png"), 1 };

		Pixel textColor{ 0x0 };
		Pixel exitColor{ 0x0 };

		int menuTextX{ (ScreenWidth / 2) };
		int menuTextY{ ScreenHeight / 2 };
	};
}
