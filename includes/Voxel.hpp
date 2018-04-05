#ifndef VOXEL_H
#define VOXEL_H

#include <vox.h>
class Skybox;
class Map;
class Camera;
class Model;

class Voxel
{
	public:

		unsigned int	width;
		unsigned int	height;
		GLFWwindow		*window;
		Map 			*map;
		Camera			*camera;
		Skybox			*skybox;
		Terrain			*terrain;

		Model			*model;

		bool			nographics = false;
		bool			fullscreen = false;


						Voxel(int argc, char **argv);
						~Voxel(void);
		void			glfwStart (bool fullscreen);
		void			loop(void);
		void			mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void			processInput(void);
		void			initSkybox();
		void			renderSkybox(void);
};

#endif
