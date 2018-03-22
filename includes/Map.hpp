#ifndef MAP_H
#define MAP_H

#include <vox.h>

//using namespace noise;

class Map
{
	public:

		std::map<int,std::map<int,int> > world;

		std::map<int,std::map<int,std::map<int,int> > > world3d;

		noise::module::Perlin myModule;

				Map(void);
		void 	generate(int sx, int sy, int sz);
		bool	collide3d(int x, int y, int z, int way);
		//Chunk	getChunk(int x, int y);

};

#endif
