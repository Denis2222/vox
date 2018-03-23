#include "Chunk.hpp"

		Chunk::Chunk(void)
		{


		}

		Chunk::Chunk(int x, int y, int z)
		{
			//std::cout << "New Chunk : " << x << " " << y << " " << z << std::endl;
			this->localCoord = glm::vec3(x, y, z);
			this->worldCoord = glm::vec3(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);
			this->state = 0;
		}

		Chunk::~Chunk(void)
		{
			//std::cout << "Delete Chunk : " << this->worldCoord.x << " " << this->worldCoord.y << " " << this->worldCoord.z << std::endl;
			//delete points;
			//delete uvs;
			//delete world;
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
			int height = getNoise(x, z);
			for (int y = 0; y < 256; y++)
			{
				if (y <= height)
				{
					if (y < 40)
						world[x][y][z] = 2;
					else
						world[x][y][z] = 3;

					if (y >= this->maxheight)
						this->maxheight = y+4;
				}
				else{ // DU VIDE
					if (y <= this->minheight)
						this->minheight = y-4;
				}
				//else
					//world[x][y][z] = 1;
			}
		}
	}
	//std::cout << "minmax:" << this->minheight << this->maxheight << std::endl;
	this->state = 1;
}

bool	Chunk::collide(int x, int y, int z, int way)
{
	if (way == 1) // UP
	{
		if (y % CHUNK_SIZE == (CHUNK_SIZE - 1))
			if (getNoise(x, z) > y)
				return (true);
		if (this->world[x][y + 1][z] > 1)
			return (true);
		return (false);
	}
	if (way == 2) // DOWN
	{
		if (y % CHUNK_SIZE == 0)
			if (getNoise(x, z) > y)
				return (true);
		if (this->world[x][y - 1][z] > 1)
			return (true);
		return (false);
	}
	if (way == 3) // EST
	{
		if (getNoise(x + 1, z) >= y )
			return (true);
		if (this->world[x+1][y][z] > 1)
			return (true);
		return (false);
	}
	if (way == 4) // OUEST
	{
		if (getNoise(x - 1, z) >= y )
			return (true);
		if (this->world[x-1][y][z] > 1)
			return (true);
		return (false);
	}
	if (way == 5) // NORD
	{
		if (getNoise(x, z + 1) >= y )
			return (true);
		if (this->world[x][y][z+1] > 1)
			return (true);
		return (false);
	}
	if (way == 6) // SUD
	{
		if (getNoise(x, z - 1) >= y )
			return (true);
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

void	Chunk::buildFace(int n, int x, int y, int z, int val)
{
	static int oneFace = ((sizeof(VCUBE) / 4)/6);
	static int oneFaceUV = ((sizeof(VCUBEUV) / 4)/6);
	int u = n + 1;

	for (int i = oneFace * n; i < oneFace * u; i+=3)
	{
		glm::vec3 vec = glm::make_vec3(&VCUBE[i]);
		vec.x += (float)x*1;
		vec.y += (float)y*1;
		vec.z += (float)z*1;
		points.push_back(vec);
	}

	for (int i = oneFaceUV * n; i < oneFaceUV * u; i+=2)
	{
		glm::vec2 vec = glm::make_vec2(&VCUBEUV[i]);
		if (this->getWorld(x, y, z) == 2)
		{
			vec = glm::make_vec2(&VCUBEUVWATER[i]);
		}
		uvs.push_back(vec);
	}
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
			for (int y = this->minheight; y < this->maxheight; y++)
			{
				//std::cout << x<< y << z << std::endl;
				if (int val = this->getWorld(x, y, z) > 1)
				{
					// UP ///////////////////////////////////////////
					if (!this->collide(x, y, z, 1))
					{
						this->buildFace(0, x, y, z, val);
					}
					// DOWN ////////////////////////////////////////////
					if (!this->collide(x, y, z, 2))
					{
						this->buildFace(1, x, y, z, val);
					}
					//EST //////////////////////////////////////////////
					if (!this->collide(x, y, z, 3))
					{
						this->buildFace(2, x, y, z, val);
					}
					//OUEST ///////////////////////////////////////////////
					if (!this->collide(x, y, z, 4))
					{
						this->buildFace(3, x, y, z, val);
					}
					//NORD
					if (!this->collide(x, y, z, 5))
					{
						this->buildFace(4, x, y, z, val);
					}
					//SUD
					if (!this->collide(x, y, z, 6))
					{
						this->buildFace(5, x, y, z, val);
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

void	Chunk::cleanVAO(void)
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO_VERT);
	glDeleteBuffers(1, &this->VBO_UV);
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
