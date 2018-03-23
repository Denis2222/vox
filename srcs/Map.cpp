#include "Map.hpp"
		Map::Map(void)
{
	std::cout << "New map" << std::endl;
	this->tg = this->threadGenerate();
	this->tb = this->threadBuild();
	//this->tg.detach();
}

void 	Map::generate(int sx, int sy, int sz) {
	//std::cout << "Generate" << std::endl;
	/*
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
	*/
/*
	int localx, localy, localz;

	localx = floor(sx / CHUNK_SIZE);
	localy = floor(sy / CHUNK_SIZE);
	localz = floor(sz / CHUNK_SIZE);

	this->setInfos(localx, localy, localz, INFO::GENERATE);
	Chunk *chunk = new Chunk(localx, localy, localz);
	chunkList.push_back(chunk);*/
	//std::cout << "generate Over" << std::endl;
}



void 	Map::setInfos(int x, int y, int z, Map::INFO info)
{
	this->infos[x][y][z] = info;
}

void 	Map::setChunkPtr(int x, int y, int z, Chunk *chunk)
{
	this->chunks[x][y][z] = chunk;
}

void 	Map::threadJobGenerate(void)
{
	std::cout << "threadJobGenerate launch ()" << std::endl;

	std::list<Chunk*>::iterator iter;
	Chunk *c;

	while (1)
	{

		iter = this->chunkList.begin();

		while(iter != this->chunkList.end())
		{
			c = (*iter);
		    //
			if (c->state == 0)
			{
				c->generate();
				std::cout << "generate Chunk Done;" << std::endl;
			}
			iter++;
		}


		std::cout << "threadJobGenerate() sleep " << std::endl;
		sleep(1);
	}
}

void 	Map::threadJobBuild(void)
{
	std::cout << "threadJobBuild launch ()" << std::endl;

	std::list<Chunk*>::iterator iter;
	Chunk *c;

	while (1)
	{

		iter = this->chunkList.begin();

		while(iter != this->chunkList.end())
		{
			c = (*iter);
		    //
			if (c->state == 1)
			{
				c->build();
				std::cout << "build Chunk Done;" << std::endl;
				//break;
			}
			iter++;
		}


		std::cout << "threadJobBuild() sleep " << std::endl;
		sleep(1);
	}
}



void 	Map::updatePosition(glm::vec3 position)
{

	std::cout << "NB Chunk in list " << this->chunkList.size() << std::endl;

	std::list<Chunk*>::iterator iter;

	iter = this->chunkList.begin();

	//std::cout << "thread id :" << this->t1.get_id() << " thread::id "  << std::endl;

	//printf("====> %d <===", this->t1.get_id());
	Chunk *c;

	//if (t1.joignagle())
	/*
	while(iter != this->chunkList.end())
	{
		c = (*iter);
	    //
		if (c->state == 0)
		{
			//Launch thread
			threadReady = 0;
			std::cout << "launch thread" << std::endl;
			std::thread t1(thradBuildChunk, c);
			std::cout << "Launch " << glm::to_string(c->localCoord) << std::endl;
			t1.detach();
		}

		iter++;
	}*/

	/*if (threadReady == 0)
		return ;*/
//	std::cout << "Map::updatePosition" << glm::to_string(position)<< std::endl;


	//std::cout << "===> " << (floor(position.x / 50) * 50) << " " << floor(position.x / 50) << std::endl;
	//std::cout << "===> " << (floor(position.y / 50) * 50) << " " << floor(position.y / 50) << std::endl;
	//std::cout << "===> " << (floor(position.z / 50) * 50) << " " << floor(position.z / 50) << std::endl;

	//std::cout << "My Chunk is :" << (floor(position.x / CHUNK_SIZE) * CHUNK_SIZE) << " " << (floor(position.y / CHUNK_SIZE) * CHUNK_SIZE) << " " << (floor(position.z / CHUNK_SIZE) * CHUNK_SIZE) << std::endl;

	int x = (floor(position.x / CHUNK_SIZE));
	int y = (floor(position.y / CHUNK_SIZE));
	int z = (floor(position.z / CHUNK_SIZE));

	std::cout << "To load:" << std::endl;

	for (int X = -1; X < 2; X++)
	{
		for (int Y = -1; Y < 2; Y++)
		{
			for (int Z = -1; Z < 2; Z++)
			{
				//std::cout << "Check if chunk " << X+x << " " << Y+y << " " << Z+z << "   => " << this->infos[(X+x)][(Y+y)][(Z+z)] << "< " <<  INFO::INIT <<std::endl;
				if (this->infos[(X+x)][(Y+y)][(Z+z)] < INFO::INIT)
				{
					int lx, ly, lz;

					lx = X+x;
					ly = Y+y;
					lz = Z+z;

					this->setInfos(lx ,ly ,lz, INFO::INIT);
					Chunk *chunk = new Chunk(lx ,ly ,lz);
					this->chunkList.push_back(chunk);
					this->setChunkPtr(lx ,ly ,lz, chunk);

					//std::cout << "HERE => " << X+x << " " << Y+y << " " << Z+z << " Value = " << this->world3d[X+x][Y+y][Z+z] << std::endl;
					//	std::cout << "deja";
				}
				else
				{
					/*this->setInfos(X+x ,Y+y ,Z+z, INFO::START);
					//TODO Add to worker list

					std::thread t1(thradGenerateMap, this, (X+x) * CHUNK_SIZE, (Y+y) * CHUNK_SIZE, (Z+z) * CHUNK_SIZE);
					std::cout << "Gen launch thread : " << (X+x) * CHUNK_SIZE << " " << (Y+y) * CHUNK_SIZE << " " << (Z+z) * CHUNK_SIZE << std::endl;
					*/
					//t1.detach();
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
