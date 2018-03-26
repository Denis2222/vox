#include "Map.hpp"

		Map::Map(void)
{
	std::cout << "New map" << std::endl;

	this->program = new Shader();
	this->program->Load("chunk");

	this->texture = loadTexture("./assets/tileset.png");

	this->tg = this->threadGenerate();
	this->tb = this->threadBuild();
	this->tp = this->threadPool();


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

void 	generateAndBuildChunk(Chunk *c, int i)
{
	std::cout << "START:" << i << std::endl;
	struct timespec start, end, middle;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	c->generate();

	clock_gettime(CLOCK_MONOTONIC_RAW, &middle);

	c->build();

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	uint64_t delta_middle = (middle.tv_sec - start.tv_sec) * 1000000 + (middle.tv_nsec - start.tv_nsec) / 1000;
	uint64_t delta_us = (end.tv_sec - middle.tv_sec) * 1000000 + (end.tv_nsec - middle.tv_nsec) / 1000;

	std::cout << "END:" << i << " " << delta_middle << ":" << delta_us << std::endl;
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
			int del = 0;
			while(iter != this->chunkList.end() && w < nbWorker && !del)
			{
				c = (*iter);
				if (c->state == Chunk::STATE::INIT) { //One Task !
					if (this->distanceToChunk(c) > FAR_CHUNK+5)
					{
						c->state = Chunk::STATE::DELETE;
						std::cout << "Direct delete ! " << std::endl;
					} else {
						c->state = Chunk::STATE::THREAD;
						workersTask.push_back(c);
						workers.push_back(std::thread(generateAndBuildChunk, c, workers.size()));
						w++;
					}
				}
				if (c->state == Chunk::STATE::DELETE)
				{
					this->setInfos(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, INFO::FREE);
					this->chunkList.remove(c);
					this->setChunkPtr(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, NULL);
					delete c;
					del = 1;
				}
				iter++;
			}
		}
		int u = 0;
		for (auto &i : workers) {
			if (i.joinable()) {
				c = workersTask.at(u);
				if (c->state != Chunk::STATE::THREAD)
				{
					i.join();
					workers.erase(workers.begin() + u);
					workersTask.erase(workersTask.begin() + u);
					w--;
				}
			}
			u++;
		}
		//std::cout << "Workers.size:" << workers.size() << std::endl;
		usleep(500);
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
		int init = 0;
		int render = 0;
		int disable = 0;
		int del = 0;
		iter = this->chunkList.begin();
		while(iter != this->chunkList.end())
		{
			c = (*iter);
			if (c->state == Chunk::STATE::INIT)
			{
				init++;
				//c->build();
			}
			if (c->state == Chunk::STATE::RENDER)
			{
				render++;
				//c->build();
			}
			if (c->state == Chunk::STATE::DISABLE)
			{
				disable++;
				//c->build();
			}
			if (c->state == Chunk::STATE::DELETE)
			{
				del++;
				//c->build();
			}
			iter++;
		}
		this->chunkInit = init;
		//std::cout << "init:" << init << "render:" << render << "disable:" << disable << "del:" << del << std::endl;
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

	int priority = CHUNK_VIEW;

	if (this->chunkInit > 10)
		priority = 1;

/*
	if (this->chunkList.size() < CHUNK_VIEW * 2)
		priority = CHUNK_VIEW / 4;
	else if (this->chunkList.size() < CHUNK_VIEW * 4)
		priority = CHUNK_VIEW / 2;
*/
	//std::cout << "Priority:" << priority << std::endl;
	for (int X = -priority; X <= priority; X++)
	{
		int Y=0;
		for (int Z = -priority; Z <= priority; Z++)
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
