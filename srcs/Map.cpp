#include "Map.hpp"
		Map::Map(void)
{
	std::cout << "New map" << std::endl;
	this->tg = this->threadGenerate();
	this->tb = this->threadBuild();
}

void 	Map::setInfos(int x, int y, int z, Map::INFO info)
{
	this->infos[x][0][z] = info;
}

void 	Map::setChunkPtr(int x, int y, int z, Chunk *chunk)
{
	this->chunks[x][0][z] = chunk;
}

void 	Map::threadJobGenerate(void)
{
	std::list<Chunk*>::iterator	iter;
	Chunk						*c;

	while (1)
	{
		iter = this->chunkList.begin();
		while(iter != this->chunkList.end())
		{
			c = (*iter);

			if (c->state == 5)
			{
				//std::cout << "DELETE !!!!!!!!!!!!!!!!!!" << std::endl;
				this->setInfos(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, INFO::FREE);
				this->chunkList.remove(c);
				this->setChunkPtr(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, NULL);
				delete c;
				break;
			}

			if (c->state == 0)
			{
				struct timespec start, end, middle;
				clock_gettime(CLOCK_MONOTONIC_RAW, &start);

				c->generate();
				clock_gettime(CLOCK_MONOTONIC_RAW, &middle);
				c->build();

				clock_gettime(CLOCK_MONOTONIC_RAW, &end);

				uint64_t delta_middle = (middle.tv_sec - start.tv_sec) * 1000000 + (middle.tv_nsec - start.tv_nsec) / 1000;
				uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
				//std::cout << "Time to do : generate : " << delta_middle << " All : " << delta_us << std::endl;
			}
			if (c->state == 3)
			{
				int x = (floor(position.x / CHUNK_SIZE));
				int z = (floor(position.z / CHUNK_SIZE));

				if ((c->localCoord.x < x-8 || c->localCoord.x > x+8) ||
					(c->localCoord.z < z-8 || c->localCoord.z > z+8))
				{
					c->state = 4;
				}
			}
			iter++;
		}
		this->updateChunkToLoad();
		usleep(5000);
	}
}

void 	Map::threadJobBuild(void)
{
	std::list<Chunk*>::iterator iter;
	Chunk *c;

	while (0)
	{
		iter = this->chunkList.begin();
		while(iter != this->chunkList.end())
		{
			c = (*iter);
			iter++;
		}
		usleep(500000);
	}
}

void 	Map::updateChunkToLoad(void)
{
	int x = (floor(position.x / CHUNK_SIZE));
	int y = (floor(position.y / CHUNK_SIZE));
	int z = (floor(position.z / CHUNK_SIZE));

	int var = 8;

	for (int X = -var; X <= var; X++)
	{
		int Y=0;
		for (int Z = -var; Z <= var; Z++)
		{
			if (this->infos[(X+x)][0][(Z+z)] < INFO::INIT)
			{
				int lx, ly, lz;
				lx = X+x;
				ly = Y+y;
				lz = Z+z;
				this->setInfos(lx ,0 ,lz, INFO::INIT);
				Chunk *chunk = new Chunk(lx ,0 ,lz);
				this->chunkList.push_back(chunk);
				this->setChunkPtr(lx ,0 ,lz, chunk);
			}
		}
	}
}

void 	Map::updatePosition(glm::vec3 position)
{
	this->position = position;
}
