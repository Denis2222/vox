#include "Chunk.hpp"

		Chunk::Chunk(void)
		{


		}

		Chunk::Chunk(int x, int y, int z)
		{
			std::cout << "New Chunk : " << x << y << z << std::endl;
			this->localCoord = glm::vec3(x, y, z);
			this->worldCoord = glm::vec3(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);
		}

void	Chunk::generate(void)
{
	int sx, sy, sz;
	sx = this->worldCoord.x;
	sy = this->worldCoord.y;
	sz = this->worldCoord.z;

	for (int x = sx; x < CHUNK_SIZE + sx; x++)
	{
		for (int z = sz; z < CHUNK_SIZE + sz; z++)
		{
			int height = (int)(noiseModule.GetValue ((double)((double)(x+20)/40.0f), (double)((double)(z+20)/40.0f), 0.40) * 10) + 20;
			for (int y = sy; y < CHUNK_SIZE + sy; y++)
			{
				if (y <= height)
					world[x][y][z] = 2;
				else
					world[x][y][z] = 1;
			}
		}
	}
	this->state = 1;
}

bool	Chunk::collide(int x, int y, int z, int way)
{
	if (way == 1) // UP
	{
		if (this->world[x][y + 1][z] > 1)
			return (true);
		return (false);
	}
	if (way == 2) // DOWN
	{
		if (this->world[x][y - 1][z] > 1)
			return (true);
		return (false);
	}
	if (way == 3) // EST
	{
		if (this->world[x+1][y][z] > 1)
			return (true);
		return (false);
	}
	if (way == 4) // OUEST
	{
		if (this->world[x-1][y][z] > 1)
			return (true);
		return (false);
	}
	if (way == 5) // NORD
	{
		if (this->world[x][y][z+1] > 1)
			return (true);
		return (false);
	}
	if (way == 6) // SUD
	{
		if (this->world[x][y][z-1] > 1)
			return (true);
		return (false);
	}
	return (false);
}

int		Chunk::getWorld(int x, int y, int z)
{
	return (this->world[x][y][z]);
}

void 	Chunk::build(void)
{
	int sx, sy, sz;
	sx = this->worldCoord.x;
	sy = this->worldCoord.y;
	sz = this->worldCoord.z;
	//this->generate(sx, sy, sz);
	int oneFace = ((sizeof(VCUBE) / 4)/6);
	int oneFaceUV = ((sizeof(VCUBEUV) / 4)/6);

	for (int x = sx; x < CHUNK_SIZE + sx; x++)
	{
		for (int z = sz; z < CHUNK_SIZE + sz; z++)
		{
			for (int y = 0; y < CHUNK_SIZE + sy; y++)
			{
				//std::cout << x<< y << z << std::endl;
				if (this->getWorld(x, y, z) > 1)
				{
					// UP ///////////////////////////////////////////
					if (!this->collide(x, y, z, 1))
					{
						for (int i = 0; i < oneFace; i+=3)
						{
							glm::vec3 vec = glm::make_vec3(&VCUBE[i]);
							vec.x += (float)x*1;
							vec.y += (float)y*1;
							vec.z += (float)z*1;
							points.push_back(vec);
						}

						for (int i = 0; i < oneFaceUV; i+=2)
						{
							glm::vec2 vec = glm::make_vec2(&VCUBEUV[i]);
							//std::cout << "vec: " << glm::to_string(vec) << std::endl;
							uvs.push_back(vec);
						}
					}
					// DOWN ////////////////////////////////////////////
					if (!this->collide(x, y, z, 2))
					{
						for (int i = oneFace; i < oneFace * 2; i+=3)
						{
							glm::vec3 vec = glm::make_vec3(&VCUBE[i]);
							vec.x += (float)x*1;
							vec.y += (float)y*1;
							vec.z += (float)z*1;
							points.push_back(vec);
						}

						for (int i = oneFaceUV; i < oneFaceUV * 2; i+=2)
						{
							glm::vec2 vec = glm::make_vec2(&VCUBEUV[i]);
							uvs.push_back(vec);
						}
					}
					//EST //////////////////////////////////////////////
					if (!this->collide(x, y, z, 3))
					{
						for (int i = oneFace * 2; i < oneFace * 3; i+=3)
						{
							glm::vec3 vec = glm::make_vec3(&VCUBE[i]);
							vec.x += (float)x*1;
							vec.y += (float)y*1;
							vec.z += (float)z*1;
							points.push_back(vec);
						}

						for (int i = oneFaceUV * 2; i < oneFaceUV * 3; i+=2)
						{
							glm::vec2 vec = glm::make_vec2(&VCUBEUV[i]);
							//std::cout << "vec: " << glm::to_string(vec) << std::endl;
							uvs.push_back(vec);
						}
					}
					//OUEST ///////////////////////////////////////////////
					if (!this->collide(x, y, z, 4))
					{
						for (int i = oneFace * 3; i < oneFace * 4; i+=3)
						{
							glm::vec3 vec = glm::make_vec3(&VCUBE[i]);
							vec.x += (float)x*1;
							vec.y += (float)y*1;
							vec.z += (float)z*1;
							points.push_back(vec);
						}

						for (int i = oneFaceUV * 3; i < oneFaceUV * 4; i+=2)
						{
							glm::vec2 vec = glm::make_vec2(&VCUBEUV[i]);
							//std::cout << "vec: " << glm::to_string(vec) << std::endl;
							uvs.push_back(vec);
						}
					}
					//NORD
					if (!this->collide(x, y, z, 5))
					{
						for (int i = oneFace * 4; i < oneFace * 5; i+=3)
						{
							glm::vec3 vec = glm::make_vec3(&VCUBE[i]);
							vec.x += (float)x*1;
							vec.y += (float)y*1;
							vec.z += (float)z*1;
							points.push_back(vec);
						}

						for (int i = oneFaceUV * 4; i < oneFaceUV * 5; i+=2)
						{
							glm::vec2 vec = glm::make_vec2(&VCUBEUV[i]);
							uvs.push_back(vec);
						}
					}
					//SUD
					if (!this->collide(x, y, z, 6))
					{
						for (int i = oneFace * 5; i < oneFace * 6; i+=3)
						{
							glm::vec3 vec = glm::make_vec3(&VCUBE[i]);
							vec.x += (float)x*1;
							vec.y += (float)y*1;
							vec.z += (float)z*1;
							points.push_back(vec);
						}

						for (int i = oneFaceUV * 5; i < oneFaceUV * 6; i+=2)
						{
							glm::vec2 vec = glm::make_vec2(&VCUBEUV[i]);
							uvs.push_back(vec);
						}
					}
				}
			}
		}
	}

	sizeuv = this->uvs.size() * sizeof(glm::vec2);
	sizevert = this->points.size() * sizeof(glm::vec3);
	nb = (this->points.size());

	this->state = 2;
}

unsigned int Chunk::buildVAO(void)
{
	/* BUFFER */
	//this->VAO;
	//unsigned int VBO[2];

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(2, &this->VBO_VERT);

	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_VERT);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeVertices(), this->getVertices(), GL_STATIC_DRAW);

	//Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_UV);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeUVs(), this->getUVs(), GL_STATIC_DRAW);
	//UV texture coords

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return (this->VAO);
}

float	*Chunk::getVertices(void)
{
	return (&this->points[0][0]);
}
size_t	Chunk::getSizeVertices(void)
{
	return (sizevert);
}

float	*Chunk::getUVs(void)
{
	return (&this->uvs[0][0]);
}
size_t	Chunk::getSizeUVs(void)
{
	return (sizeuv);
}

size_t	Chunk::getTriangle(void)
{
	return (nb);
}
