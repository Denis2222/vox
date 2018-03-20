/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:41:19 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/19 08:15:16 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vox.h>
#include <cmath>
#include <Shader.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

t_app	*root(void)
{
	static t_app	*app = 0;

	if (app == 0)
	{
		app = (t_app*)malloc(sizeof(t_app));
		if (!app)
		{
			printf("General malloc fail root \n");
			exit(1);
		}
	}
	return (app);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Resize to :" << width << " * " << height << std::endl;
    glViewport(0, 0, width, height);
}

void processInput(t_app *app)
{
    if(glfwGetKey(app->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(app->window, true);
}

int		init_glfw(t_app *app)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return (0);
	}
	app->width = WIDTH;
	app->height = HEIGHT;
	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	app->window = glfwCreateWindow(app->width, app->height, TITLE, NULL, NULL);
	if (app->window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return (0);
	}
	glfwMakeContextCurrent(app->window);
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return (0);
	}
	glfwSetFramebufferSizeCallback(app->window, framebuffer_size_callback);
	//glfwSetInputMode(app->window, GLFW_STICKY_KEYS, GL_TRUE);
	//glfwSetInputMode(app->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	//glfwSwapInterval(0);//delete fps limit
	//glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //WIREFRAME MODE
	//glDepthFunc(GL_LESS);
	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	return (1);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    /*if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);*/
}

	Camera camera(0);

float rando()
{
	return ((float)(rand()%20));
}

int		main(int argc, char **argv)
{
	t_app	*app;

	app = root();

	if (!init_glfw(app))
	{
		printf("Failed to INIT GLFW\n");
		return (-1);
	}
	glfwSetCursorPosCallback(app->window, mouse_callback);
	float vertices[] = {
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,



		1+  -0.5f, 1+-0.5f, 1+-0.5f,  0.0f, 0.0f,
	 1+    0.5f, 1+-0.5f,1+ -0.5f,  1.0f, 0.0f,
	 1+    0.5f, 1+ 0.5f,1+ -0.5f,  1.0f, 1.0f,
	 1+    0.5f, 1+ 0.5f,1+ -0.5f,  1.0f, 1.0f,
	 1+   -0.5f, 1+ 0.5f,1+ -0.5f,  0.0f, 1.0f,
	 1+   -0.5f, 1+-0.5f,1+ -0.5f,  0.0f, 0.0f,

	 1+   -0.5f, 1+-0.5f,1+  0.5f,  0.0f, 0.0f,
	 1+    0.5f, 1+-0.5f,1+  0.5f,  1.0f, 0.0f,
	 1+    0.5f, 1+ 0.5f,1+  0.5f,  1.0f, 1.0f,
	 1+    0.5f, 1+ 0.5f,1+  0.5f,  1.0f, 1.0f,
	 1+   -0.5f, 1+ 0.5f,1+  0.5f,  0.0f, 1.0f,
	 1+   -0.5f, 1+-0.5f,1+  0.5f,  0.0f, 0.0f,

	 1+   -0.5f, 1+ 0.5f,1+  0.5f,  1.0f, 0.0f,
	 1+   -0.5f, 1+ 0.5f,1+ -0.5f,  1.0f, 1.0f,
	 1+   -0.5f, 1+-0.5f,1+ -0.5f,  0.0f, 1.0f,
	 1+   -0.5f, 1+-0.5f,1+ -0.5f,  0.0f, 1.0f,
	 1+   -0.5f, 1+-0.5f,1+  0.5f,  0.0f, 0.0f,
	 1+   -0.5f, 1+ 0.5f,1+  0.5f,  1.0f, 0.0f,

	 1+    0.5f, 1+ 0.5f,1+  0.5f,  1.0f, 0.0f,
	 1+    0.5f, 1+ 0.5f,1+ -0.5f,  1.0f, 1.0f,
	 1+    0.5f, 1+-0.5f,1+ -0.5f,  0.0f, 1.0f,
	 1+    0.5f, 1+-0.5f,1+ -0.5f,  0.0f, 1.0f,
	 1+    0.5f, 1+-0.5f,1+  0.5f,  0.0f, 0.0f,
	 1+    0.5f, 1+ 0.5f,1+  0.5f,  1.0f, 0.0f,

	 1+   -0.5f, 1+-0.5f,1+ -0.5f,  0.0f, 1.0f,
	 1+    0.5f, 1+-0.5f,1+ -0.5f,  1.0f, 1.0f,
	 1+    0.5f, 1+-0.5f,1+  0.5f,  1.0f, 0.0f,
	 1+    0.5f, 1+-0.5f,1+  0.5f,  1.0f, 0.0f,
	 1+   -0.5f, 1+-0.5f,1+  0.5f,  0.0f, 0.0f,
	 1+   -0.5f, 1+-0.5f,1+ -0.5f,  0.0f, 1.0f,

	 1+   -0.5f, 1+ 0.5f,1+ -0.5f,  0.0f, 1.0f,
	 1+    0.5f, 1+ 0.5f,1+ -0.5f,  1.0f, 1.0f,
	 1+    0.5f, 1+ 0.5f,1+  0.5f,  1.0f, 0.0f,
	 1+    0.5f, 1+ 0.5f,1+  0.5f,  1.0f, 0.0f,
	 1+   -0.5f, 1+ 0.5f,1+  0.5f,  0.0f, 0.0f,
	 1+   -0.5f, 1+ 0.5f,1+ -0.5f,  0.0f, 1.0f

	};

std::cout << rando() << std::endl;

	glm::vec3 cubePositions[] = {
	  glm::vec3( 0.0f,  0.0f,  0.0f),
	  glm::vec3( 2.0f,  -5.0f, 3.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -6.3f),
	  glm::vec3( 2.4f, -0.4f, -3.5f)
	};


	/* BUFFER */
	unsigned int VAO;
	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//UV texture coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	Shader program("learn");
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	stbi_set_flip_vertically_on_load(true);
	/* TEXTURE  0*/
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("./assets/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture : " << std::endl;
	}
	stbi_image_free(data);

	/* TEXTURE  1*/
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	data = stbi_load("./assets/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture : " << std::endl;
	}
	stbi_image_free(data);

	program.use();
	program.setInt("texture1", 0);
	program.setInt("texture2", 1);

	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);








	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)(app->width / app->height), 0.1f, 100.0f);
	program.setMat4("projection", projection);
	glm::mat4 view(1.0f);

	while (glfwGetKey(app->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(app->window) == 0)
	{
		processInput(app);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();

		//float greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
		//program.setFloat4("uniColor", 0,greenValue,0,0);

		camera.ProcessInput();
		view = camera.getView();

		glm::mat4 model(1.0f);


		program.setMat4("model", model);
		program.setMat4("view", view);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);
		for(unsigned int i = 0; i < 12; i++)
		{
		  glm::mat4 model;
		  model = glm::translate(model, cubePositions[i]);
		  float angle = 20.0f * i;
		  	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(15.0f * cubePositions[i][0]), glm::vec3(0.5f, 1.0f, 0.0f));
		  program.setMat4("model", model);

		  glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
		}



		glfwSwapBuffers(app->window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return (0);
}
