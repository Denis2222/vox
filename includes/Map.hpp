#ifndef MAP_H
#define MAP_H

#include <Chunk.hpp>
#include <Shader.hpp>
//using namespace noise;
class Shader;
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

				Map(void);
				~Map(void);
		void 	generate(int sx, int sy, int sz);


		Chunk 		*getChunk(int x, int y, int z);
		Map::INFO	getInfos(int x, int y, int z);

		void	updatePosition(glm::vec3 position);

		void 	updateChunkToLoad(void);


		void 	Render(glm::mat4 view, glm::mat4 projection);
		void 	SlowRender(void);
	private:

		int chunkInit = 0; // Nb chunk in Chunk::STATE::INIT;

		std::map<int,std::map<int,std::map<int,Map::INFO> > > infos;

		std::thread threadDestroy;

		std::thread threadGenerate() {
			return std::thread(&Map::threadJobGenerate, this);
		}

		std::thread threadPool() {
			return std::thread(&Map::threadPoolJob, this);
		}

		std::thread threadBuild() {
			return std::thread(&Map::threadJobBuild, this);
		}

		std::vector<std::thread>	workers;
		std::vector<Chunk*>			workersTask;

		std::thread 			tg;
		std::thread 			tp;
		std::thread 			tb;

		Shader 					*program;
		GLuint					texture;

		glm::vec3 				position;

		void	setChunkPtr(int x, int y, int z, Chunk *chunk);
		void	setInfos(int x, int y, int z, Map::INFO info);

		float	distanceToChunk(Chunk *c);
		float	distanceToChunk(int x, int y, int z);

		void 	threadJobGenerate(void);
		void 	threadJobBuild(void);
		void 	threadPoolJob(void);

		//static void 	generateAndBuildChunk(Chunk *c);


};

#endif
