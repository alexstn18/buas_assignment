#pragma once
#include "template.h"
#include "surface.h"
#include "HUD.h"
#include <string>
#include <Windows.h>
#include <SDL.h>
#include <Audio/Sound.hpp>

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

		Audio::Sound menuSound{ "assets/sfx_menu_move3.wav", Audio::Sound::Type::Sound };
		/*
			Audio::Device::setMasterVolume(0.5f);

			Audio::Sound marioCoin{ "mario-coin-sound.mp3", Audio::Sound::Type::Sound };
			marioCoin.setVolume(0.2f);


			marioCoin.play();
		*/

		int menuTextX{ ScreenWidth / 2 };
		int menuTextY{ ScreenHeight / 2 };

		bool isHoveringPlay{ false };
		bool isHoveringExit{ false };
		bool finished{ false };
		bool gameOver{ false };
	};
}
