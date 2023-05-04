#pragma once
#include <Sound.hpp>

class SFX
{
public:
	SFX() = default; // default constructor

	// all of the audio files used in the game
	// CREDITS TO Juhani Junkala for his "The Essential Retro Video Game Sound Effects Collection [512 sounds]"
	// "The Essential Retro Video Game Sound Effects Collection [512 sounds]" is held under the Creative Commons CC0 License.
	// https://opengameart.org/content/512-sound-effects-8-bit-style
	Audio::Sound ambience{ "assets/sfx_windambience1.wav", Audio::Sound::Type::Music };
	Audio::Sound clickSound{ "assets/sfx_action_click.wav", Audio::Sound::Type::Sound };
	Audio::Sound bounceSound{ "assets/sfx_damage_hit9.wav", Audio::Sound::Type::Sound };
	Audio::Sound deathSound{ "assets/sfx_damage_hit10.wav", Audio::Sound::Type::Sound };
	Audio::Sound portalSound{ "assets/sfx_movement_portal1.wav", Audio::Sound::Type::Sound };
	Audio::Sound coinSound{ "assets/sfx_coin_double3.wav", Audio::Sound::Type::Sound };
	Audio::Sound winSound{ "assets/sfx_windows3point1_sound.wav", Audio::Sound::Type::Sound };
};	