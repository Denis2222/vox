/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:41:19 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/23 08:22:04 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vox.h>

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

	//map->updatePosition(camera.position);
/*
	while (1)
	{
		usleep(1000000);
		std::cout << "." << std::endl;
	}
*///
//return (0);
	//Chunk chunk(0,0,0);

	//chunk.generate();
	//chunk.build();


	/* BUFFER */
	//chunk.buildVAO();

	Shader program("learn");
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	unsigned int texture = loadTexture("./assets/tileset.png");

	program.use();
	program.setInt("texture1", 0);


	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(75.0f), ((float)app->width / (float)app->height), 0.1f, 700.0f);
	program.setMat4("projection", projection);
	glm::mat4 view(1.0f);

	glm::mat4 model(1.0f);

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	app->test = 0;


	std::list<Chunk*>::iterator iter;
	Chunk *c;
	while (glfwGetKey(app->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(app->window) == 0)
	{

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame  fps:%d \n", 1000.0/double(nbFrames), nbFrames);
			nbFrames = 0;
			lastTime += 1.0;
			//std::cout << glm::to_string(camera.position) << std::endl;
			//std::cout << glm::to_string(camera.front) << std::endl;
			//std::cout << "yaw : " << camera.yaw << std::endl;
			//std::cout << "pitch : " << camera.pitch << std::endl;
			//std::cout << "app->test" <<  app->test << std::endl;
			map->updatePosition(camera.position);

			iter = map->chunkList.begin();
			while(iter != map->chunkList.end())
			{
				c = (*iter);
				//
				if (c->state == 2)
				{
					c->buildVAO();
					std::cout << "build VAO Done;" << std::endl;
					//break;
					c->state = 3;
				}
				iter++;
			}


		}

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();

		processInput(app);
		camera.ProcessInput();


		glm::mat4 model(1.0f);

		program.setMat4("model", model);
		program.setMat4("view", camera.getView());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);


		iter = map->chunkList.begin();
		while(iter != map->chunkList.end())
		{
			c = (*iter);
			//
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

	//glDeleteVertexArrays(1, &chunk.VAO);
	//glDeleteBuffers(1, &VBO[0]);
	//glDeleteBuffers(1, &VBO[1]);

	glfwTerminate();
	return (0);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.mouse_callback(xpos,ypos);
}
