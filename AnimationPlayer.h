#pragma once
#include "surface.h"
#include "template.h"
#include "Timer.h"

using namespace Tmpl8;

class AnimationPlayer
{
public:
	void Init();
	void playAnim();
	void resetAnim();
private:
	void animChecker();
};