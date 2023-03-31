#pragma once
#include "template.h"

using namespace Tmpl8;

struct Line
{
	vec2 p0, p1;
	Line(const vec2& point0, const vec2& point1)
	{
		p0 = point0;
		p1 = point1;
	}
};