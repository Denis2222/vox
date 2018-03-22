/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vox.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:25:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/22 08:37:30 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOX_H
# define VOX_H

# ifdef __linux__
#  define GL3_PROTOTYPES 1
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#  define OPENGL_VERSION_MAJOR 3
#  define OPENGL_VERSION_MINOR 3
# endif

# ifdef __APPLE__
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
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
# include  <noise/noise.h>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

# define WIDTH 800
# define HEIGHT 600
# define TITLE "Voxel"
# define BASE_FOV 45.0f

#include <iostream>
//#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/gtx/string_cast.hpp"

#include "Map.hpp"
#include <Shader.hpp>
#include <Camera.hpp>
#include <Chunk.hpp>

#define CHUNK_SIZE 200

typedef struct		s_app
{
	unsigned int	width;
	unsigned int	height;
	GLFWwindow		*window;
}					t_app;

t_app				*root(void);

int					init_glfw(t_app *app);
GLuint				shader_load(const char *name);


static int			g_oldstate;

#endif
