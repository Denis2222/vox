#include "Camera.hpp"

Camera::Camera(unsigned int id, unsigned int w, unsigned int h, GLFWwindow *win) {
	this->ID = id;

	this->window = win;
	this->grounded = false;
	this->jump = 0;
	this->god = false;

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
	{
		if (this->god)
			deltaSpeed*=20;
		else
			deltaSpeed*=4;
	}

	float posY = position.y;
	float posX = position.x;
	float posZ = position.z;

	glm::vec3 oldPos = position;

	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
        position += deltaSpeed * front;
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
        position -= deltaSpeed * front;
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * deltaSpeed;
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * deltaSpeed;

	if (!this->god)
		position.y = posY;

	if (glfwGetKey(this->window, GLFW_KEY_F) == GLFW_PRESS)
		std::cout << "Block:" << glm::to_string(this->position) << std::endl;

	if (glfwGetKey(this->window, GLFW_KEY_G) == GLFW_PRESS)
		this->god = true;
	if (glfwGetKey(this->window, GLFW_KEY_H) == GLFW_PRESS)
		this->god = false;

	if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(this->window, true);
	}

	//Get where i am !

	if ( glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glm::vec3 detector(0.0f,0.0f,0.0f);
		for (float d = 0; d < 5.0f; d+=0.2f)
		{
			detector = position+glm::vec3(0.0f,0.5f,0.0f)+ (front * d);
			if (map->getBlockInfo(detector) > 1) {
				//std::cout << "Quelque chose" << std::endl;
				int x = (int)round(detector.x);
				int y = (int)round(detector.y);
				int z = (int)round(detector.z);
				//printf("Case float : X:%f Y:%f Z:%f\n",m.x, m.y, m.z);
				Chunk *c;
				c = map->getChunkWorld(x, y, z);
				if (c != NULL) {
					if (c->state == Chunk::STATE::RENDER) {
						x = x - c->worldCoord.x;
						y = y;
						z = z - c->worldCoord.z;
						c->interact( x, y, z, 0);
					}
				}
				break;
			}
		}
	}

	if ( glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		glm::vec3 detector(0.0f,0.0f,0.0f);
		for (float d = 1.1; d < 5.0f; d+=0.2f)
		{
			detector = position+glm::vec3(0.0f,0.5f,0.0f)+ (front * d);
			if (map->getBlockInfo(detector) < 2) {
				//std::cout << "Quelque chose" << std::endl;
				int x = (int)round(detector.x);
				int y = (int)round(detector.y);
				int z = (int)round(detector.z);
				//printf("Case float : X:%f Y:%f Z:%f\n",m.x, m.y, m.z);
				Chunk *c;
				c = map->getChunkWorld(x, y, z);
				if (c != NULL) {
					if (c->state == Chunk::STATE::RENDER) {
						x = x - c->worldCoord.x;
						y = y;
						z = z - c->worldCoord.z;
						c->interact( x, y, z, 6);
					}
				}
				break;
			}
		}
	}


	glm::vec3 m = glm::round(this->position);

	float pHeight = 1.0f; // Hauteur joueur
	m = this->position + glm::vec3(0.0f, 0.0f, 0.0f);
	if (map->getBlockInfo(m+glm::vec3(0.0f, -pHeight, 0.0f)) < 2) {
		if (!this->god) {
			this->grounded = false;
			position.y-= 0.3f;
		}
	} else {
		this->grounded = true;
		this->jump = 0;
	}

	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (this->grounded)
			this->jump = 45;
	}

	if (this->jump > 0)
	{
		if (map->getBlockInfo(m+glm::vec3(0.0f, pHeight, 0.0f)) > 1) {
			this->jump = 0;
		} else {
			position.y+=(0.01f * this->jump);
			this->jump--;
		}
	}

	float s = 0.3f;

	if (!this->god)
	{
		if (map->getBlockInfo(m+glm::vec3(s, 0.0f, 0.0f)) > 1) {
			position.x = posX-0.05f;
		}
		if (map->getBlockInfo(m+glm::vec3(-s, 0.0f, 0.0f)) > 1) {
			position.x = posX+0.05f;
		}
		if (map->getBlockInfo(m+glm::vec3(0.0f, 0.0f, s)) > 1) {
			position.z = posZ-0.05f;
		}
		if (map->getBlockInfo(m+glm::vec3(0.0f, 0.0f, -s)) > 1) {
			position.z = posZ+0.05f;
		}
	}
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
