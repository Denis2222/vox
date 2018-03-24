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

void 	Map::setChunkPtr(int x, int y, int z, Chunk *chunk)
{
	this->chunks[x][0][z] = chunk;
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
				//std::cout << "DELETE !!!!!!!!!!!!!!!!!!" << std::endl;
				this->setInfos(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, INFO::FREE);
				this->chunkList.remove(c);
				this->setChunkPtr(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, NULL);
				delete c;
				break;
			}

			if (c->state == Chunk::STATE::INIT)
			{
				struct timespec start, end, middle;
				//clock_gettime(CLOCK_MONOTONIC_RAW, &start);

				c->generate();
				//clock_gettime(CLOCK_MONOTONIC_RAW, &middle);


				clock_gettime(CLOCK_MONOTONIC_RAW, &end);

				//uint64_t delta_middle = (middle.tv_sec - start.tv_sec) * 1000000 + (middle.tv_nsec - start.tv_nsec) / 1000;
				//uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
				//std::cout << "Time to do : generate : " << delta_middle << " All : " << delta_us << std::endl;
			}
			if (c->state == Chunk::STATE::RENDER)
			{
				int x = (floor(position.x / CHUNK_SIZE));
				int z = (floor(position.z / CHUNK_SIZE));

				if ((c->localCoord.x < x-CHUNK_VIEW || c->localCoord.x > x+CHUNK_VIEW) ||
					(c->localCoord.z < z-CHUNK_VIEW || c->localCoord.z > z+CHUNK_VIEW))
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
				c->build();
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

	for (int X = -CHUNK_VIEW; X <= CHUNK_VIEW; X++)
	{
		int Y=0;
		for (int Z = -CHUNK_VIEW; Z <= CHUNK_VIEW; Z++)
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

void 	Map::onSlowRenderChunkVAOUpdate(void)
{
	std::list<Chunk*>::iterator	iter;
	Chunk 						*c;

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

void 	Map::onRenderChunks(glm::mat4 view, glm::mat4 projection)
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
		if (c->state == 3)
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
