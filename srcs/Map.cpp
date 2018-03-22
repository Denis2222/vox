#include "Map.hpp"
		Map::Map(void)
{
	std::cout << "New map" << std::endl;
}

void 	Map::generate(int sx, int sy, int sz) {
	//std::cout << "Generate" << std::endl;
	int s = CHUNK_SIZE;
	for (int x = sx; x < s + sx; x++)
	{
		for (int z = sz; z < s + sz; z++)
		{
			int height = (int)(myModule.GetValue ((double)((double)(x+20)/40.0f), (double)((double)(z+20)/40.0f), 0.50) * 10) + 20;
			for (int y = sy; y < s + sy; y++)
			{
				if (y <= height)
					world3d[x][y][z] = 2;
				else
					world3d[x][y][z] = 1;
			}
		}
	}
	this->setInfos(floor(sx / 50), floor(sy / 50), floor(sz / 50), INFO::GENERATE);
	//std::cout << "generate Over" << std::endl;
}

bool	Map::collide3d(int x, int y, int z, int way)
{
	if (way == 1) // UP
	{
		if (this->world3d[x][y + 1][z] > 1)
			return (true);
		return (false);
	}
	if (way == 2) // DOWN
	{
		if (this->world3d[x][y - 1][z] > 1)
			return (true);
		return (false);
	}
	if (way == 3) // EST
	{
		if (this->world3d[x+1][y][z] > 1)
			return (true);
		return (false);
	}
	if (way == 4) // OUEST
	{
		if (this->world3d[x-1][y][z] > 1)
			return (true);
		return (false);
	}
	if (way == 5) // NORD
	{
		if (this->world3d[x][y][z+1] > 1)
			return (true);
		return (false);
	}
	if (way == 6) // SUD
	{
		if (this->world3d[x][y][z-1] > 1)
			return (true);
		return (false);
	}
	return (false);
}
int		Map::getWorld(int x, int y, int z)
{
	return (this->world3d[x][y][z]);
}

void 	Map::setInfos(int x, int y, int z, Map::INFO info)
{
	this->infos[x][y][z] = info;
}

void 	Map::updatePosition(glm::vec3 position)
{
//	std::cout << "Map::updatePosition" << glm::to_string(position)<< std::endl;


	//std::cout << "===> " << (floor(position.x / 50) * 50) << " " << floor(position.x / 50) << std::endl;
	//std::cout << "===> " << (floor(position.y / 50) * 50) << " " << floor(position.y / 50) << std::endl;
	//std::cout << "===> " << (floor(position.z / 50) * 50) << " " << floor(position.z / 50) << std::endl;

	//std::cout << "My Chunk is :" << (floor(position.x / CHUNK_SIZE) * CHUNK_SIZE) << " " << (floor(position.y / CHUNK_SIZE) * CHUNK_SIZE) << " " << (floor(position.z / CHUNK_SIZE) * CHUNK_SIZE) << std::endl;

	int x = (floor(position.x / CHUNK_SIZE));
	int y = (floor(position.y / CHUNK_SIZE));
	int z = (floor(position.z / CHUNK_SIZE));

	//std::cout << "To load:" << std::endl;

	for (int X = -1; X < 2; X++)
	{
		for (int Y = -1; Y < 2; Y++)
		{
			for (int Z = -1; Z < 2; Z++)
			{

				if (this->world3d[(X+x) * CHUNK_SIZE][(Y+y) * CHUNK_SIZE][(Z+z) * CHUNK_SIZE] > 0)
				{
					//std::cout << "HERE => " << X+x << " " << Y+y << " " << Z+z << " Value = " << this->world3d[X+x][Y+y][Z+z] << std::endl;
				//	std::cout << "deja";
				}
				else
				{
					//TODO Add to worker list
					//std::cout << "Gen : " << (X+x) * CHUNK_SIZE << " " << (Y+y) * CHUNK_SIZE << " " << (Z+z) * CHUNK_SIZE << std::endl;
					this->generate((X+x) * CHUNK_SIZE, (Y+y) * CHUNK_SIZE, (Z+z) * CHUNK_SIZE);
				}
			}
		}
	}

}

/*
Chunk	Map::getChunk(int x, int y)
{
	Chunk chunk;
	return (chunk);
}
*/
