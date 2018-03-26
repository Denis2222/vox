#ifndef TERRAIN_H
#define TERRAIN_H

#include <vox.h>

class Terrain
{
	public:
		std::map<int,std::map<int, char> > map;


		//std::map<glm::vec2, char> map2d;

		Terrain(void);
		~Terrain(void);
};

#endif
