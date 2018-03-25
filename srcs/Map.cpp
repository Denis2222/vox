#include "Map.hpp"

		Map::Map(void)
{
	std::cout << "New map" << std::endl;

	this->program = new Shader();
	this->program->Load("chunk");

	this->texture = loadTexture("./assets/tileset.png");

	this->tg = this->threadGenerate();
	this->tb = this->threadBuild();


}

void 	Map::setInfos(int x, int y, int z, Map::INFO info)
{
	this->infos[x][0][z] = info;
}

Map::INFO	Map::getInfos(int x, int y, int z)
{
	return (this->infos[x][0][z]);
}

void 	Map::setChunkPtr(int x, int y, int z, Chunk *chunk)
{
	this->chunks[x][0][z] = chunk;
}

Chunk *Map::getChunk(int x, int y, int z)
{
	if (this->infos[x][y][z] > 0)
		return (this->chunks[x][y][z]);
	else
		std::cout << "get Chunk inexistant !!" << std::endl;
	return (NULL);
}

void 	generateAndBuildChunk(Chunk *c)
{
	struct timespec start, end, middle;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	c->generate();

	clock_gettime(CLOCK_MONOTONIC_RAW, &middle);

	c->build();

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	uint64_t delta_middle = (middle.tv_sec - start.tv_sec) * 1000000 + (middle.tv_nsec - start.tv_nsec) / 1000;
	uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

	std::cout << "Time to do : generate : " << delta_middle << " All : " << delta_us << std::endl;
}

void 	Map::threadPoolJob(void)
{
	int nbWorker = 8;
	int w = 0;

	std::list<Chunk*>::iterator	iter;
	Chunk						*c;

	while (1)
	{
		if (w < 4)
		{
			iter = this->chunkList.begin();
			while(iter != this->chunkList.end() && w < nbWorker)
			{
				c = (*iter);
				if (c->state == Chunk::STATE::INIT) { //One Task !
					if (this->distanceToChunk(c) > FAR_CHUNK+5)
					{
						c->state = Chunk::STATE::DELETE;
						std::cout << "Direct delete ! " << std::endl;
							continue;
					}
					c->state = Chunk::STATE::THREAD;
					w++;
					workers.push_back(std::thread(generateAndBuildChunk, c));
				}
				iter++;
			}
		}
		for (auto &i : workers) {
			if (i.joinable()) {
				i.join();
				w--;
			}
		}
		usleep(5000);
	}
}

void 	Map::threadJobGenerate(void)
{
	std::list<Chunk*>::iterator	iter;
	Chunk						*c;
	std::cout << "do something job generate " << std::endl;
	while (1)
	{
		iter = this->chunkList.begin();
		while(iter != this->chunkList.end())
		{
			c = (*iter);

			if (c->state == Chunk::STATE::DELETE)
			{
				this->setInfos(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, INFO::FREE);
				this->chunkList.remove(c);
				this->setChunkPtr(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, NULL);
				delete c;
				break;
			}
			if (c->state == Chunk::STATE::RENDER)
			{
				if (this->distanceToChunk(c) > FAR_CHUNK)
				{
					c->state = Chunk::STATE::DISABLE;
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
	std::cout << "do something " << std::endl;
	std::list<Chunk*>::iterator iter;
	Chunk *c;

	while (1)
	{
		iter = this->chunkList.begin();
		while(iter != this->chunkList.end())
		{
			c = (*iter);
			if (c->state == Chunk::STATE::GENERATE)
			{
				//c->build();
			}
			iter++;
		}
		usleep(5000);
	}
}

float	Map::distanceToChunk(Chunk *c)
{
	return (this->distanceToChunk(c->localCoord.x, c->localCoord.y, c->localCoord.z));
}

float	Map::distanceToChunk(int x, int y, int z)
{

	glm::vec3 c(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);

	glm::vec3 chunkCenter(CHUNK_SIZE / 2,CHUNK_SIZE / 2,CHUNK_SIZE / 2);
	glm::vec3 center = c + chunkCenter;

	float d = distance(center, this->position);
	//std::cout << "Distance avec le chunk 0 0 0 :" << d << std::endl;
	return (d);
}

void 	Map::updateChunkToLoad(void)
{
	int x = (floor(position.x / CHUNK_SIZE));
	int y = (floor(position.y / CHUNK_SIZE));
	int z = (floor(position.z / CHUNK_SIZE));

	for (int X = -CHUNK_VIEW; X <= CHUNK_VIEW; X++)
	{
		int Y=0;
		for (int Z = -CHUNK_VIEW; Z <= CHUNK_VIEW; Z++)
		{
			if (this->distanceToChunk(X+x, 0, Z+z) < FAR_CHUNK)
			{
				//std::cout << "Add to render" << std::endl;
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
}

void 	Map::SlowRender(void)
{
	std::list<Chunk*>::iterator	iter;
	Chunk *c;

	iter = this->chunkList.begin();
	while(iter != this->chunkList.end())
	{
		c = (*iter);
		if (c->state == Chunk::STATE::BUILD)
		{
			c->buildVAO();
			c->state = Chunk::STATE::RENDER;
		}
		if (c->state == Chunk::STATE::DISABLE)
		{
			c->cleanVAO();
			c->state = Chunk::STATE::DELETE;
		}
		iter++;
	}
}

void 	Map::Render(glm::mat4 view, glm::mat4 projection)
{
	std::list<Chunk*>::iterator	iter;
	Chunk *c;

	glm::mat4 model(1.0f);
	this->program->use();
	this->program->setInt("texture1", 0);
	this->program->setMat4("projection", projection);
	this->program->setMat4("model", model);
	this->program->setMat4("view", view);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	iter = this->chunkList.begin();
	while(iter != this->chunkList.end())
	{
		c = (*iter);
		if (c->state == Chunk::STATE::RENDER)
		{
			glBindVertexArray(c->VAO);
			glDrawArrays(GL_TRIANGLES, 0, c->getTriangle());
		}
		iter++;
	}
}

void 	Map::updatePosition(glm::vec3 position)
{
	this->position = position;
}
