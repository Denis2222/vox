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


unsigned int loadCubemap(std::vector<std::string> faces)
{

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
		stbi_set_flip_vertically_on_load(false);
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

int		main(int argc, char **argv)
{
	t_app	*app;

	app = root();


	//printf("%d %d ", sizeof(char), sizeof(int));


	//return (0);
	int i = init_glfw(app);





	if (!i)
	{
		printf("Failed to INIT GLFW\n");
		return (-1);
	}

//	Terrain *terrain = new Terrain();

	std::cout << (floor(-1 / CHUNK_SIZE)) << " " << std::endl;
	std::cout << (floor(-3 / CHUNK_SIZE)) << " " << std::endl;
	std::cout << (floor(18 / CHUNK_SIZE)) << " " << std::endl;
	std::cout << (floor(1 / CHUNK_SIZE)) << " " << std::endl;
//return 0;

	Map *map = new Map();
	map->updatePosition(camera.position);


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

	int cursorx;
	int cursory;
	int cursorz;

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
	return (0);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.mouse_callback(xpos,ypos);
}
