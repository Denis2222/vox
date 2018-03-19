#include "Camera.hpp"

Camera::Camera(unsigned int id)
{
	ID = id;
}

void 		Camera::ProcessInput()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	float deltaSpeed = speed * deltaTime;

	if (glfwGetKey(root()->window, GLFW_KEY_W) == GLFW_PRESS)
        position += deltaSpeed * front;
    if (glfwGetKey(root()->window, GLFW_KEY_S) == GLFW_PRESS)
        position -= deltaSpeed * front;
    if (glfwGetKey(root()->window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * deltaSpeed;
    if (glfwGetKey(root()->window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * deltaSpeed;
}

glm::mat4	Camera::getView(void)
{
	return (glm::lookAt(position, position + front, up));
}
/*
void 		Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	if(pitch > 89.0f)
	  pitch =  89.0f;
	if(pitch < -89.0f)
	  pitch = -89.0f;

	 front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	 front.y = sin(glm::radians(pitch));
	 front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	 front = glm::normalize(front);
}
*/
