#include "Chunk.hpp"

float Chunk::vertex[108] = {

//FACE UP
	-0.5f , 0.5f, -0.5f,
	0.5f , 0.5f, 0.5f,
	0.5f , 0.5f, -0.5f,

	-0.5f , 0.5f, -0.5f,
	-0.5f , 0.5f, 0.5f,
	0.5f , 0.5f, 0.5f,
//FACE DOWN
	0.5f , -0.5f, 0.5f,
	-0.5f , -0.5f, -0.5f,
	0.5f , -0.5f, -0.5f,

	0.5f , -0.5f, 0.5f,
	-0.5f , -0.5f, 0.5f,
	-0.5f , -0.5f, -0.5f,
// FACE EST
	0.5f , 0.5f, -0.5f,
	0.5f , -0.5f, 0.5f,
	0.5f , -0.5f, -0.5f,

	0.5f , 0.5f, -0.5f,
	0.5f , 0.5f, 0.5f,
	0.5f , -0.5f, 0.5f,

//face ouest
	-0.5f , -0.5f, 0.5f,
	-0.5f , 0.5f, -0.5f,
	-0.5f , -0.5f, -0.5f,

	-0.5f , -0.5f, 0.5f,
	-0.5f , 0.5f, 0.5f,
	-0.5f , 0.5f, -0.5f,
//FACE NORD
	0.5f , 0.5f, 0.5f,
	-0.5f , -0.5f, 0.5f,
	0.5f , -0.5f, 0.5f,

	0.5f , 0.5f, 0.5f,
	-0.5f , 0.5f, 0.5f,
	-0.5f , -0.5f, 0.5f,
//FACE SUD
	0.5f , -0.5f, -0.5f,
	-0.5f , 0.5f, -0.5f,
	0.5f , 0.5f, -0.5f,

	0.5f , -0.5f, -0.5f,
	-0.5f , -0.5f, -0.5f,
	-0.5f , 0.5f, -0.5f
};

const float t1 = 0.332;
const float t2 = 0.667;

float Chunk::uv[72] = {

//FACE UP
		t1 , t2,
		0.0f , 1.0f,
		0.0f , t2,

		t1 , t2,
		t1 , 1.0f,
		0.0f , 1.0f,
//FACE DOWN
		1.0f , 0.0f,
		0.0f , 1.0f,
		0.0f , 0.0f,

		1.0f , 0.0f,
		1.0f , 1.0f,
		0.0f , 1.0f,
// FACE EST
		t1 , 1.0f,
		t2 , t2,
		t1 , t2,

		t1 , 1.0f,
		t2 , 1.0f,
		t2 , t2,

//face OUEST
t2 , t2,
		t1 , 1.0f,
		t1 , t2,

		t2 , t2,
		t1 , 1.0f,
		t2 , 1.0f,
//FAce nord
		t1 , 1.0f,
		t2 , t2,
		t1 , t2,

		t1 , 1.0f,
		t2 , 1.0f,
		t2 , t2,
//FACE SUD

		t2 , t2,
		t2 , 0.999f,
		t1 , 0.999f,

		t2 , t2,
		t1 , t2,
		t2, 0.999f,

	};

Chunk::Chunk(void)
{


}

void 	Chunk::customChunk(int sx, int sz, int sy, int size) {

	Map map;

	map.generate(sx, sy, sz);
	int oneFace = ((sizeof(vertex) / 4)/6);
	int oneFaceUV = ((sizeof(uv) / 4)/6);

	for (int x = sx; x < size + sx; x++)
	{
		std::cout << x << std::endl;
		for (int z = sz; z < size + sz; z++)
		{
			for (int y = 0; y < size + sy; y++)
			{
				//std::cout << x<< y << z << std::endl;
				if (map.world3d[x][y][z] > 0)
				{
					// UP ///////////////////////////////////////////
					if (!map.collide3d(x, y, z, 1))
					{
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
					if (!map.collide3d(x, y, z, 2))
					{
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
					if (!map.collide3d(x, y, z, 3))
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
					if (!map.collide3d(x, y, z, 4))
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
					if (!map.collide3d(x, y, z, 5))
					{
						for (int i = oneFace * 4; i < oneFace * 5; i+=3)
						{
							glm::vec3 vec = glm::make_vec3(&vertex[i]);
							vec.x += (float)x*1;
							vec.y += (float)y*1;
							vec.z += (float)z*1;
							points.push_back(vec);
						}

						for (int i = oneFaceUV * 4; i < oneFaceUV * 5; i+=2)
						{
							glm::vec2 vec = glm::make_vec2(&uv[i]);
							uvs.push_back(vec);
						}
					}
					//SUD
					if (!map.collide3d(x, y, z, 6))
					{
						for (int i = oneFace * 5; i < oneFace * 6; i+=3)
						{
							glm::vec3 vec = glm::make_vec3(&vertex[i]);
							vec.x += (float)x*1;
							vec.y += (float)y*1;
							vec.z += (float)z*1;
							points.push_back(vec);
						}

						for (int i = oneFaceUV * 5; i < oneFaceUV * 6; i+=2)
						{
							glm::vec2 vec = glm::make_vec2(&uv[i]);
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
