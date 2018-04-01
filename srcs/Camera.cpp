#include "Camera.hpp"

Camera::Camera(unsigned int id, unsigned int w, unsigned int h, GLFWwindow *win) {
	this->ID = id;

	this->window = win;


	this->height = h;
	this->width = w;
	//this->position.y = getNoise((int)position.y, (int)position.z)+40.0f;
}

Camera::Camera(unsigned int id) {
	this->ID = id;
	//this->position.y = getNoise((int)position.y, (int)position.z)+40.0f;
}

void 		Camera::ProcessInput(Map *map) {
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

	(void)posX;
	(void)posY;
	(void)posZ;
	//Get where i am !
	glm::vec3 m = glm::floor(this->position + 0.5f);



	//m = m / glm::vec3(CHUNK_SIZE, 1,CHUNK_SIZE);

	Chunk *c;
	if (1) {
		int x = (int)round(m.x);
		int y = (int)round(m.y);
		int z = (int)round(m.z);
		//system("clear");
		//printf("Case float : X:%f Y:%f Z:%f\n",m.x, m.y, m.z);
		c = map->getChunkWorld(x, y, z);
		if (c != NULL) {
			if (c->state == Chunk::STATE::RENDER) {

				x = x - c->worldCoord.x;
				y = y;
				z = z - c->worldCoord.z;

				//system("clear");
				//printf("X:%d Y:%d Z:%d\n",x,y,z);
				//printf(" x+1 :%d\n", c->collideDebug(x,y,z, 3));
				//printf(" x-1 :%d\n", c->collideDebug(x,y,z, 4));
				//printf(" z+1 :%d\n", c->collideDebug(x,y,z, 5));
				//printf(" z-1 :%d\n", c->collideDebug(x,y,z, 6));
				//printf("===============================\n");
				/*
				x = x - c->worldCoord.x;
				z = z - c->worldCoord.z;

				if ( glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
					c->interact( x, y, z, 0);
				}
				if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
					c->interact( x, y, z, 4);
				}
*/
			}
		}
		else {
			std::cout << "Chunk Introuvable !" << std::endl;
		}
	}

	//position.y = posY;
}

glm::mat4	Camera::getView(void) {
	//glm::vec3 t(0.0f,position.y, 0.0f);
	glm::vec3	realPosition = glm::vec3(0.0f, 0.0f,  0.0f);

	return (glm::lookAt(realPosition, realPosition + front, up));
}
glm::mat4	Camera::getProjection(void) {
	return (glm::perspective(glm::radians(80.0f), ((float)this->width / (float)this->height), 0.1f, FAR));
}

void 		Camera::mouse_callback(double xpos, double ypos) {
	if(firstMouse) {
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
