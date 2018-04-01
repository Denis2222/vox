#include <GameObject/Skybox.hpp>

		Terrain::Terrain(void) {
			this->shader = new Shader();
			this->shader->Load("triangle");


			float vertices[] = {
				0.5f,  0.5f, 0.0f,  // top right
				0.5f, -0.5f, 0.0f,  // bottom right
				-0.5f, -0.5f, 0.0f,  // bottom left
				-0.5f,  0.5f, 0.0f   // top left
			};
			unsigned int indices[] = {  // note that we start from 0!
				0, 1, 3,  // first Triangle
				1, 2, 3   // second Triangle
			};

			glGenVertexArrays(1, &this->VAO);
			glGenBuffers(1, &this->VBO);
			glGenBuffers(1, &this->EBO);
			// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			glBindVertexArray(this->VAO);

			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			glBindVertexArray(0);

		}

		Terrain::~Terrain(void) {
			delete this->shader;
		}


		void Terrain::render(Camera *camera) {
			// draw skybox as last
			glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
			this->shader->use();

			glm::mat4 model(1.0f);

			glm::mat4 myMatrix = glm::translate(model, glm::vec3(10,100,10));
			this->shader->setMat4("model", model);
			this->shader->setMat4("view", glm::mat3(camera->getView()));
			this->shader->setMat4("projection", camera->getProjection());
			// skybox cube
			glBindVertexArray(this->VAO);
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			glDepthFunc(GL_LESS); // set depth function back to default
		}
