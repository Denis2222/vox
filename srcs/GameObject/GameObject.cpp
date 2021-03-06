#include <GameObject/GameObject.hpp>

// STATIC ########################################################
long						GameObject::uid = 0;
// ###############################################################

// CANONICAL #####################################################

GameObject::GameObject ( void )
{
	this->transform.position = glm::vec3(0,0,0);
	this->transform.rotation = glm::vec3(0,0,0);
	this->transform.scale = glm::vec3(1,1,1);
	this->tag = "Default";
	GameObject::uid += 1;
	this->id = GameObject::uid;
	return ;
}

GameObject::GameObject ( GameObject const & src )
{
	*this = src;
	return ;
}

GameObject &				GameObject::operator=( GameObject const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameObject::~GameObject ( void )
{
	if (this->tag != "Default") {
		this->mutex.lock();
		for (auto &it : this->components)
		{
			if (it.first == "Model")
				continue ;
			delete it.second;
		}
		this->components.clear();
		this->mutex.unlock();
	}
	return ;
}

std::ostream &				operator<<(std::ostream & o, GameObject const & i)
{
	o << "GameObject :" << std::endl;
	o << "position : vec3(" << i.transform.position.x << "," << i.transform.position.y << "," << i.transform.position.z << ")" << std::endl;
	o << "rotation : vec3(" << i.transform.rotation.x << "," << i.transform.rotation.y << "," << i.transform.rotation.z << ")" << std::endl;
	o << "scale : vec3(" << i.transform.scale.x << "," << i.transform.scale.y << "," << i.transform.scale.z << ")" << std::endl;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						GameObject::Translate(glm::vec3 v)
{
	this->transform.position = this->transform.position + v;
}

void									GameObject::Render(void) {
	Model *model = this->GetComponent<Model>();
	//printf("GameObject render");
	model->Draw(this->scene->GetCamera());
}
void									GameObject::Update(void) {

}

// ###############################################################
