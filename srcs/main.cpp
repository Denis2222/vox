/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:41:19 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/23 15:34:52 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vox.h>
#include <Model.hpp>
#include <filesystem>

Camera camera(0);

int		main(int argc, char **argv)
{
	t_app	*app;

	app = root();
	init_glfw(app);

	if (!init_glfw(app))
	{
		printf("Failed to INIT GLFW\n");
		return (-1);
	}

	Map *map = new Map();

	map->updatePosition(camera.position);

	Shader program("learn");

	Shader modelShader("model");
	Model ourModel(Filesystem::getPath("assets/nanosuit/nanosuit.obj"));


	glClearColor(0.527f, 0.804f, 0.918f, 1.0f);
	unsigned int texture = loadTexture("./assets/tileset.png");

	program.use();
	program.setInt("texture1", 0);

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(75.0f), ((float)app->width / (float)app->height), 0.1f, FAR);
	program.setMat4("projection", projection);
	glm::mat4 view(1.0f);
	glm::mat4 model(1.0f);


	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	std::list<Chunk*>::iterator iter;
	Chunk *c;

	while (glfwGetKey(app->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(app->window) == 0)
	{

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 0.10 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame  fps:%d chunks:%lu\n", 100.0/double(nbFrames), nbFrames * 10, map->chunkList.size());
			nbFrames = 0;
			lastTime += 0.10f;

			map->updatePosition(camera.position);

			int x = (floor(camera.position.x / CHUNK_SIZE));
			int y = (floor(camera.position.y / CHUNK_SIZE));
			int z = (floor(camera.position.z / CHUNK_SIZE));

			iter = map->chunkList.begin();
			while(iter != map->chunkList.end())
			{
				c = (*iter);
				if (c->state == Chunk::STATE::BUILD)
				{
					c->buildVAO();
					c->state = Chunk::STATE::RENDER;
				}
				if (c->state == Chunk::STATE::DISABLE)
				{
					c->cleanVAO();
					c->state = Chunk::STATE::DELETE;
				}
				iter++;
			}

			//glm::mat4 MV = camera.getView() * model;
			glm::mat4 projection = glm::frustum(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);
			glm::vec4 viewport(0.0f,0.0f, (float)app->width , (float)app->height);

			glm::vec3 projected = glm::project(glm::vec3(10.0f, 0.0f, 10.0f), camera.getView(), projection, viewport);

			std::cout << glm::to_string(projected) << std::endl;

			std::cout << "cpos:" << glm::to_string(camera.position) << std::endl;
			std::cout << "cfront:" << glm::to_string(camera.front) << std::endl;

		}
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();
		processInput(app);
		camera.ProcessInput();



		//Physics
		Chunk *p;
		p = map->chunks[floor(camera.position.x / CHUNK_SIZE)][0][floor(camera.position.z / CHUNK_SIZE)];
		if (p->world[floor(camera.position.x)][floor(camera.position.y)][floor(camera.position.z)] > 0)
		{

		}
		else
		{
			camera.position.y-=0.1f;
		}
		glm::mat4 model(1.0f);
		program.setMat4("model", model);
		program.setMat4("view", camera.getView());




		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		iter = map->chunkList.begin();
		while(iter != map->chunkList.end())
		{
			c = (*iter);
			if (c->state == 3)
			{
				glBindVertexArray(c->VAO);
				glDrawArrays(GL_TRIANGLES, 0, c->getTriangle());
			}
			iter++;
		}

		glfwSwapBuffers(app->window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.mouse_callback(xpos,ypos);
}
