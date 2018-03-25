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

		void	setInfos(int x, int y, int z, Map::INFO info);
		void	setChunkPtr(int x, int y, int z, Chunk *chunk);
		void	updatePosition(glm::vec3 position);

		void 	updateChunkToLoad(void);


		void 	Render(glm::mat4 view, glm::mat4 projection);
		void 	SlowRender(void);
	private:
		std::map<int,std::map<int,std::map<int,Map::INFO> > > infos;

		std::thread threadDestroy;

		std::thread threadGenerate() {
			return std::thread(&Map::threadJobGenerate, this);
		}

		std::thread threadBuild() {
			return std::thread(&Map::threadJobBuild, this);
		}

		std::thread 			tg;
		std::thread 			tb;
		Shader 					*program;
		GLuint					texture;

		glm::vec3 				position;

		void 	threadJobGenerate(void);
		void 	threadJobBuild(void);

};

#endif
