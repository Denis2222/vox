#ifndef MAP_H
#define MAP_H

#include <Chunk.hpp>
#include <Shader.hpp>
#include <mutex>

//using namespace noise;
class Shader;
class Chunk;

class Map
{
	public:
		std::map<int,std::map<int,std::map<int,Chunk*> > > 	chunks;
		std::list<Chunk*> 									chunkList;
		std::mutex											mutexList;

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
		Chunk		*getChunkWorld(int x, int y, int z);
		int			getBlockInfo(int x, int y, int z);
		void 		getBlockInfoReallyMore(int qx,int qy,int  qz);

		void		updatePosition(glm::vec3 position);
		void 		updateChunkToLoad(void);
		void 		Render(glm::mat4 view, glm::mat4 projection);
		void 		SlowRender(void);

	private:
		int 		chunkInit = 0;
		std::map<int,std::map<int,std::map<int,Map::INFO> > >	infos;

		std::vector<std::thread>								workers;
		std::vector<Chunk*>										workersTask;

		std::thread 											tg;
		std::thread 											tp;

		Shader 													*program;
		GLuint													texture;
		glm::vec3 												position;

		std::thread threadUpdate() {
			return std::thread(&Map::threadUpdateJob, this);
		}

		std::thread threadPool() {
			return std::thread(&Map::threadPoolJob, this);
		}

		void		setChunkPtr(int x, int y, int z, Chunk *chunk);
		void		setInfos(int x, int y, int z, Map::INFO info);

		float		distanceToChunk(Chunk *c);
		float		distanceToChunk(int x, int y, int z);

		void 		threadUpdateJob(void);
		void 		threadPoolJob(void);
};

#endif
