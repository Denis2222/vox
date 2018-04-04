/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vox.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:25:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/04/04 04:35:46 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOX_H
# define VOX_H

# ifdef __linux__
#  define GL3_PROTOTYPES 1
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
//# include  <libnoise/noise.h>
#  define OPENGL_VERSION_MAJOR 4
#  define OPENGL_VERSION_MINOR 4
# endif


# ifdef __APPLE__
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
//# include  <noise/noise.h>
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

# include <stb_image.h>

#include <iostream>
//#define GLM_FORCE_SWIZZLE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"

# define WIDTH 2048
# define HEIGHT 1024
# define TITLE "Voxel"
# define BASE_FOV 45.0f

#define CHUNK_SIZE 32
#define CHUNK_VIEW 16

#define FAR 1000.0f

#define CHUNK_HEIGHT 256

#define FAR_MAP 320.0f
#define FAR_CHUNK FAR_MAP+(CHUNK_SIZE*3)
#define MAX_CHUNK_INIT 15

//NVIDIA VRAM
#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049


#include "PerlinNoise.hpp"
#include "static.h"

#include <Camera.hpp>
#include <GameObject/Map/Map.hpp>
#include <GameObject/Map/Chunk.hpp>
#include <GameObject/Shader.hpp>
#include <GameObject/Skybox.hpp>
#include <GameObject/Terrain.hpp>
#include <Voxel.hpp>

int					getHeight(int x, int y);
int					getHeight(int x, int y, int z);
int 				getMoisture(int x, int y);
int					getBlockType(int x, int y, int z, int height);
glm::vec2 			getUVBlock(int val, int i);

void 				noiseParam(int seed);

int					parseLine(char* line);
int					getValue();

static int			g_oldstate;

#endif
