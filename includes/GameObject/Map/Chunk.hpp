#ifndef CHUNK_H
#define CHUNK_H

#include <vox.h>

class Map;

class Chunk
{
	public:
		enum STATE
		{
			  INIT, 	//Just New
			  GENERATE, //World ready
			  THREAD,   //Thread Processing
			  BUILD,	//Vertex & UV ready to bind
			  RENDER,	//Bind & In render while
			  TOUPDATE, //Need Update
			  UPDATE,	//Update ready
			  DISABLE,	//Out render and clean VAO from main thread
			  DELETE	//Ready to be delete
		};

		Chunk::STATE 									state;
		glm::vec3 										worldCoord;
		glm::vec3 										localCoord;

		unsigned int 									VAO;
		unsigned int 									VBO_VERT;
		unsigned int 									VBO_UV;

		size_t 											sizeuv;
		size_t 											sizevert;
		size_t 											nb;

		Map 											*map;
		std::vector<glm::vec3> 							points;
		std::vector<glm::vec2> 							uvs;

		std::map<int,std::map<int,std::map<int,int> > > world;

		int 											minheight = 256;
		int 											maxheight = 0;


					Chunk(void);
					Chunk(int x, int y, int z, Map *map);
					~Chunk(void);

		void 		interact(int x, int y, int z, int val);
		void		generate(void);



		void 		build(void);
		int 		getBlockType(int x, int y, int z, int height);
		void		buildFace(int n, int x, int y, int z, int val);

		bool		collide(int x, int y, int z, int way);
		bool		collideDebug(int x, int y, int z, int way);
		int			getWorld(int x, int y, int z);
		void		setWorld(int x, int y, int z, int val);

		float		*getVertices(void);
		size_t		getSizeVertices(void);
		float		*getUVs(void);
		size_t		getSizeUVs(void);
		size_t		getTriangle(void);


		unsigned int	buildVAO();
		void			updateVAO(void);
		void			cleanVAO(void);
};

#endif
