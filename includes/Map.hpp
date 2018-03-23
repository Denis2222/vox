#ifndef MAP_H
#define MAP_H

#include <vox.h>

//using namespace noise;

class Chunk;

class Map
{
	public:
		std::map<int,std::map<int,std::map<int,int> > > world3d;
		std::map<int,std::map<int,std::map<int,Chunk> > > chunks;

		std::list<Chunk*> chunkList;
		enum INFO
		{
			  EMPTY, 	// Not used
			  FREE,  	// Used & Free
			  START,
			  GENERATE, // In world
			  CHUNK		// Chunk load
		};

		std::map<int,std::map<int,std::map<int,Map::INFO> > > infos;

		std::thread t1;
		int threadReady = 1;
		std::mutex world3d_mutex;

		noise::module::Perlin myModule;

				Map(void);
		int		getWorld(int x, int y, int z);
		void 	generate(int sx, int sy, int sz);
		bool	collide3d(int x, int y, int z, int way);
		void 	setInfos(int x, int y, int z, Map::INFO info);
		void	updatePosition(glm::vec3 position);
		void 	threadBuildChunk(Chunk *chunk);

		//Chunk	getChunk(int x, int y);
};

#endif
