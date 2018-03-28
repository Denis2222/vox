#include <Voxel.hpp>

		Voxel::Voxel(void) {
			std::cout << "Lets GO " << std::endl;
			this->glfwStart();
			this->camera = new Camera(0, WIDTH, HEIGHT, this->window);
			this->map = new Map();
			this->map->updatePosition(this->camera->position);
			this->skybox = new Skybox();
			//this->initSkybox();
			this->loop();

		}

		Voxel::~Voxel(void){
			std::cout << "Delete" << std::endl;
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
					printf("%f ms/frame  fps:%d chunks:%lu\n", 100.0/double(nbFrames), nbFrames * 10, this->map->chunkList.size());
					nbFrames = 0;
					lastTime += 0.10;
					this->map->updatePosition(this->camera->position);
					this->map->SlowRender();
				}
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				this->camera->ProcessInput(map);
				this->map->Render(this->camera->getView(), this->camera->getProjection());
				this->skybox->render(this->camera);

				glfwSwapBuffers(this->window);
				glfwPollEvents();
			}
		}

		void 	Voxel::processInput(void) {

		}

		void Voxel::glfwStart (void) {
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW\n" << std::endl;
				exit(0);
			}
			glfwWindowHint(GLFW_SAMPLES, 0);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			this->window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
			if (this->window == NULL)
			{
				std::cout << "Failed to open GLFW window.\n" << std::endl;
				getchar();
				glfwTerminate();
				exit(0);
			}
			glfwMakeContextCurrent(this->window);
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GLEW\n" << std::endl;
				getchar();
				glfwTerminate();
				exit(0);
			}
			//glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
			glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glEnable(GL_DEPTH_TEST);
			//glEnable(GL_MULTISAMPLE);
			//glfwSwapInterval(0);//delete fps limit
			glfwSetInputMode(this->window, GLFW_STICKY_MOUSE_BUTTONS, 1);
			glEnable(GL_CULL_FACE);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //WIREFRAME MODE
			//glDepthFunc(GL_LESS);

			//glfwSetCursorPosCallback(this->window, this->mouse_callback);
			glClearColor(0.527f, 0.804f, 0.918f, 1.0f);
		}