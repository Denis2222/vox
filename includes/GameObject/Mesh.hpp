#ifndef MESH_H
#define MESH_H

//#include <vox.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GameObject/Shader.hpp>

class Shader;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
	public:
	    /*  Mesh Data  */
	    std::vector<Vertex> vertices;
	    std::vector<unsigned int> indices;
	    std::vector<Texture> textures;
	    unsigned int VAO;

	    /*  Functions  */
	    // constructor
	    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	    // render the mesh
	    void Draw(Shader *shader);

	private:
	    /*  Render data  */
	    unsigned int VBO, EBO;

	    /*  Functions    */
	    // initializes all the buffer objects/arrays
	    void setupMesh();
};
#endif
