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
		glm::vec3	position = glm::vec3(0.0f, 70.0f,  0.0f);
		//glm::vec3	position = glm::vec3(0.0f, 0.0f,  -3.0f);
		//glm::vec3	front = glm::vec3(0.0f, 0.0f,  1.0f);
		glm::vec3	front = glm::vec3(-1.6f, -0.0f,  0.0f);
		glm::vec3	up = glm::vec3(0.0f, 1.0f,  0.0f);




		float		speed = 5.0f;
		float 		deltaTime = 0.0f;
		float 		lastFrame = 0.0f;
		float 		lastX = 400;
		float 		lastY = 300;
		float		yaw = 46.0f;
		float		pitch = -35.25f;
		float		sensitivity = 0.05f;

		bool		firstMouse = true;

					Camera(unsigned int id);
		void 		ProcessInput();
		glm::mat4 	getView();
		glm::mat4 	getProjection();
		void 		mouse_callback(double xpos, double ypos);
};

#endif
