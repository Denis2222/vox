#include "Chunk.hpp"

Chunk::Chunk(void)
{
	int size = 1;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			for (int z = 0; z < size; z++)
			{


				int randy = 0;

				for (int i = 0; i < ((sizeof(vertex) / 4) / 2); i+=3)
				{
					glm::vec3 vec = glm::make_vec3(&vertex[i]);
					vec.x += (float)x*2;
					vec.y += (float)y*2 + (float)randy;
					vec.z += (float)z*2;
					points.push_back(vec);
				}

				for (int i = 0; i < ((sizeof(uv) / 4) / 2); i+=2)
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
	nb = this->points.size() * 3;
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
