#include "Map.hpp"

	Map::Map(void) {
		this->program = new Shader();
		this->program->Load("chunk");
		this->texture = loadTexture("./assets/tileset.png");
		this->tg = this->threadUpdate();
		this->tp = this->threadPool();
	}

void 		Map::setInfos(int x, int y, int z, Map::INFO info) {
	this->infos[x][0][z] = info;
}

Map::INFO	Map::getInfos(int x, int y, int z) {
	return (this->infos[x][0][z]);
}

void 		Map::setChunkPtr(int x, int y, int z, Chunk *chunk) {
	this->chunks[x][0][z] = chunk;
}

Chunk 		*Map::getChunk(int x, int y, int z) {
	if (this->infos[x][y][z] > 0)
		return (this->chunks[x][y][z]);
	return (NULL);
}

Chunk		*Map::getChunkWorld(int x, int y, int z) {
	int cx = floor(x) / CHUNK_SIZE;
	int cy = 0;
	int cz = floor(z) / CHUNK_SIZE;

	if (x < 0)
		cx = (floor(x)-CHUNK_SIZE) / CHUNK_SIZE;
	if (z < 0)
		cz = (floor(z)-CHUNK_SIZE) / CHUNK_SIZE;

	Chunk *c = getChunk(cx, cy, cz);
	return (c);
}

int			Map::getBlockInfo(int x, int y, int z) {
	Chunk *c = getChunkWorld(x, y, z);
	if (c)
		if (c->state > Chunk::STATE::BUILD)
			return (c->getWorld(x, y, z));

	return (-1);
}

float		Map::distanceToChunk(Chunk *c) {
	return (this->distanceToChunk(c->localCoord.x, c->localCoord.y, c->localCoord.z));
}

float		Map::distanceToChunk(int x, int y, int z) {
	glm::vec3 c(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);
	glm::vec3 chunkCenter(CHUNK_SIZE / 2,CHUNK_SIZE / 2,CHUNK_SIZE / 2);
	glm::vec3 center = c + chunkCenter;

	float d = distance(center, this->position);
	return (d);
}

void 		Map::updatePosition(glm::vec3 position) {
	this->position = position;
}

void 		Map::getBlockInfoReallyMore(int x,int y,int z) {
	int cx = floor(x) / CHUNK_SIZE;
	int cy = 0;
	int cz = floor(z) / CHUNK_SIZE;

	if (x < 0)
	cx = (floor(x)-CHUNK_SIZE) / CHUNK_SIZE;
	if (z < 0)
	cz = (floor(z)-CHUNK_SIZE) / CHUNK_SIZE;

	Chunk *c = getChunk(cx, cy, cz);
	std::cout << "ChunkCoord:" << cx << " " << cy << " " << cz << " " << std::endl;
	if (c)
	{
		std::cout << "VALUE:  x:" << x<< " y:" << y<< " z:" << z << " !! : " <<  c->world[x][y][z] << std::endl;
		std::cout << "LocalCoord:" << c->localCoord.x << " " << c->localCoord.y << " " << c->localCoord.z << " " << std::endl;
	}
}

void 		generateAndBuildChunk(Chunk *c, int i) {
	//std::cout << "START:" << i << std::endl;
	//struct timespec start, end, middle;
	//clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	c->generate();
	//clock_gettime(CLOCK_MONOTONIC_RAW, &middle);
	c->build();
	//clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	//uint64_t delta_middle = (middle.tv_sec - start.tv_sec) * 1000000 + (middle.tv_nsec - start.tv_nsec) / 1000;
	//uint64_t delta_us = (end.tv_sec - middle.tv_sec) * 1000000 + (end.tv_nsec - middle.tv_nsec) / 1000;
	//std::cout << "END:" << i << " " << delta_middle << ":" << delta_us << std::endl;
}

void 		Map::threadPoolJob(void) {
	int nbWorker = 8;
	int w = 0;

	std::list<Chunk*>::iterator	iter;
	Chunk						*c;

	while (1)
	{
		int del = 0;
		if (w < 4)
		{
			iter = this->chunkList.begin();
			del = 0;
			while(iter != this->chunkList.end() && !del)
			{
				//std::cout << "HERE" << std::endl;
				c = (*iter);
				if (c->state == Chunk::STATE::INIT) { //One Task !
					if (this->distanceToChunk(c) > FAR_CHUNK+5 || this->chunkInit > 50 && this->distanceToChunk(c) > FAR_CHUNK/3)
					{
						c->state = Chunk::STATE::DELETE;
						std::cout << "Direct delete ! " << std::endl;
					} else if (w < nbWorker) {
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
				if (c->state == Chunk::STATE::RENDER)
				{
					if (this->distanceToChunk(c) > FAR_CHUNK)
					{
						c->state = Chunk::STATE::DISABLE;
					}
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
		if (!del)
			usleep(5000);
	}
}

void 		Map::threadUpdateJob(void) {
	std::list<Chunk*>::iterator	iter;
	Chunk						*c;


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
			if (c->state == Chunk::STATE::TOUPDATE)
			{
				std::cout << "Update " << glm::to_string(c->localCoord) << std::endl;
				c->points.clear();
				c->uvs.clear();
				c->build();
				c->state = Chunk::STATE::UPDATE;
			}
			if (c->state == Chunk::STATE::INIT)
				init++;
			if (c->state == Chunk::STATE::RENDER)
				render++;
			if (c->state == Chunk::STATE::DISABLE)
				disable++;
			if (c->state == Chunk::STATE::DELETE)
				del++;
			iter++;
		}
		this->chunkInit = init;
		this->updateChunkToLoad();
		usleep(5000);
	}
}

void 		Map::updateChunkToLoad(void) {
	int x = (floor(position.x / CHUNK_SIZE));
	int y = (floor(position.y / CHUNK_SIZE));
	int z = (floor(position.z / CHUNK_SIZE));

	int priority = CHUNK_VIEW;

	int chunkAddPerPassage = 0;

	for (priority = 0; priority <= CHUNK_VIEW && chunkAddPerPassage<50 && this->chunkInit < 50; priority++)
	{

		for (int X = -priority; X <= priority; X++)
		{

			int Y=0;
			for (int Z = -priority; Z <= priority; Z++)
			{

				if (this->distanceToChunk(X+x, 0, Z+z) < FAR_CHUNK)
				{
					if (this->infos[(X+x)][0][(Z+z)] < INFO::INIT)
					{
						chunkAddPerPassage++;
						int lx, ly, lz;
						lx = X+x;
						ly = Y+y;
						lz = Z+z;
						this->setInfos(lx ,0 ,lz, INFO::INIT);
						Chunk *chunk = new Chunk(lx ,0 ,lz, this);
						this->chunkList.push_back(chunk);
						this->setChunkPtr(lx ,0 ,lz, chunk);
					}
				}
			}
		}
	}
}

void 		Map::SlowRender(void) {
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

void 		Map::Render(glm::mat4 view, glm::mat4 projection) {
	std::list<Chunk*>::iterator	iter;
	Chunk *c;

	glm::mat4 modelidentity(1.0f);
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
		if (c->state == Chunk::STATE::UPDATE)
		{
			c->updateVAO();
			c->state = Chunk::STATE::RENDER;
		}
		if (c->state == Chunk::STATE::RENDER || Chunk::STATE::TOUPDATE)
		{
			glBindVertexArray(c->VAO);
			glDrawArrays(GL_TRIANGLES, 0, c->getTriangle());
		}
		iter++;
	}
}
