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

#define RENDER glfwGetKey(app->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(app->window) == 0

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

	Shader modelShader;

	modelShader.Load("model");
	Model ourModel("assets/viper/viper.obj");

	glm::mat4 modelObj(1.0f);
	modelObj = glm::translate(modelObj, glm::vec3(0.0f, 80.0f, 0.0f)); // translate it down so it's at the center of the scene
	modelObj = glm::scale(modelObj, glm::vec3(1.5f, 1.5f, 1.5f));	// it's a bit too big for our scene, so scale it down

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	while (RENDER)
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 0.10 ){
			printf("%f ms/frame  fps:%d chunks:%lu\n", 100.0/double(nbFrames), nbFrames * 10, map->chunkList.size());
			nbFrames = 0;
			lastTime += 0.10f;
			map->updatePosition(camera.position);
			map->SlowRender();
		}
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(app);
		camera.ProcessInput();

		//Physics
		/*
		Chunk *p;
		p = map->chunks[floor(camera.position.x / CHUNK_SIZE)][0][floor(camera.position.z / CHUNK_SIZE)];
		if (p->world[floor(camera.position.x)][floor(camera.position.y)][floor(camera.position.z)] > 0){}else{camera.position.y-=0.1f;}
		*/

		modelShader.use();
        modelShader.setMat4("projection", camera.getProjection());
        modelShader.setMat4("view", camera.getView());
        modelShader.setMat4("model", modelObj);
        ourModel.Draw(modelShader);

		map->Render(camera.getView(), camera.getProjection());


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
