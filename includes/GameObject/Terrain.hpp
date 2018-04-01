#ifndef TERRAIN_H
#define TERRAIN_H

#include <vox.h>
class Camera;
class Shader;

class Terrain
{
	public:
		unsigned int 	ID;

		unsigned int 	textureID;

		unsigned int 	VAO;
		unsigned int 	VBO;
		unsigned int 	EBO;

		unsigned int	cubemapTexture;
		Shader 			*shader;

						Terrain(void);
						~Terrain(void);
		void 			render(Camera *camera);
};

#endif
