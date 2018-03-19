/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:41:19 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/19 06:46:37 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <cmath>
#include <Shader.hpp>

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
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
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
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //WIREFRAME MODE
	//glDepthFunc(GL_LESS);
	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	return (1);
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
	float vertices[] = {
	     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // top right
	     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,// bottom right
	    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,// bottom left
	    -0.5f,  0.5f, 0.0f,    0.5f, 0.5f, 0.5f,// top left
	};
	unsigned int indices[] = {  // note that we start from 0!
	    0, 1, 3,   // first triangle
	    1, 2, 3    // second triangle
	};
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	Shader program("learn");
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	while (glfwGetKey(app->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(app->window) == 0)
	{
		processInput(app);
        glClear(GL_COLOR_BUFFER_BIT);

		program.use();

		float greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
		program.setFloat4("uniColor", 0,greenValue,0,0);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(app->window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return (0);
}
