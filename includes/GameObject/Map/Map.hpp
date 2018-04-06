#ifndef MAP_H
#define MAP_H

#include <mutex>
#include <GameObject/Map/Chunk.hpp>
#include <GameObject/Shader.hpp>

//using namespace noise;
class Shader;
class Chunk;

class Map
{
	public:
		std::map<int,std::map<int,Chunk*> > 	chunks;
		std::list<Chunk*> 									chunkList;
		std::list<Chunk*> 									renderList;
		std::mutex											mutex_infos;
		std::mutex											mutex_chunks;

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
		Chunk		*getChunkWorld(float x, float y, float z);

		void 		explode(int x, int y , int z);
		int			getBlockInfo(int x, int y, int z);
		int			getBlockInfo(glm::vec3 v) ;
		void 		getBlockInfoReallyMore(int qx,int qy,int  qz);

		void		updatePosition(glm::vec3 position);
		void 		updateChunkToLoad(void);
		void 		Render(glm::mat4 view, glm::mat4 projection, glm::vec3 position);
		void 		SlowRender(void);

	private:
		int 		chunkInit = 0;
		std::map<int,std::map<int,Map::INFO> >	infos;

		std::map<int, unsigned int> textures;

		unsigned int											nbWorker;
		unsigned int 											thread;
		std::vector<std::thread>								workers;
		std::vector<Chunk*>										workersTask;

		std::thread 											tp;

		Shader 													*program;
		GLuint													texture;
		glm::vec3 												position;
/*
		std::thread threadPool() {
			return ;
		}*/

		void			setChunkPtr(int x, int y, int z, Chunk *chunk);
		void			setInfos(int x, int y, int z, Map::INFO info);

		float			distanceToChunk(Chunk *c);
		float			distanceToChunk(int x, int y, int z);

		void 			threadPoolJob(void);

		unsigned int	loadTexture(const char *path);
};

#endif
