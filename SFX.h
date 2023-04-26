#pragma once
#include <Audio/Sound.hpp>

class SFX
{
public:
	SFX() = default;

	Audio::Sound ambience{ "assets/sfx_windambience1.wav", Audio::Sound::Type::Music };
	Audio::Sound clickSound{ "assets/sfx_action_click.wav", Audio::Sound::Type::Sound };
	Audio::Sound bounceSound{ "assets/sfx_damage_hit9.wav", Audio::Sound::Type::Sound };
	Audio::Sound deathSound{ "assets/sfx_damage_hit10.wav", Audio::Sound::Type::Sound };
	Audio::Sound portalSound{ "assets/sfx_movement_portal1.wav", Audio::Sound::Type::Sound };
	Audio::Sound coinSound{ "assets/sfx_coin_double3.wav", Audio::Sound::Type::Sound };
	Audio::Sound winSound{ "assets/sfx_windows3point1_sound.wav", Audio::Sound::Type::Sound };
};