/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vox.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:25:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/23 15:59:41 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOX_H
# define VOX_H

# ifdef __linux__
#  define GL3_PROTOTYPES 1
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# include  <libnoise/noise.h>
#  define OPENGL_VERSION_MAJOR 3
#  define OPENGL_VERSION_MINOR 3
# endif


# ifdef __APPLE__
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# include  <noise/noise.h>
#  define OPENGL_VERSION_MAJOR 4
#  define OPENGL_VERSION_MINOR 0
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <libgen.h>
# include <pthread.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <ratio>
#include <chrono>

# define WIDTH 2500
# define HEIGHT 2000
# define TITLE "Voxel"
# define BASE_FOV 45.0f

#include <iostream>
//#define GLM_FORCE_SWIZZLE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"

//#include <Mesh.hpp>
#include <Shader.hpp>
#include "static.h"

#include "Map.hpp"

//#include <Model.hpp>
#include <Camera.hpp>
#include <Chunk.hpp>

#define CHUNK_SIZE 32
#define CHUNK_VIEW 8
#define FAR 500.0f

#define FAR_MAP 360.0f
#define FAR_CHUNK FAR_MAP+(CHUNK_SIZE*3)

typedef struct		s_app
{
	unsigned int	width;
	unsigned int	height;

	unsigned int	VAO2;
	unsigned int	chunk2size;

	bool			test;

	GLFWwindow		*window;
}					t_app;

t_app				*root(void);

int					init_glfw(t_app *app);
GLuint				shader_load(const char *name);

void				mouse_callback(GLFWwindow* window, double xpos, double ypos);
void				processInput(t_app *app);
void				framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int		loadTexture(const char *path);
int 				getNoise(int x, int y);


static int			g_oldstate;
#include "FastNoise.h"
static FastNoise myNoise;

#endif
