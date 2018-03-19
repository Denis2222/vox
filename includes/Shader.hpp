#ifndef SHADER_H
#define SHADER_H

#include <scop.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
	public:
		unsigned ID;

		Shader(const GLchar* name);

		void use();

		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setFloat4(const std::string &name, float r, float g, float b, float a) const;
	private:
		void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
