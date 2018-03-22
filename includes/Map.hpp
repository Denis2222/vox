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


		enum INFO
		{
			  EMPTY, 	// Not used
			  FREE,  	// Used & Free
			  GENERATE, // In world
			  CHUNK		// Chunk load
		};

		std::map<int,std::map<int,std::map<int,Map::INFO> > > infos;



		noise::module::Perlin myModule;

				Map(void);
		int		getWorld(int x, int y, int z);
		void 	generate(int sx, int sy, int sz);
		bool	collide3d(int x, int y, int z, int way);
		void 	setInfos(int x, int y, int z, Map::INFO info);
		void	updatePosition(glm::vec3 position);


		//Chunk	getChunk(int x, int y);
};

#endif
