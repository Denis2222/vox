#include "Camera.hpp"

Camera::Camera(unsigned int id, unsigned int w, unsigned int h, GLFWwindow *win)
{
	this->ID = id;

	this->window = win;
	this->height = h;
	this->width = w;
	//this->position.y = getNoise((int)position.y, (int)position.z)+40.0f;
}

Camera::Camera(unsigned int id)
{
	this->ID = id;
	//this->position.y = getNoise((int)position.y, (int)position.z)+40.0f;
}

void 		Camera::ProcessInput(Map *map)
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	float deltaSpeed = speed * deltaTime;

	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	this->mouse_callback(xPos, yPos);

	if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		deltaSpeed*=40;

	float posY = position.y;
	float posX = position.x;
	float posZ = position.z;


	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
        position += deltaSpeed * front;
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
        position -= deltaSpeed * front;
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * deltaSpeed;
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * deltaSpeed;

	if (0)//NO GOD MODE
		position.y-= 0.1f;

	if (glfwGetKey(this->window, GLFW_KEY_F) == GLFW_PRESS)
		std::cout << "Block:" << glm::to_string(this->position) << std::endl;

	if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(this->window, true);
	}


	//Get where i am !
	glm::vec3 m = glm::floor(this->position + 0.5f);



	//m = m / glm::vec3(CHUNK_SIZE, 1,CHUNK_SIZE);

	Chunk *c;
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		c = map->getChunkWorld((int)round(m.x), (int)round(m.y), (int)round(m.z));
		if (c != NULL)
		{
			if (c->state == Chunk::STATE::RENDER)
			{
				//usleep(50000);
				system("clear");
				printf("X:%d Y:%d Z:%d\n",(int)round(m.x), (int)round(m.y), (int)round(m.z));
				printf("X:%f Y:%f Z:%f\n",m.x, m.y, m.z);
				printf("debug x+1 :%d\n", c->collideDebug((int)round(m.x), (int)round(m.y), (int)round(m.z), 3));
				printf("debug x-1 :%d\n", c->collideDebug((int)round(m.x), (int)round(m.y), (int)round(m.z), 4));
				printf("debug z+1 :%d\n", c->collideDebug((int)round(m.x), (int)round(m.y), (int)round(m.z), 5));
				printf("debug z11 :%d\n", c->collideDebug((int)round(m.x), (int)round(m.y), (int)round(m.z), 6));
				printf("===============================\n");
				//c->interact( floor(m.x+0.5f), floor(m.y), floor(m.z), 0);
			}
		}
	}

/*
	if (map->getBlockInfo(p.x, floor(p.y-1.5f), p.z) > 1)
		position.y = posY;

	std::cout << "X+1" << map->getBlockInfo(p.x + 0.2f, floor(p.y-0.5f), p.z);
	std::cout << " X-1" << map->getBlockInfo(p.x - 0.2f, floor(p.y-0.5f), p.z);

	std::cout << " Z+1" << map->getBlockInfo(p.x, floor(p.y-0.5f), p.z + 0.2f);
	std::cout << " Z-1" << map->getBlockInfo(p.x, floor(p.y-0.5f), p.z - 0.2f);

	std::cout << std::endl;
	if (map->getBlockInfo(p.x + 0.2f, floor(p.y-0.5f), p.z) >1)
		position.x = posX-0.1f;
	if (map->getBlockInfo(p.x + -0.2f, floor(p.y-0.5f), p.z) >1)
		position.x = posX+0.01f;

	if (map->getBlockInfo(p.x, floor(p.y-0.5f), p.z + 0.2f) >1)
		position.z = posZ-0.01f;
	if (map->getBlockInfo(p.x, floor(p.y-0.5f), p.z - 0.2f) >1)
		position.z = posZ+0.01f;
	//Get block arroud;
*/



	//position.y = posY;
}

glm::mat4	Camera::getView(void)
{
	return (glm::lookAt(position, position + front, up));
}
glm::mat4	Camera::getProjection(void)
{
	return (glm::perspective(glm::radians(75.0f), ((float)this->width / (float)this->height), 0.1f, FAR));
}

void 		Camera::mouse_callback(double xpos, double ypos)
{
	if(firstMouse)
	{
	    lastX = xpos;
	    lastY = ypos;
	    firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
    pitch += yoffset;

	if(pitch > 89.0f)
	  pitch =  89.0f;
	if(pitch < -89.0f)
	  pitch = -89.0f;

	 front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	 front.y = sin(glm::radians(pitch));
	 front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	 front = glm::normalize(front);
}
