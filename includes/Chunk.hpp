#ifndef CHUNK_H
#define CHUNK_H

#include <vox.h>

class Map;

class Chunk
{
	public:
	//	static float vertex[108];
	//	static	float uv[72];

		int state = 0;

		glm::vec3 worldCoord;
		glm::vec3 localCoord;

		unsigned int VAO;
		unsigned int VBO_VERT;
		unsigned int VBO_UV;

		size_t sizeuv;
		size_t sizevert;
		size_t nb;

		std::vector<glm::vec3> points;
		std::vector<glm::vec2> uvs;

		noise::module::Perlin myModule;

		std::map<int,std::map<int,std::map<int,int> > > world;

				Chunk(void);
				Chunk(int x, int y, int z);
				~Chunk(void);
		void	cleanVAO(void);
		float	*getVertices(void);
		size_t	getSizeVertices(void);
		void	generate(void);
		void 	build(void);
		float	*getUVs(void);
		size_t	getSizeUVs(void);
		size_t	getTriangle(void);

		bool	collide(int x, int y, int z, int way);
		int		getWorld(int x, int y, int z);
		unsigned int buildVAO();
};

#endif
