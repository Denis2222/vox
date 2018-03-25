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

	myNoise.SetNoiseType(FastNoise::SimplexFractal);
	myNoise.SetSeed(150);

	app = root();
	int i = init_glfw(app);

	if (!i)
	{
		printf("Failed to INIT GLFW\n");
		return (-1);
	}
	Map *map = new Map();

	Shader modelShader;

	modelShader.Load("model");
	Model ourModel("assets/nanosuit/nanosuit.obj");

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



	double lastTime = glfwGetTime();
	int nbFrames = 0;
	while (RENDER)
	{
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

		Chunk *p;
		float o = 0.5f;
		glm::vec3 m = camera.position;
		m = camera.position + glm::vec3(o,-1.5f,o);
		//m = m / glm::vec3(CHUNK_SIZE, 1,CHUNK_SIZE);

		p = map->getChunk(floor(m.x / CHUNK_SIZE), 0, floor(m.z / CHUNK_SIZE));
		if (p != NULL)
		{
			if (p->getWorld(floor(m.x), floor(m.y), floor(m.z)) > 0)
			{

			}
			else{
				camera.position.y-=0.1f;
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
