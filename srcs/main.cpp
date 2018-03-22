/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:41:19 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/22 08:36:52 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vox.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

t_app	*root(void) {
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
void 	framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	std::cout << "Resize to :" << width << " * " << height << std::endl;
    glViewport(0, 0, width, height);
}
void 	processInput(t_app *app) {
    if(glfwGetKey(app->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(app->window, true);
}
int		init_glfw(t_app *app) {
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return (0);
	}
	app->width = WIDTH;
	app->height = HEIGHT;
	glfwWindowHint(GLFW_SAMPLES, 0);
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
	glfwSetInputMode(app->window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(app->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	//glfwSwapInterval(0);//delete fps limit
	//glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //WIREFRAME MODE
	//glDepthFunc(GL_LESS);
	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	return (1);
}
void 	mouse_callback(GLFWwindow* window, double xpos, double ypos);

Camera camera(0);



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

	//Map map;
	Chunk chunk;
	Chunk chunk2;
	chunk.customChunk(0,0,0, CHUNK_SIZE);

	glm::vec3 cubePositions[] = {
	  glm::vec3( 0.0f,  0.0f,  0.0f)
	};


	/* BUFFER */
	unsigned int VAO;
	unsigned int VBO[2];

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, &VBO[0]);

	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, chunk.getSizeVertices(), chunk.getVertices(), GL_STATIC_DRAW);

	//Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, chunk.getSizeUVs(), chunk.getUVs(), GL_STATIC_DRAW);
	//UV texture coords

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
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
	unsigned char *data = stbi_load("./assets/tileset.png", &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture : " << std::endl;
	}
	stbi_image_free(data);

	/* TEXTURE  1*/
/*
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
*/
	program.use();
	program.setInt("texture1", 0);
//	program.setInt("texture2", 1);

	glm::mat4 model(1.0f);
	glm::mat4 projection(1.0f);



	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	projection = glm::perspective(glm::radians(75.0f), ((float)app->width / (float)app->height), 0.1f, 700.0f);
	program.setMat4("projection", projection);
	glm::mat4 view(1.0f);

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	while (glfwGetKey(app->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(app->window) == 0)
	{

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame  fps:%d triangles:%zu \n", 1000.0/double(nbFrames), nbFrames, chunk.getTriangle() / 3);
			nbFrames = 0;
			lastTime += 1.0;

			std::cout << glm::to_string(camera.position) << std::endl;
			std::cout << glm::to_string(camera.front) << std::endl;
			std::cout << "yaw : " << camera.yaw << std::endl;
			std::cout << "pitch : " << camera.pitch << std::endl;
		}

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
/*
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
*/
		glBindVertexArray(VAO);
		for(unsigned int i = 0; i < 1; i++)
		{
		  glm::mat4 model;
		  model = glm::translate(model, cubePositions[i]);
		  program.setMat4("model", model);
		  glDrawArrays(GL_TRIANGLES, 0, chunk.getTriangle());
		}

		glfwSwapBuffers(app->window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteBuffers(1, &VBO[1]);

	glfwTerminate();
	return (0);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.mouse_callback(xpos,ypos);
}
