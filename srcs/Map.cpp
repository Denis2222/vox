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

int s = 20;
for (int x = 0; x < s; x++)
{

	for (int z = 0; z < s; z++)
	{

		int height = (int)(myModule.GetValue ((double)((double)x/20.0f), (double)((double)z/20.0f), 0.50) * 10) + 4;
		for (int y = 0; y < s; y++)
		{
			std::cout << x << y << z << std::endl;
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
/*
Chunk	Map::getChunk(int x, int y)
{
	Chunk chunk;
	return (chunk);
}
*/
