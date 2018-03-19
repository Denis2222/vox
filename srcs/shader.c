/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:30:42 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/19 04:18:00 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <string.h>

long	get_file_size(FILE *p_file)
{
	long length;

	length = 0;
	fseek(p_file, 0, SEEK_END);
	length = ftell(p_file);
	fseek(p_file, 0, SEEK_SET);
	return (length);
}

char	*load_shader_file(char *path)
{
	FILE	*file;
	long	size;
	char	*str;

	str = NULL;
	file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Can't read shader file : %s\n", path);
		return (0);
	}
	size = get_file_size(file);
	str = (char*)malloc(size + 1);
	bzero(str, size + 1);
	if (!str)
		exit(1);
	fread(str, size, 1, file);
	fclose(file);
	return (str);
}

int		shader_check_error(GLuint shader_id)
{
	int		log_length;
	char	*log;

	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 0)
	{
		log = (GLchar*)malloc(log_length);
		if (log == NULL)
		{
			fprintf(stderr,
				"Malloc log compilation du shader error !\n");
			return (0);
		}
		bzero(log, log_length);
		glGetShaderInfoLog(shader_id, log_length, &log_length, log);
		fprintf(stderr, "Erreur de compilation :\n%s", log);
		free(log);
	}
	return (1);
}

GLuint	shader_compile(const char *name, GLenum type)
{
	GLuint		shader_id;
	char		*data;
	char		path[1024];
	char const	*data_ptr;

	if (type == GL_VERTEX_SHADER)
		sprintf(path, "./shaders/%s.vert", name);
	if (type == GL_FRAGMENT_SHADER)
		sprintf(path, "./shaders/%s.frag", name);
	if (!(data = load_shader_file(path)))
		return (0);
	shader_id = glCreateShader(type);
	data_ptr = data;
	glShaderSource(shader_id, 1, &data_ptr, NULL);
	glCompileShader(shader_id);
	free(data);
	if (!shader_check_error(shader_id))
		return (0);
	return (shader_id);
}

GLuint	shader_load(const char *name)
{
	GLuint fragment_shader_id;
	GLuint vertex_shader_id;
	GLuint program_id;

	vertex_shader_id = shader_compile(name, GL_VERTEX_SHADER);
	fragment_shader_id = shader_compile(name, GL_FRAGMENT_SHADER);
	if (!vertex_shader_id || !fragment_shader_id)
	{
		printf("Corrige les shaders \n Programme termine \n");
	}
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);
	if (!shader_check_error(program_id))
		printf("Probleme de link\n");
	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
	std::cout << "Link shader complete :" << program_id << std::endl;
	return (program_id);
}
