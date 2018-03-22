#include "Map.hpp"
		Map::Map(void)
{
	std::cout << "New map" << std::endl;
}

void Map::generate(int sx, int sy, int sz) {
	std::cout << "Generate" << std::endl;
	int s = CHUNK_SIZE;
	for (int x = sx; x < s + sx; x++)
	{
		for (int z = sz; z < s + sz; z++)
		{
			int height = (int)(myModule.GetValue ((double)((double)(x+20)/40.0f), (double)((double)(z+20)/40.0f), 0.50) * 10) + 20;
			for (int y = sy; y < s + sy; y++)
			{
				if (y <= height)
					world3d[x][y][z] = 1;
				else
					world3d[x][y][z] = 0;
			}
		}
	}
	std::cout << "generate Over" << std::endl;
}

bool	Map::collide3d(int x, int y, int z, int way)
{
	if (way == 1) // UP
	{
		if (this->world3d[x][y + 1][z] > 0)
			return (true);
		return (false);
	}
	if (way == 2) // DOWN
	{
		if (this->world3d[x][y - 1][z] > 0)
			return (true);
		return (false);
	}
	if (way == 3) // EST
	{
		if (this->world3d[x+1][y][z] > 0)
			return (true);
		return (false);
	}
	if (way == 4) // OUEST
	{
		if (this->world3d[x-1][y][z] > 0)
			return (true);
		return (false);
	}
	if (way == 5) // NORD
	{
		if (this->world3d[x][y][z+1] > 0)
			return (true);
		return (false);
	}
	if (way == 6) // SUD
	{
		if (this->world3d[x][y][z-1] > 0)
			return (true);
		return (false);
	}
	return (false);
}

/*
Chunk	Map::getChunk(int x, int y)
{
	Chunk chunk;
	return (chunk);
}
*/
