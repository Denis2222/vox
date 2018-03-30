/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:41:19 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/30 16:17:51 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Voxel.hpp>

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	Voxel start;
	return (0);
}
/*
	GLint nCurAvailMemoryInKBStart = 0;
	glGetIntegerv( GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, &nCurAvailMemoryInKBStart );

	Map *map = new Map();
	map->updatePosition(camera.position);

	long kbusestart = getValue();

*/
/*
	Shader modelShader;

	modelShader.Load("model");
	Model ourModel("assets/ncube_snow.obj");

	glm::mat4 modelObj(1.0f);
	modelObj = glm::translate(modelObj, glm::vec3(0.0f, getNoise(0,0), 10.0f)); // translate it down so it's at the center of the scene
	modelObj = glm::scale(modelObj, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

	Shader skyboxShader;
	skyboxShader.Load("skybox");
	skyboxShader.setInt("skybox", 0);
	float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };



	unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	std::vector<std::string> faces
	{
	    "./assets/skybox/right.jpg",
	    "./assets/skybox/left.jpg",
	    "./assets/skybox/top.jpg",
	    "./assets/skybox/bottom.jpg",
	    "./assets/skybox/front.jpg",
	    "./assets/skybox/back.jpg"
	};
	unsigned int cubemapTexture = loadCubemap(faces);
*/


/*	int cursorx;
	int cursory;
	int cursorz;
*/


/*
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	while (RENDER)
	{
		Chunk *p;
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 0.10 ){
			//printf("%f ms/frame  fps:%d chunks:%lu\n", 100.0/double(nbFrames), nbFrames * 10, map->chunkList.size());
			nbFrames = 0;
			lastTime += 0.10f;
			map->updatePosition(camera.position);
			map->SlowRender();

			//GLint nTotalMemoryInKB = 0;
			//glGetIntegerv( GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, &nTotalMemoryInKB );

			GLint nCurAvailMemoryInKB = 0;
			glGetIntegerv( GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, &nCurAvailMemoryInKB );


			std::cout << "VRAM use: " << ((nCurAvailMemoryInKBStart - nCurAvailMemoryInKB)/1024) << std::endl;

			std::cout << "Memory use :" << (getValue() - kbusestart) << std::endl;

		}

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(app);
		camera.ProcessInput();

		//Physics


		float o = 0.5f;
		glm::vec3 m = camera.position;
		m = camera.position + glm::vec3(o,0.0f,o);
		//m = m / glm::vec3(CHUNK_SIZE, 1,CHUNK_SIZE);

		Chunk *c;
		if (glfwGetKey(root()->window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			c = map->getChunkWorld(m.x, m.y, m.z);
			if (c != NULL)
			{
				c->interact( floor(m.x+0.5f), floor(m.y), floor(m.z), 4);
			}
		}

		if (glfwGetKey(root()->window, GLFW_KEY_E) == GLFW_PRESS)
		{
			c = map->getChunkWorld(m.x, m.y, m.z);
			if (p)
			{

				//std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\nGetBlockInfo: " << x << " " << y << " " << z << " " << std::endl;
				//map->getBlockInfoReallyMore(x, y, z);
				//std::cout << "collide up:" << p->collideDebug(floor(m.x+1.0f), floor(m.y), floor(m.z), 1) << std::endl;
				//std::cout << "collide down:" << p->collideDebug(floor(m.x+1.0f), floor(m.y), floor(m.z), 2) << std::endl;
				//std::cout << "collide est:" << p->collideDebug(floor(m.x+1.0f), floor(m.y), floor(m.z), 3) << std::endl;
				//std::cout << "collide ouest:" << p->collideDebug(floor(m.x+1.0f), floor(m.y), floor(m.z), 4) << std::endl;
				///std::cout << "collide nord:" << p->collideDebug(floor(m.x+1.0f), floor(m.y), floor(m.z), 5) << std::endl;
				//std::cout << "collide sud:" << p->collideDebug(floor(m.x+1.0f), floor(m.y), floor(m.z), 6) << std::endl;
			}
			//std::cout << "info 2:35:5 > " << map->getBlockInfo(2, 35, 5) << std::endl;
		}

		if ( glfwGetMouseButton(root()->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			c = map->getChunkWorld(m.x, m.y, m.z);
			if (c != NULL)
			{
				if (c->getWorld(floor(m.x+0.5f), floor(m.y), floor(m.z)))
				{
					c->interact( floor(m.x+0.5f), floor(m.y), floor(m.z), 1);
				}
				if (0) {
					//camera.position.y-=0.1f;
				}
			}
		}



		modelShader.use();
        modelShader.setMat4("projection", camera.getProjection());
        modelShader.setMat4("view", camera.getView());
        modelShader.setMat4("model", modelObj);
        ourModel.Draw(modelShader);

		map->Render(camera.getView(), camera.getProjection());


		// draw skybox as last
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader.use();
		//glm::mat4 view(); // remove translation from the view matrix
		skyboxShader.setMat4("view", glm::mat3(camera.getView()));
		skyboxShader.setMat4("projection", camera.getProjection());
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default


		glfwSwapBuffers(app->window);
		glfwPollEvents();
	}
	glfwTerminate();

	delete map;

	GLint nCurAvailMemoryInKB = 0;
	glGetIntegerv( GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, &nCurAvailMemoryInKB );


	std::cout << "VRAM use: " << ((nCurAvailMemoryInKBStart - nCurAvailMemoryInKB)/1024) << std::endl;
	std::cout << "Memory use :" << (getValue() - kbusestart) << std::endl;

	sleep(10);

	return (0);
	*/
//}
/*
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.mouse_callback(xpos,ypos);
}*/
