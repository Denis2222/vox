#ifndef CHUNK_H
#define CHUNK_H

#include <vox.h>

class Map;

class Chunk
{
	public:
		static float vertex[108];



	static	float uv[72];

		size_t sizeuv;
		size_t sizevert;
		size_t nb;

		std::vector<glm::vec3> points;
		std::vector<glm::vec2> uvs;

				Chunk(void);
		float	*getVertices(void);
		size_t	getSizeVertices(void);
		void 	customChunk(int sx, int sy, int sz,int size);
		float	*getUVs(void);
		size_t	getSizeUVs(void);
		size_t	getTriangle(void);
};

#endif
