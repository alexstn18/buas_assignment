#include "Map.h"

// tile properties
constexpr int tileSize = 32;
constexpr int linii = 10;
constexpr int coloane = 5;

void Map::Init()
{
}
// credits: https://www.3dgep.com/cpp-fast-track-11-tiles/
void Map::DrawTile(int tilex, int tiley, Surface& screen, int x, int y)
{
	Pixel* src = m_tiles.GetBuffer() + 1 + tilex * (tileSize + 1) + (1 + tiley * (tileSize + 1)) * (ScreenHeight - 5);
	Pixel* dst = screen.GetBuffer() + x + y * ScreenWidth;
	for (int i = 0; i < tileSize; i++, src += (ScreenHeight - 5), dst += ScreenWidth)
	{
		for (int j = 0; j < tileSize; j++)
		{
			dst[j] = src[j];
		}
	}
}
// credits: https://www.3dgep.com/cpp-fast-track-11-tiles/
void Map::Render(Surface& screen)
{
	for (int y = 0; y < coloane; y++)
	{
		for (int x = 0; x < linii; x++)
		{
			int tilex = map[y][x * 3] - 'a';
			int tiley = map[y][x * 3 + 1] - 'a';
			DrawTile(tilex,
					 tiley,
					 screen,
					 x * tileSize,
					 y * tileSize);
		}
	}
}
