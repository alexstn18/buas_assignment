#pragma once
#include "surface.h"
#include "template.h"
#include "Level.h"
#include <vector>

using namespace Tmpl8;

class LevelManager
{
public:
	std::vector<Level*> levels;

	void LoadLevel();
	void DisplayLevel();
private:
	// Sprite m_level1_map{ new Surface("assets/tutorialTileMap.png"), 1 };
	// Sprite m_level2_map{ new Surface("assets/tutorialTileMap.png"), 1 };
	// Sprite m_level3_map{ new Surface("assets/tutorialTileMap.png"), 1 };
};