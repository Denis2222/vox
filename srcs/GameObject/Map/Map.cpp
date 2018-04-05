#include <GameObject/Map/Map.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <inttypes.h>

	Map::Map(void) {
		this->nbWorker = 16;
		this->thread = 1;
		this->program = new Shader();
		this->program->Load("chunk");

		for (const auto& tex : blocks_texture) {
			//std::cout << texture.first << " has value " << texture.second << std::endl;
			this->textures[tex.first] = this->loadTexture(tex.second.c_str());
			std::cout << this->textures[tex.first] << std::endl;
		}
		this->texture = this->textures[0];
		this->tp = std::thread(&Map::threadPoolJob, this);
		this->chunkInit = 0;
	}

	Map::~Map(void) {
		std::cout << "Delete map ask :" << std::endl;
		this->nbWorker = 0;

		while (workers.size()>0)
			usleep(5000);
		this->thread = 0;
		std::cout << "Worker stoped" << std::endl;
		tp.join();
		std::cout << "Thread Join" << std::endl;

		std::list<Chunk*>::iterator	iter;
		Chunk						*c;
		if (this->chunkList.size() > 0) {
			iter = this->chunkList.begin();
			while(iter != this->chunkList.end()) {
				c = (*iter);
				delete c;
				iter++;
			}
		}
		std::cout << "Chunk List delete" << std::endl;
		delete this->program;

		sleep(1);
	}

void 		Map::setInfos(int x, int y, int z, Map::INFO info) {
	this->mutex_infos.lock();
		this->infos[x][z] = info;
	this->mutex_infos.unlock();
}

Map::INFO	Map::getInfos(int x, int y, int z) {
	Map::INFO info;

	this->mutex_infos.lock();
		info = this->infos[x][z];
	this->mutex_infos.unlock();

	return (info);
}

void 		Map::setChunkPtr(int x, int y, int z, Chunk *chunk) {
	this->mutex_chunks.lock();
	this->chunks[x][z] = chunk;
	this->mutex_chunks.unlock();
}

Chunk 		*Map::getChunk(int x, int y, int z) {
	Chunk *c;

	c = NULL;
	if (this->getInfos(x, 0, z) > 0)
	{
		//printf("x:%d z:%d \n", x, z);
		this->mutex_chunks.lock();
		c = this->chunks[x][z];
		this->mutex_chunks.unlock();
	}
	return (c);
}

Chunk		*Map::getChunkWorld(float x, float y, float z) {
	int cx = round((int)x / CHUNK_SIZE);
	int cy = 0;
	int cz = round((int)z / CHUNK_SIZE);

	if (x < 0)
		cx = (x-CHUNK_SIZE) / CHUNK_SIZE;
	if (z < 0)
		cz = (z-CHUNK_SIZE) / CHUNK_SIZE;

	//printf("getChunkWorld %d %d %d \n", cx, cy, cz);
	Chunk *c = getChunk(cx, cy, cz);
	return (c);
}

Chunk		*Map::getChunkWorld(int x, int y, int z) {
	int cx = round(x / CHUNK_SIZE);
	int cy = 0;
	int cz = round(z / CHUNK_SIZE);

	if (x < 0)
		cx = (x-CHUNK_SIZE) / CHUNK_SIZE;
	if (z < 0)
		cz = (z-CHUNK_SIZE) / CHUNK_SIZE;

	//printf("getChunkWorld %d %d %d \n", cx, cy, cz);
	Chunk *c = getChunk(cx, cy, cz);
	return (c);
}

int			Map::getBlockInfo(glm::vec3 v) {
	//std::cout << "BEFORE Wth : V: " << glm::to_string(v) << std::endl;
	int x = ((int)round(v.x));
	int y = round(v.y);
	int z = ((int)round(v.z));
	Chunk *c = getChunkWorld(x, y, z);
	//std::cout << "AFTER Wth : V: " << glm::to_string(v) << std::endl;

	//printf("chunk:%f %f %f \n", c->localCoord.x, c->localCoord.y, c->localCoord.z);
	if (c)
		if (c->state > Chunk::STATE::BUILD)
		{
			x = (x - (int)c->worldCoord.x)%CHUNK_SIZE;
			y = y;
			z = (z - (int)c->worldCoord.z)%CHUNK_SIZE;
			//printf("block: x:%d y:%d z:%d \n", x, y, z);
			return (c->getWorld(			   x, y, z));
		}

	return (-1);
}

int			Map::getBlockInfo(int x, int y, int z) {
	Chunk *c = getChunkWorld(x, y, z);
	if (c)
		if (c->state > Chunk::STATE::BUILD)
			return (c->getWorld(x - (int)c->worldCoord.x, y, z - (int)c->worldCoord.z));

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
	//std::cout << "ChunkCoord:" << cx << " " << cy << " " << cz << " " << std::endl;
	if (c) {
		//std::cout << "VALUE:  x:" << x<< " y:" << y<< " z:" << z << " !! : " <<  c->world[x][y][z] << std::endl;
		//std::cout << "LocalCoord:" << c->localCoord.x << " " << c->localCoord.y << " " << c->localCoord.z << " " << std::endl;
	}
}

void 		generateAndBuildChunk(Chunk *c, int i) {
	//	static long long timegenerate = 0;
	//	static int nbgenerate = 0;

	//	static long long timebuild = 0;
	//	static int nbbuild = 0;

	//	struct timespec start, end, middle;
	//	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		c->generate();
	//	clock_gettime(CLOCK_MONOTONIC_RAW, &middle);
		c->build();
	//	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	//	uint64_t delta_middle = (middle.tv_sec - start.tv_sec) * 1000000 + (middle.tv_nsec - start.tv_nsec) / 1000;
	//	uint64_t delta_us = (end.tv_sec - middle.tv_sec) * 1000000 + (end.tv_nsec - middle.tv_nsec) / 1000;

	//	timegenerate+=delta_middle/1000;
	//	timebuild+= delta_us/1000;
	//	nbbuild++;
	//	nbgenerate++;
		//std::cout << "END:" << i << " " << delta_middle << ":" << delta_us << std::endl;
		//printf("Timer: %" PRIu64 " %" PRIu64 "\n", delta_middle, delta_us);


	//	printf("Average: %" PRIu64 " ms %" PRIu64 " ms\n", timegenerate/nbgenerate, timebuild/nbbuild);
}

void 		Map::threadPoolJob(void) {
	int w = 0;

	std::list<Chunk*>::iterator	iter;
	Chunk						*c;

	while (this->thread) {
		int full = 0;

		if (this->chunkList.size() > 0)
		{
			iter = this->chunkList.begin();
			while(iter != this->chunkList.end() && !full) {
				c = (*iter);
				if (c->state == Chunk::STATE::TOUPDATE) {
					//std::cout << "Update " << glm::to_string(c->localCoord) << std::endl;
					c->points.clear();
					c->uvs.clear();
					c->build();
					c->state = Chunk::STATE::UPDATE;
					full = 1;
				}
				if (c->state == Chunk::STATE::INIT) { //One Task !
					if (this->distanceToChunk(c) > FAR_CHUNK+5 || (this->chunkInit > MAX_CHUNK_INIT && this->distanceToChunk(c) > FAR_CHUNK/3))
					{
						c->state = Chunk::STATE::DELETE;
						this->chunkInit--;
						//std::cout << "Direct delete ! " << std::endl;
					} else if (w < this->nbWorker) {
						c->state = Chunk::STATE::THREAD;
						workersTask.push_back(c);
						workers.push_back(std::thread(generateAndBuildChunk, c, workers.size()));
						w++;
						full = 1;
					}
				}
				if (c->state == Chunk::STATE::DELETE) {
					this->setInfos(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, INFO::FREE);
					this->chunkList.remove(c);
					this->setChunkPtr(c->localCoord.x ,c->localCoord.y ,c->localCoord.z, NULL);
					delete c;
					full = 1;
					break;
				}
				if (c->state == Chunk::STATE::RENDER) {
					if (this->distanceToChunk(c) > FAR_CHUNK)
						c->state = Chunk::STATE::DISABLE;
				}
				iter++;
			}
		}

		int u = 0;
		if (workers.size() > 0)
		{
			for (auto &i : workers) {

				if (i.joinable()) {
					c = workersTask.at(u);
					if (c->state != Chunk::STATE::THREAD) {
						i.join();
						this->chunkInit--;
						//if (workers.size() >= u)
							workers.erase(workers.begin() + u);
						workersTask.erase(workersTask.begin() + u);
						w--;
					}
				}
				u++;

			}
		}


		if (!full) {
			this->updateChunkToLoad();
			usleep(3000);
		}
	}
}

void 		Map::updateChunkToLoad(void) {
	int x = (floor(position.x / CHUNK_SIZE));
	int y = (floor(position.y / CHUNK_SIZE));
	int z = (floor(position.z / CHUNK_SIZE));

	int priority = CHUNK_VIEW;

	int chunkAddPerPassage = 0;
	int Y=0;
	for (priority = 0; priority <= CHUNK_VIEW && chunkAddPerPassage<MAX_CHUNK_INIT && this->chunkInit < MAX_CHUNK_INIT; priority++) {
		for (int X = -priority; X <= priority && this->chunkInit < MAX_CHUNK_INIT; X++) {
			for (int Z = -priority; Z <= priority && this->chunkInit < MAX_CHUNK_INIT; Z++) {
				if (this->distanceToChunk(X+x, 0, Z+z) < FAR_CHUNK) {
					if (this->getInfos((X+x),0,(Z+z)) < INFO::INIT) {
						chunkAddPerPassage++;
						int lx, ly, lz;
						lx = X+x;
						ly = Y+y;
						lz = Z+z;
						this->setInfos(lx ,0 ,lz, INFO::INIT);
						Chunk *chunk = new Chunk(lx ,0 ,lz, this);
						this->chunkList.push_back(chunk);
						this->setChunkPtr(lx ,0 ,lz, chunk);
						this->chunkInit++;
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
	while(iter != this->chunkList.end()) {
		c = (*iter);
		if (c->state == Chunk::STATE::UPDATE) {
			c->updateVAO();
			c->state = Chunk::STATE::RENDER;
		}
		if (c->state == Chunk::STATE::BUILD) {
			c->buildVAO();
			c->state = Chunk::STATE::RENDER;
			this->renderList.push_back(c);
		}
		if (c->state == Chunk::STATE::DISABLE) {
			c->cleanVAO();
			this->renderList.remove(c);
			c->state = Chunk::STATE::DELETE;
		}
		iter++;
	}
}

void 		Map::Render(glm::mat4 view, glm::mat4 projection, glm::vec3 position) {
	std::list<Chunk*>::iterator	iter;
	Chunk *c;

	this->position = position;
	glm::mat4 modelidentity(1.0f);
	glm::mat4 model(1.0f);
	this->program->use();
	this->program->setMat4("projection", projection);
	this->program->setMat4("model", model);
	this->program->setMat4("view", view);


	glm::vec4 lightpos(this->position.x, 5000.0f,  this->position.z, 0);

	glm::vec4 toto = lightpos;

	this->program->setVec3("lightPos", toto);
/*
	this->program->setInt("texturelol[0]", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);*/

	for (const auto& tex : blocks_texture) {
		//std::cout << this->textures[tex.first] << std::endl;
		std::string idTextureShader = "texturelol[";
		idTextureShader+= std::to_string(tex.first);
		idTextureShader+= "]";
		//std::cout << idTextureShader << std::endl;
		this->program->setInt(idTextureShader.c_str(), tex.first);
		glActiveTexture(GL_TEXTURE0 + tex.first);
		glBindTexture(GL_TEXTURE_2D, this->textures[tex.first]);
	}

	iter = this->renderList.begin();
	//long nbtriangle = 0;
	//int nbchunks = 0;
	while(iter != this->renderList.end()) {
		c = (*iter);

		if (c->state == Chunk::STATE::RENDER || Chunk::STATE::TOUPDATE) {
			glm::mat4 myMatrix = glm::translate(model, c->worldCoord - this->position);
			this->program->setMat4("model", myMatrix);
			glBindVertexArray(c->VAO);
			glDrawArrays(GL_TRIANGLES, 0, c->getTriangle());
			//nbtriangle+=c->getTriangle();
			//nbchunks++;
		}
		iter++;
	}
	//std::cout << "Print triangle:" << nbtriangle << "Average:" << (nbtriangle / (nbchunks + 1) ) << " nbchunk:" <<nbchunks<< std::endl;
}

unsigned int Map::loadTexture(const char *path) {
	stbi_set_flip_vertically_on_load(true);
	/* TEXTURE  0*/
	unsigned int texture;
	glGenTextures(1 , &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture : " << std::endl;
	}

	stbi_image_free(data);
	return (texture);
}
