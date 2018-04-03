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
		deltaSpeed*=20;

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

	position.y = posY;

	if (glfwGetKey(this->window, GLFW_KEY_F) == GLFW_PRESS)
		std::cout << "Block:" << glm::to_string(this->position) << std::endl;

	if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(this->window, true);
	}

	(void)posX;
	(void)posY;
	(void)posZ;
	//Get where i am !
	glm::vec3 m = glm::round(this->position);
	Chunk *c;
	if (1) {
		int x = (int)round(m.x);
		int y = (int)round(m.y);
		int z = (int)round(m.z);
		//printf("Case float : X:%f Y:%f Z:%f\n",m.x, m.y, m.z);
		c = map->getChunkWorld(x, y, z);
		if (c != NULL) {
			if (c->state == Chunk::STATE::RENDER) {
				x = x - c->worldCoord.x;
				y = y;
				z = z - c->worldCoord.z;
				if ( glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
					c->interact( x, y, z, 0);
				}
				if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
					c->interact( x, y, z, 4);
				}
			}
		} else {
			std::cout << "Chunk Introuvable !" << std::endl;
		}
	}




	float pHeight = 0.5f;
	system("clear");

	printf("x:%.2f y:%.2f z:%.2f \n", m.x, m.y, m.z);

	if (map->getBlockInfo(m.x, m.y-pHeight, m.z) < 2)
	{
		printf("ground x:%.2f y:%.2f z:%.2f \n", m.x, m.y-pHeight, m.z);
		position.y-= 0.3f;
	}

	float dN = 99.0f;
	float dS = 99.0f;
	float dE = 99.0f;
	float dW = 99.0f;



	float dSE = 99.0f;
	float dSW = 99.0f;

	float dNE = 99.0f;
	float dNW = 99.0f;

	float s = 1.0f;

	m = this->position + glm::vec3(0.0f, 0.0f, 0.0f);

	if (map->getBlockInfo(m+glm::vec3(s, 0.0f, 0.0f)) > 1)
	{
		dW = glm::distance(m+glm::vec3(s, 0.0f, 0.0f), m);
		std::cout << "X+1 " << dW << std::endl;
		position.x = posX;
		//position.x = posX;
	}
	if (map->getBlockInfo(m+glm::vec3(-s, 0.0f, 0.0f)) > 1)
	{
		dE = glm::distance(m+glm::vec3(-s, 0.0f, 0.0f), m);
		std::cout << "X-1 " << dE << std::endl;
		position.x = posX;
		//position.x = posX+0.1f;
	}
	if (map->getBlockInfo(m+glm::vec3(0.0f, 0.0f, s)) > 1)
	{
		dN = glm::distance(m+glm::vec3(0.0f, 0.0f, s), m);
		std::cout << "Z+1 dN:" << dN << std::endl;
		position.z = posZ;
	}
	if (map->getBlockInfo(m+glm::vec3(0.0f, 0.0f, -s)) > 1)
	{
		dS = glm::distance(m+glm::vec3(0.0f, 0.0f, -s), m);
		std::cout << "Z-1 dS:" << dS << std::endl;
		position.z = posZ;
	}
/*
	if (map->getBlockInfo(round(m.x + s), m.y-pHeight, round(m.z + s)) > 1)
	{
		dNW = glm::distance(glm::vec3(round(m.x + s), m.y-pHeight, round(m.z + s)), m);
		std::cout << "X+1 Z+1 " << dNW << std::endl;
		//position.x = posX;
	}
	if (map->getBlockInfo(round(m.x - s), m.y-pHeight, round(m.z + s)) > 1)
	{
		dNE = glm::distance(glm::vec3(round(m.x - s), m.y-pHeight, round(m.z + s)), m);
		std::cout << "X-1 Z+1 " << dNE << std::endl;
		//position.x = posX;
	}
	if (map->getBlockInfo(round(m.x + s), m.y-pHeight, round(m.z - s)) > 1)
	{
		dSW = glm::distance(glm::vec3(round(m.x + s), m.y-pHeight, round(m.z - s)), m);
		std::cout << "X+1 Z-1 " << dSW << std::endl;
		//position.z = posZ;
	}
	if (map->getBlockInfo(round(m.x - s), m.y-pHeight, round(m.z - s)) > 1)
	{
		dSE = glm::distance(glm::vec3(round(m.x - s), m.y-pHeight, round(m.z - s)), m);
		std::cout << "X-1 Z-1 " << dSE << std::endl;
		//position.z = posZ;
	}
*/
/*
	if (dW < 2.0f && dW > 0.0f)
	{

	}

	if (dE < 2.0f && dE > 0.0f)
	{
		position.x = posX;
	}

	if (dN < 3.0f && dN > 0.0f)
	{
		position.z = posZ;
	}

	if (dS < 3.0f && dS > 0.0f)
	{
		position.z = posZ;
	}
*/

/*
if (map->getBlockInfo(m.x + s, m.y-pHeight, m.z + (s/4)) > 1 || map->getBlockInfo(m.x + s, m.y-pHeight, m.z - (s/4)) > 1)
{
	std::cout << "X+1" << std::endl;
	position.x = posX;
} else if (map->getBlockInfo(m.x - s, m.y-pHeight, m.z + (s/4)) > 1 || map->getBlockInfo(m.x - s, m.y-pHeight, m.z - (s/4)) > 1)
{
	std::cout << "X-1" << std::endl;
	position.x = posX;
}
if (map->getBlockInfo(m.x + (s/4), m.y-pHeight, m.z + s) > 1 || map->getBlockInfo(m.x - (s/4), m.y-pHeight, m.z + s) > 1)
{
	std::cout << "Z+1" << std::endl;
	position.z = posZ;
} else if (map->getBlockInfo(m.x - (s/4), m.y-pHeight, m.z - s) > 1 || map->getBlockInfo(m.x + (s/4), m.y-pHeight, m.z - s) > 1)
{
	std::cout << "Z-1" << std::endl;
	position.z = posZ;
}

*/

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
