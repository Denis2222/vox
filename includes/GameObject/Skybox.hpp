#ifndef SKYBOX_H
#define SKYBOX_H

#include <vox.h>
class Camera;
class Shader;

class Skybox
{
	public:
		unsigned int 	ID;

		unsigned int 	textureID;

		unsigned int 	skyboxVAO;
		unsigned int 	skyboxVBO;

		unsigned int	cubemapTexture;
		Shader 			*shader;

						Skybox(void);
						~Skybox(void);
		void 			Load(void);
		unsigned int	loadCubemap(std::vector<std::string> faces);
		void 			render(Camera *camera);
};

#endif
