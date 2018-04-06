#include <Scene.hpp>


			Scene::Scene(Camera *camera) {
				this->SetCamera(camera);
				Model::PreLoad("shotgun", "assets/rocket/rocketlauncher.x", "model");

					GameObject *obj = new GameObject();

					obj->tag = "shotgun";
					obj->scene = this;
					obj->transform.scale = glm::vec3(0.005f,0.005f, 0.005f);
					obj->transform.rotation = glm::vec3(0,90,-70);
					obj->transform.position = glm::vec3(.15f, -0.05f, -0.05f);
					obj->AddComponent<Model>(Model::model["shotgun"]);


					this->Add(obj);

			}

			Scene::~Scene(void) {

			}

	Camera	*Scene::GetCamera() {
		return (this->camera);
	}

	void 	Scene::SetCamera(Camera *camera) {
		this->camera = camera;
	}

	void 	Scene::Add(GameObject *obj) {
		if (!obj)
			return ;
		this->objects[obj->id] = obj;
	}


	void 	Scene::Remove(GameObject *obj) {
		if (!obj)
			return ;
		this->objects.erase(obj->id);
	}

	void Scene::view(void) {
		for (auto const &it : this->objects) {
			GameObject *o = it.second;
			//printf("GameObject id: %d\n", o->id);
		}
	}

	void Scene::Render(void) {
		for (auto const &it : this->objects) {
			//printf("Each object !\n");
			GameObject *c = it.second;
			c->Update();
			c->Render();
		}
	}
