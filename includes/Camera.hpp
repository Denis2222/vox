#ifndef CAMERA_H
#define CAMERA_H

#include <vox.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Camera
{
	public:
		unsigned int ID;
		//glm::vec3	position = glm::vec3(-41.0f, 53.0f,  -39.0f);
		glm::vec3	position = glm::vec3(0.0f, 0.0f,  -3.0f);
		glm::vec3	front = glm::vec3(0.0f, 0.0f,  1.0f);
		//glm::vec3	front = glm::vec3(0.6f, -0.4f,  0.6f);
		glm::vec3	up = glm::vec3(0.0f, 1.0f,  0.0f);
		float		speed = 10.0f;
		float 		deltaTime = 0.0f;
		float 		lastFrame = 0.0f;
		float 		lastX = 400;
		float 		lastY = 300;
		float		yaw = -90.0f;
		float		pitch = 0.0f;
		float		sensitivity = 0.05f;

		bool		firstMouse = true;

					Camera(unsigned int id);
		void 		ProcessInput();
		glm::mat4 	getView();
		void 		mouse_callback(double xpos, double ypos);
};

#endif
