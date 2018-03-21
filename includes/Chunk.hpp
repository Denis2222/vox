#ifndef CHUNK_H
#define CHUNK_H

#include <vox.h>
#include <Map.hpp>

class Chunk
{
	public:
		float vertex[108] = {

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
		float uv[72] = {

//FACE UP
			1.0f , 0.0f,
			0.0f , 1.0f,
			0.0f , 0.0f,

			1.0f , 0.0f,
			1.0f , 1.0f,
			0.0f , 1.0f,
//FACE DOWN
			1.0f , 0.0f,
			0.0f , 1.0f,
			0.0f , 0.0f,

			1.0f , 0.0f,
			1.0f , 1.0f,
			0.0f , 1.0f,
// FACE EST
			1.0f , 0.0f,
			0.0f , 1.0f,
			0.0f , 0.0f,

			1.0f , 0.0f,
			1.0f , 1.0f,
			0.0f , 1.0f,
//face OUEST
			0.0f , 0.0f,
			1.0f , 1.0f,
			0.0f , 1.0f,

			0.0f , 0.0f,
			1.0f , 0.0f,
			1.0f , 1.0f,
//FAce nord
			1.0f , 0.0f,
			0.0f , 1.0f,
			0.0f , 0.0f,

			1.0f , 0.0f,
			1.0f , 1.0f,
			0.0f , 1.0f,
//FACE SUD
			1.0f , 0.0f,
			0.0f , 1.0f,
			0.0f , 0.0f,

			1.0f , 0.0f,
			1.0f , 1.0f,
			0.0f , 1.0f
		};

		size_t sizeuv;
		size_t sizevert;
		size_t nb;

		//std::vector<float> uvs;

		std::vector<glm::vec3> points;
		std::vector<glm::vec2> uvs;

				Chunk(void);
		float	*getVertices(void);
		size_t	getSizeVertices(void);

		void 	customChunk(Map *map, int sx, int sz, int size);
		float	*getUVs(void);
		size_t	getSizeUVs(void);

		size_t	getTriangle(void);

		//void 	customChunk(std::map<int,std::map<int,int>> world , int x, int y, int size);

};

#endif
