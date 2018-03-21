#include "Chunk.hpp"

Chunk::Chunk(void)
{
	/*int size = 1;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			for (int z = 0; z < size; z++)
			{


				int randy = 0;

				for (int i = 0; i < ((sizeof(vertex) / 4)); i+=3)
				{
					glm::vec3 vec = glm::make_vec3(&vertex[i]);
					vec.x += (float)x*1;
					vec.y += (float)y*1 + (float)randy;
					vec.z += (float)z*1;
					points.push_back(vec);
				}

				for (int i = 0; i < ((sizeof(uv) / 4)); i+=2)
				{
					glm::vec2 vec = glm::make_vec2(&uv[i]);
					//std::cout << "vec: " << glm::to_string(vec) << std::endl;
					uvs.push_back(vec);
				}
			}
		}
	}


	sizeuv = this->uvs.size() * sizeof(glm::vec2);
	sizevert = this->points.size() * sizeof(glm::vec3);
	nb = this->points.size() * 3;*/
}

bool	collide(std::map<int,std::map<int,int>> world, int x, int y, int z, int way)
{
	if (way == 1) // UP
	{
		if (world[x][z] > y + 1)
		{
			std::cout << "!!!!!!!!COLLIDE world x y : " << world[x][z] << std::endl;
			std::cout << " x: " << x << " y: " << y << " z: " << z << std::endl;
			return (true);
		}
		else
		{
			std::cout << "world x z : " << world[x][z] << std::endl;
			std::cout << "kick one poly x: " << x << " y: " << y << " z: " << z << std::endl;
			return (false);
		}
	}

	if (way == 3) // EST
	{
		if (world[x+1][z] > y + 1)
		{
			return (true);
		}
		else
		{
			return (false);
		}
	}
}

void 	Chunk::customChunk(std::map<int,std::map<int,int>> world , int sx, int sy, int size){

	int oneFace = ((sizeof(vertex) / 4)/6);
	int oneFaceUV = ((sizeof(uv) / 4)/6);

	for (int x = sx; x < size; x++)
	{
		for (int z = sy; z < size; z++)
		{

			for (int y = 0; y < world[x][z]; y++)
			{
				// UP
				if (!collide(world, x, y, z, 1))
				{
					std::cout << "Show UP" << std::endl;
					for (int i = 0; i < oneFace; i+=3)
					{
						glm::vec3 vec = glm::make_vec3(&vertex[i]);
						vec.x += (float)x*1;
						vec.y += (float)y*1;
						vec.z += (float)z*1;
						points.push_back(vec);
					}

					for (int i = 0; i < oneFaceUV; i+=2)
					{
						glm::vec2 vec = glm::make_vec2(&uv[i]);
						//std::cout << "vec: " << glm::to_string(vec) << std::endl;
						uvs.push_back(vec);
					}
				}
				//EST
				if (!collide(world, x, y, z, 3))
				{
					for (int i = oneFace * 2; i < oneFace * 3; i+=3)
					{
						glm::vec3 vec = glm::make_vec3(&vertex[i]);
						vec.x += (float)x*1;
						vec.y += (float)y*1;
						vec.z += (float)z*1;
						points.push_back(vec);
					}

					for (int i = oneFaceUV * 2; i < oneFaceUV * 3; i+=2)
					{
						glm::vec2 vec = glm::make_vec2(&uv[i]);
						//std::cout << "vec: " << glm::to_string(vec) << std::endl;
						uvs.push_back(vec);
					}
				}

				//NORD
				//if (!collide(world, x, y, z, 4))
				//{
					for (int i = oneFace * 3; i < oneFace * 4; i+=3)
					{
						glm::vec3 vec = glm::make_vec3(&vertex[i]);
						vec.x += (float)x*1;
						vec.y += (float)y*1;
						vec.z += (float)z*1;
						points.push_back(vec);
					}

					for (int i = oneFaceUV * 3; i < oneFaceUV * 4; i+=2)
					{
						glm::vec2 vec = glm::make_vec2(&uv[i]);
						//std::cout << "vec: " << glm::to_string(vec) << std::endl;
						uvs.push_back(vec);
					}
				//}

			}
		}
	}


	sizeuv = this->uvs.size() * sizeof(glm::vec2);
	sizevert = this->points.size() * sizeof(glm::vec3);
	nb = this->points.size() * 3;

}


bool	collide3d(std::map<int,std::map<int,std::map<int,int>>> world, int x, int y, int z, int way)
{
	if (way == 1) // UP
	{
		if (world[x][y + 1][z] > 0)
			return (true);
		return (false);
	}

	if (way == 2) // DOWN
	{
		if (world[x][y - 1][z] > 0)
			return (true);
		return (false);
	}

	if (way == 3) // EST
	{
		if (world[x+1][y][z] > 0)
			return (true);
		return (false);
	}
	if (way == 4) // OUEST
	{
		if (world[x-1][y][z] > 0)
			return (true);
		return (false);
	}
	if (way == 5) // NORD
	{
		if (world[x][y][z+1] > 0)
			return (true);
		return (false);
	}
	if (way == 6) // SUD
	{
		if (world[x][y][z-1] > 0)
			return (true);
		return (false);
	}
}

void 	Chunk::customChunk3D(std::map<int,std::map<int,std::map<int,int>>> world, int sx, int sz, int size){

	int oneFace = ((sizeof(vertex) / 4)/6);
	int oneFaceUV = ((sizeof(uv) / 4)/6);

	for (int x = sx; x < size; x++)
	{
		for (int z = sz; z < size; z++)
		{

			for (int y = 0; y < size; y++)
			{
				if (world[x][y][z] <= 0)
					break;
				// UP ///////////////////////////////////////////
				if (!collide3d(world, x, y, z, 1))
				{
					std::cout << "Show UP" << std::endl;
					for (int i = 0; i < oneFace; i+=3)
					{
						glm::vec3 vec = glm::make_vec3(&vertex[i]);
						vec.x += (float)x*1;
						vec.y += (float)y*1;
						vec.z += (float)z*1;
						points.push_back(vec);
					}

					for (int i = 0; i < oneFaceUV; i+=2)
					{
						glm::vec2 vec = glm::make_vec2(&uv[i]);
						//std::cout << "vec: " << glm::to_string(vec) << std::endl;
						uvs.push_back(vec);
					}
				}

				// DOWN ////////////////////////////////////////////
				if (!collide3d(world, x, y, z, 2))
				{
					std::cout << "Show DOWN" << std::endl;
					for (int i = oneFace; i < oneFace * 2; i+=3)
					{
						glm::vec3 vec = glm::make_vec3(&vertex[i]);
						vec.x += (float)x*1;
						vec.y += (float)y*1;
						vec.z += (float)z*1;
						points.push_back(vec);
					}

					for (int i = oneFaceUV; i < oneFaceUV * 2; i+=2)
					{
						glm::vec2 vec = glm::make_vec2(&uv[i]);
						uvs.push_back(vec);
					}
				}

				//EST //////////////////////////////////////////////

				if (!collide3d(world, x, y, z, 3))
				{
					for (int i = oneFace * 2; i < oneFace * 3; i+=3)
					{
						glm::vec3 vec = glm::make_vec3(&vertex[i]);
						vec.x += (float)x*1;
						vec.y += (float)y*1;
						vec.z += (float)z*1;
						points.push_back(vec);
					}

					for (int i = oneFaceUV * 2; i < oneFaceUV * 3; i+=2)
					{
						glm::vec2 vec = glm::make_vec2(&uv[i]);
						//std::cout << "vec: " << glm::to_string(vec) << std::endl;
						uvs.push_back(vec);
					}
				}

				//OUEST ///////////////////////////////////////////////
				if (!collide3d(world, x, y, z, 4))
				{
					for (int i = oneFace * 3; i < oneFace * 4; i+=3)
					{
						glm::vec3 vec = glm::make_vec3(&vertex[i]);
						vec.x += (float)x*1;
						vec.y += (float)y*1;
						vec.z += (float)z*1;
						points.push_back(vec);
					}

					for (int i = oneFaceUV * 3; i < oneFaceUV * 4; i+=2)
					{
						glm::vec2 vec = glm::make_vec2(&uv[i]);
						//std::cout << "vec: " << glm::to_string(vec) << std::endl;
						uvs.push_back(vec);
					}
				}

				//NORD
				//if (!collide(world, x, y, z, 4))
				//{
				/*
					for (int i = oneFace * 3; i < oneFace * 4; i+=3)
					{
						glm::vec3 vec = glm::make_vec3(&vertex[i]);
						vec.x += (float)x*1;
						vec.y += (float)y*1;
						vec.z += (float)z*1;
						points.push_back(vec);
					}

					for (int i = oneFaceUV * 3; i < oneFaceUV * 4; i+=2)
					{
						glm::vec2 vec = glm::make_vec2(&uv[i]);
						//std::cout << "vec: " << glm::to_string(vec) << std::endl;
						uvs.push_back(vec);
					}
				//}*/

			}
		}
	}


	sizeuv = this->uvs.size() * sizeof(glm::vec2);
	sizevert = this->points.size() * sizeof(glm::vec3);
	nb = (this->points.size());

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
