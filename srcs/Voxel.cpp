#include <Voxel.hpp>

		Voxel::Voxel(int argc, char **argv) {
			std::cout << "Lets GO " << std::endl;

			int seed = 0;
			if (argc > 1)
				seed = atoi(argv[1]);

			noiseParam(seed);

			if (argc == 3)
				this->glfwStart(true);
			else
				this->glfwStart(false);

			this->camera = new Camera(0, this->width, this->height, this->window);

			this->map = new Map();
			this->map->updatePosition(this->camera->position);
			//this->map->updateChunkToLoad();

			this->model = new Model("assets/42/42_texture.obj");


			//this->terrain = new Terrain();
			this->skybox = new Skybox();
			this->skybox->Load();
			this->loop();
		}

		Voxel::~Voxel(void) {
			std::cout << "Delete" << std::endl;
			delete this->skybox;
			delete this->map;
			delete this->camera;
			glfwTerminate();
		}

		void Voxel::loop(void) {
			double currentTime, lastTime = glfwGetTime();
			int nbFrames = 0;
			while (glfwGetKey(this->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(this->window) == 0)
			{
				nbFrames++;
				currentTime = glfwGetTime();
				if (currentTime - lastTime >= 0.10)
				{
					//printf("%f ms/frame  fps:%d chunks:%lu", 100.0/double(nbFrames), nbFrames * 10, this->map->chunkList.size());
					//std::cout << glm::to_string(this->camera->position) << std::endl;
					nbFrames = 0;
					lastTime += 0.10;
					//this->map->updatePosition(this->camera->position);
					this->map->SlowRender();
				}
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				this->camera->ProcessInput(map);
				this->map->Render(this->camera->getView(), this->camera->getProjection(), this->camera->position);


				//this->terrain->render(this->camera);
				this->model->Draw(this->camera);

				this->skybox->render(this->camera);

				glfwSwapBuffers(this->window);
				glfwPollEvents();
			}
		}

		void Voxel::glfwStart (bool fullscreen) {
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW\n" << std::endl;
				exit(0);
			}

			glfwWindowHint(GLFW_SAMPLES, 0);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


			this->width = 2048;
			this->height = 1536;
			if (fullscreen)
			{
				const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				this->width = mode->width;
				this->height = mode->height;
				this->window = glfwCreateWindow(this->width, this->height, TITLE, glfwGetPrimaryMonitor(), NULL);
			} else {
				this->width = 2048;
				this->height = 1536;
				this->window = glfwCreateWindow(this->width, this->height, TITLE, NULL, NULL);
			}

			if (this->window == NULL) {
				std::cout << "Failed to open GLFW window.\n" << std::endl;
				getchar();
				glfwTerminate();
				exit(0);
			}
			glfwMakeContextCurrent(this->window);
			if (glewInit() != GLEW_OK) {
				std::cout << "Failed to initialize GLEW\n" << std::endl;
				getchar();
				glfwTerminate();
				exit(0);
			}
			//glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
			glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_MULTISAMPLE);
			//glfwSwapInterval(0);//delete fps limit
			glfwSetInputMode(this->window, GLFW_STICKY_MOUSE_BUTTONS, 1);
			glEnable(GL_CULL_FACE);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //WIREFRAME MODE
			glDepthFunc(GL_LESS);

			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//glfwSetCursorPosCallback(this->window, this->mouse_callback);
			glClearColor(0.527f, 0.804f, 0.918f, 1.0f);
		}
