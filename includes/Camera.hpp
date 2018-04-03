#ifndef CAMERA_H
#define CAMERA_H

#include <vox.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Map;

class Camera
{
	public:
		unsigned int ID;

		unsigned int 	width;
		unsigned int 	height;
		bool			grounded;
		bool			god;
		GLFWwindow		*window;

		glm::vec3		position = glm::vec3(500.0f, 30.0f,  500.0f);
		glm::vec3		front = glm::vec3(-1.6f, -0.0f,  0.0f);
		glm::vec3		up = glm::vec3(0.0f, 1.0f,  0.0f);

		float			speed = 2.0f;
		float 			deltaTime = 0.0f;
		float 			lastFrame = 0.0f;
		float 			lastX = 400;
		float 			lastY = 300;
		float			yaw = 46.0f;
		float			pitch = -35.25f;
		float			sensitivity = 0.05f;

		bool			firstMouse = true;

						Camera(unsigned int id, unsigned int w, unsigned int h, GLFWwindow *win);
						Camera(unsigned int id);
		void 			ProcessInput(Map *map);
		glm::mat4 		getView();
		glm::mat4 		getProjection();
		void 			mouse_callback(double xpos, double ypos);
};

#endif
