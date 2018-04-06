#ifndef SCENE_HPP
#define SCENE_HPP

#include <vox.h>

class GameObject;
class Camera;

class Scene {

	std::unordered_map<long, GameObject*> 	objects;
	Camera									*camera;

	public:
		Scene(Camera *camera);
		~Scene(void);

		void Add(GameObject *obj);
		void Remove(GameObject *obj);


		Camera	*GetCamera();
		Camera	*SetCamera(Camera *camera);

		void view(void);
		void Render(void);
};

#endif
