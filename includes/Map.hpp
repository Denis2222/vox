#ifndef MAP_H
#define MAP_H

#include <Chunk.hpp>

//using namespace noise;

class Chunk;

class Map
{
	public:
		//std::map<int,std::map<int,std::map<int,int> > > world3d;
		std::map<int,std::map<int,std::map<int,Chunk*> > > chunks;

		std::list<Chunk*> chunkList;
		enum INFO
		{
			  EMPTY, 	// Not used
			  FREE,  	// Used & Free
			  INIT,
			  GENERATE, // In world
			  CHUNK		// Chunk load
		};

		std::map<int,std::map<int,std::map<int,Map::INFO> > > infos;

		std::thread threadDestroy;

		std::thread threadGenerate() {
			return std::thread(&Map::threadJobGenerate, this);
		}

		std::thread threadBuild() {
			return std::thread(&Map::threadJobBuild, this);
		}

		std::thread tg;
		std::thread tb;

		glm::vec3 position;

		std::mutex world3d_mutex;

		noise::module::Perlin myModule;

				Map(void);
				~Map(void);
		void 	generate(int sx, int sy, int sz);

		void	setInfos(int x, int y, int z, Map::INFO info);
		void	setChunkPtr(int x, int y, int z, Chunk *chunk);
		void	updatePosition(glm::vec3 position);


		void 	updateChunkToLoad(void);
		void 	threadJobGenerate(void);
		void 	threadJobBuild(void);
		//Chunk	getChunk(int x, int y);
};

#endif
