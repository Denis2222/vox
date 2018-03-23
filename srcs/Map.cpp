#include "Map.hpp"
		Map::Map(void)
{
	std::cout << "New map" << std::endl;
	this->tg = this->threadGenerate();
	this->tb = this->threadBuild();
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
	std::list<Chunk*>::iterator iter;
	Chunk *c;
	while (1)
	{
		//std::cout << "thread Job Generate" << std::endl;
		iter = this->chunkList.begin();
		while(iter != this->chunkList.end())
		{
			c = (*iter);
			if (c->state == 0)
			{
				c->generate();
				c->build();
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

	while (1)
	{
		//std::cout << "thread Job Build" << std::endl;
		iter = this->chunkList.begin();
		while(iter != this->chunkList.end())
		{
			c = (*iter);
		    //
			/*if (c->state == 1)
			{

			}*/
			if (c->state == 3)
			{
				glm::vec3 posY = this->position;
				posY.y = 0;
				if (floor(this->position.x / CHUNK_SIZE) - c->localCoord.x > FAR
					|| floor(this->position.z / CHUNK_SIZE) - c->localCoord.z > FAR)
				{
					c->state = 4;
					//Disable from rendering
				}
			}

			if (c->state == 5)
			{
				//It's time to clean !
				this->setInfos(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, INFO::FREE);
				this->chunkList.remove(c);
				this->setChunkPtr(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, NULL);
				delete c;
				break;
			}

			iter++;
		}
		usleep(5000);
	}
}

void 	Map::updateChunkToLoad(void)
{
	int x = (floor(position.x / CHUNK_SIZE));
	int y = (floor(position.y / CHUNK_SIZE));
	int z = (floor(position.z / CHUNK_SIZE));

	int var = 5;


	for (int X = -var; X < var + 1; X++)
	{
		//int Y=0;
		for (int Y = -1; Y < 1; Y++)
		{
			//int Y = 0;
			for (int Z = -var; Z < var + 1; Z++)
			{
				if (this->infos[(X+x)][(Y+y)][(Z+z)] < INFO::INIT)
				{
					//if ( glm::distance(posY, ) < FAR+CHUNK_SIZE)
					//{
					/*if (glm::distance(this->position, glm::vec3(X+x, Y+y, Z+z)) < FAR * 2)
					{*/
						int lx, ly, lz;
						lx = X+x;
						ly = Y+y;
						lz = Z+z;
						this->setInfos(lx ,ly ,lz, INFO::INIT);
						Chunk *chunk = new Chunk(lx ,ly ,lz);
						this->chunkList.push_back(chunk);
						this->setChunkPtr(lx ,ly ,lz, chunk);
					//}
				//	}
				}
			}
		}
	}
}

void 	Map::updatePosition(glm::vec3 position)
{
	this->position = position;
}
