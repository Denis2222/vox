#include "Map.hpp"

		Map::Map(void)
{
	std::cout << "New map" << std::endl;

	this->generate();
}

void Map::generate(void) {
	std::cout << "Generate" << std::endl;
	//std::map<int,std::map<int,int>> m;
/*
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{

		//	world[x][y] = 2;//(int)(myModule.GetValue ((double)((double)x/20.0f), (double)((double)y/20.0f), 0.50) * 10) + 4;
			if (world[x][y] <=1)
			 	world[x][y] = 1;
		}
	}
*/

int s = 100;
for (int x = 0; x < s; x++)
{

	for (int z = 0; z < s; z++)
	{

		int height = (int)(myModule.GetValue ((double)((double)x/20.0f), (double)((double)z/20.0f), 0.50) * 10) + 20;
		for (int y = 0; y < s; y++)
		{
			//std::cout << x << y << z << std::endl;
			if (y <= height)
				world3d[x][y][z] = 1;
			else
				world3d[x][y][z] = 0;
		}
	}
}

	std::cout << "generate Over" << std::endl;

	//Chunk chunk;
	//chunk.customChunk3D(world3d, 0,0,10);
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
}

/*
Chunk	Map::getChunk(int x, int y)
{
	Chunk chunk;
	return (chunk);
}
*/
