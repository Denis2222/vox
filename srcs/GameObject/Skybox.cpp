#include <GameObject/Skybox.hpp>

		Skybox::Skybox(void) {
			this->Load();
			this->shader = new Shader();
			this->shader->Load("skybox");
			this->shader->setInt("skybox", 0);
		}

		Skybox::~Skybox(void) {
			delete this->shader;
		}

		void Skybox::Load(void) {
			float skyboxVertices[] = {
				// positions
				-1.0f,  1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				-1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f
			};
			glGenVertexArrays(1, &this->skyboxVAO);
			glGenBuffers(1, &this->skyboxVBO);
			glBindVertexArray(this->skyboxVAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			std::vector<std::string> faces {
			    "./assets/skybox/right.jpg",
			    "./assets/skybox/left.jpg",
			    "./assets/skybox/top.jpg",
			    "./assets/skybox/bottom.jpg",
			    "./assets/skybox/front.jpg",
			    "./assets/skybox/back.jpg"
			};
			this->cubemapTexture = loadCubemap(faces);
		}

		unsigned int Skybox::loadCubemap(std::vector<std::string> faces) {
		    glGenTextures(1, &this->textureID);
		    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);

		    int width, height, nrChannels;
		    for (unsigned int i = 0; i < faces.size(); i++)
		    {
				stbi_set_flip_vertically_on_load(false);
		        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		        if (data)
		        {
		            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
		                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		            );
		            stbi_image_free(data);
		        }
		        else
		        {
		            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
		            stbi_image_free(data);
		        }
		    }
		    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		    return textureID;
		}

		void Skybox::render(Camera *camera) {
			// draw skybox as last
			glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
			this->shader->use();
			//glm::mat4 view(); // remove translation from the view matrix
			this->shader->setMat4("view", glm::mat3(camera->getView()));
			this->shader->setMat4("projection", camera->getProjection());
			// skybox cube
			glBindVertexArray(this->skyboxVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthFunc(GL_LESS); // set depth function back to default
		}
