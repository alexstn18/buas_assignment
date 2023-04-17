#pragma once
struct BoundingBox
{
	float left;
	float right;
	float top;
	float bottom;

	float previousLeft;
	float previousRight;
	float previousTop;
	float previousBottom;

	static bool AABB(const BoundingBox& a, const BoundingBox& b)
	{
		return(a.right > b.left &&
			a.left < b.right &&
			a.bottom > b.top &&
			a.top < b.bottom);
	}

	bool Intersect(const BoundingBox& other)
	{
		return(right > other.left &&
			left < other.right &&
			bottom > other.top &&
			top < other.bottom);
	}
};