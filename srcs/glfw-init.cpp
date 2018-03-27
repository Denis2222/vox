#include <vox.h>

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
	//glEnable(GL_MULTISAMPLE);
	//glfwSwapInterval(0);//delete fps limit
	glfwSetInputMode(app->window, GLFW_STICKY_MOUSE_BUTTONS, 1);
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //WIREFRAME MODE
	//glDepthFunc(GL_LESS);

	glfwSetCursorPosCallback(app->window, mouse_callback);
	glClearColor(0.527f, 0.804f, 0.918f, 1.0f);
	return (1);
}

void 	framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	std::cout << "Resize to :" << width << " * " << height << std::endl;
    glViewport(0, 0, width, height);
}

void 	processInput(t_app *app) {

	//t_app *app;
	//app = root();

    if(glfwGetKey(app->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(app->window, true);

	if(glfwGetKey(app->window, GLFW_KEY_P) == GLFW_PRESS && app->test == 0)
	{
		/*
		app->test = 1;

		Chunk chunk2(CHUNK_SIZE, 0,0);

		chunk2.build();
		app->VAO2 = chunk2.buildVAO();

		app->chunk2size = chunk2.getTriangle();
		*/
	}

}


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
