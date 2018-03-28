#include "Chunk.hpp"

		Chunk::Chunk(int x, int y, int z, Map *map)
		{
			this->localCoord = glm::vec3(x, y, z);
			this->worldCoord = glm::vec3(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);
			this->state = STATE::INIT;
			this->map = map;
		}

		Chunk::~Chunk()
		{
			points.clear();;
			uvs.clear();;
			world.clear();
		}

int		Chunk::getBlockType(int x, int y, int z, int height)
{
	int type = 0;
	if (y < 41)
		type = 2; // Water
	else if (y < 42)
		type =  4; // Rock
	else if (y <= height && y > (height - 3))
		type = 3; //  Grass
	else
		type = 4; // Rock

	if (y > 80)
		type = 5; // Snow
	return (type);
}

void	Chunk::generate(void)
{
	int sx, sy, sz;
	sx = this->worldCoord.x;
	sy = this->worldCoord.y;
	sz = this->worldCoord.z;

	for (int x = sx; x < CHUNK_SIZE + sx; x++)
	{
		for (int z = sz; z < CHUNK_SIZE + sz; z++)
		{
			int height = getNoise(x, z);
			for (int y = 0; y < CHUNK_HEIGHT; y++)
			{
				if (y <= height)
				{
					setWorld(x, y, z, getBlockType(x, y, z, height));

					if (y >= this->maxheight)
						this->maxheight = y+1;
					if (y <= this->minheight)
						this->minheight = y-1;
				}
			}
		}
	}
	this->state = STATE::GENERATE;
}

void Chunk::interact(int x, int y, int z, int val)
{
	this->setWorld(x, y, z, val);
	this->state = STATE::TOUPDATE;
	if ((x == this->worldCoord.x || z == this->worldCoord.z ||
		x == this->worldCoord.x + CHUNK_SIZE-1 || z == this->worldCoord.z + CHUNK_SIZE-1))
	{
		Chunk *c = this->map->getChunk(floor((x + 1) / CHUNK_SIZE), 0, floor((z + 1) / CHUNK_SIZE));
		c->state = STATE::TOUPDATE;
		c = this->map->getChunk(floor((x - 1) / CHUNK_SIZE), 0, floor((z + 1) / CHUNK_SIZE));
		c->state = STATE::TOUPDATE;
		c = this->map->getChunk(floor((x + 1) / CHUNK_SIZE), 0, floor((z - 1) / CHUNK_SIZE));
		c->state = STATE::TOUPDATE;
		c = this->map->getChunk(floor((x - 1) / CHUNK_SIZE), 0, floor((z - 1) / CHUNK_SIZE));
		c->state = STATE::TOUPDATE;
	}
}

bool	Chunk::collide(int x, int y, int z, int way)
{

	bool retour = false;
	int info = -1;
	if ((x <= this->worldCoord.x || z <= this->worldCoord.z ||
		x >= this->worldCoord.x + CHUNK_SIZE-1 || z >= this->worldCoord.z + CHUNK_SIZE-1) && way != 1 && way != 2 )
	{
		int qx = x;
		int qy = y;
		int qz = z;

		if (way == 1) // UP
			qy = qy + 1;
		if (way == 2) // DOWN
			qy = qy - 1;
		if (way == 3) // EST
			qx = qx + 1;
		if (way == 4) // OUEST
			qx = qx - 1;
		if (way == 5) // NORD
			qz = qz + 1;
		if (way == 6) // SUD
			qz = qz - 1;
		info = this->map->getBlockInfo(qx, qy, qz);
		if (info > 1)
			retour = true;
		else if (info  < 1)
		{
			if (getNoise(qx, qz) >= qy)
					retour = true;
			else
				retour = false;
		}
		else if (info == 0)
			retour = false;
		else
			retour = false;
	} else {
		if (way == 1) // UP
		{
			if (getWorld(x, y + 1, z) > 1)
				retour = true;
		}
		if (way == 2) // DOWN
		{
			if (y == 0)
				retour = true;
			if (getWorld(x, y - 1, z) > 1)
				retour = true;
		}
		if (way == 3) // EST
		{
			if (getWorld(x + 1, y, z) > 1)
				retour = true;
		}
		if (way == 4) // OUEST
		{
			if (getWorld(x - 1 , y, z) > 1)
				retour = true;
		}
		if (way == 5) // NORD
		{
			if (getWorld(x, y, z + 1) > 1)
				retour = true;
		}
		if (way == 6) // SUD
		{
			if (getWorld(x, y, z - 1) > 1)
				retour = true;
		}
	}
	return (retour);
}

bool	Chunk::collideDebug(int x, int y, int z, int way)
{

	//std::cout << "PATATOR: X" << x << " " << this->worldCoord.x << " Y " <<  y << " " << this->worldCoord.y << " Z:" <<  z << " " << this->worldCoord.z << std::endl;
	bool retour = false;
	int info = -1;
	if ((x <= this->worldCoord.x || z <= this->worldCoord.z ||
		x >= this->worldCoord.x + CHUNK_SIZE-1 || z >= this->worldCoord.z + CHUNK_SIZE-1) && way != 1 && way != 2 )
	{
		//std::cout << "Externe" << std::endl;


		int qx = x;
		int qy = y;
		int qz = z;

		if (way == 1) // UP
			qy = qy + 1;
		if (way == 2) // DOWN
			qy = qy - 1;
		if (way == 3) // EST
			qx = qx + 1;
		if (way == 4) // OUEST
			qx = qx - 1;
		if (way == 5) // NORD
			qz = qz + 1;
		if (way == 6) // SUD
			qz = qz - 1;


		info = this->map->getBlockInfo(qx, qy, qz);

		//info = -1;

			//std::cout << "info: " << info << std::endl;
		if (info > 1)
			retour = true;
		else if (info  < 1)
		{
			//std::cout << "info < 0" << "Tu va prendre ton noise ! " << std::endl;
			if (getNoise(qx, qz) >= qy)
					retour = true;
			else
				retour = false;
		}
		else if (info == 0)
			retour = false;
		else
			retour = false;

				std::cout << "Externe " << std::endl;
				this->map->getBlockInfoReallyMore(qx, qy, qz);
				//std::cout << "Externe x:"<< x <<" y:" << y <<" z:" << z<< " bool:" << retour << " way:" << way << " info:" << info << std::endl;

	} else {
		std::cout << "Interne " << std::endl;

		//std::cout << "getWorld:" << getWorld(x, y, z) << "getBlockInfo():" << this->map->getBlockInfo(x, y, z) << std::endl;
		int value = -10;


		int qx = x;
		int qy = y;
		int qz = z;

		if (way == 1) // UP
			qy = qy + 1;
		if (way == 2) // DOWN
			qy = qy - 1;
		if (way == 3) // EST
			qx = qx + 1;
		if (way == 4) // OUEST
			qx = qx - 1;
		if (way == 5) // NORD
			qz = qz + 1;
		if (way == 6) // SUD
			qz = qz - 1;

		if (value = getWorld(qx, qy, qz) > 1)
			retour = true;

		std::cout << "Interne  x:"<< x <<" y:" << y << " z:" << z << "way" << way << "value:" << value << std::endl;
		this->map->getBlockInfoReallyMore(qx, qy, qz);
	}
	return (retour);
}


int		Chunk::getWorld(int x, int y, int z)
{
	return (this->world[x][y][z]);
}

void	Chunk::setWorld(int x, int y, int z, int val)
{
	this->world[x][y][z] = val;
}

void	Chunk::buildFace(int n, int x, int y, int z, int val)
{
	static int oneFace = ((sizeof(VCUBE) / 4)/6/2);
	static int oneFaceUV = ((sizeof(VCUBEUV) / 4)/6/2);
	int u = n + 1;

	for (int i = oneFace * n; i < oneFace * u; i+=3)
	{
		glm::vec3 vec = glm::make_vec3(&VCUBE[i]);
		vec.x = vec.x*0.5f + (float)x*1;
		vec.y = vec.y*0.5f +(float)y*1;
		vec.z = vec.z*0.5f +(float)z*1;
		points.push_back(vec);
	}

	for (int i = oneFace * n + 54; i < oneFace * u + 54; i+=3)
	{
		glm::vec3 vec = glm::make_vec3(&VCUBE[i]);
		vec.x = vec.x*0.5f + (float)x*1;
		vec.y = vec.y*0.5f +(float)y*1;
		vec.z = vec.z*0.5f +(float)z*1;
		points.push_back(vec);
	}

	for (int i = oneFaceUV * n; i < oneFaceUV * u; i+=2)
	{
		glm::vec2 vec = glm::make_vec2(&VCUBEUV[i]);
		if (val == 2)
			vec = glm::make_vec2(&VCUBEUVWATER[i]);
		else if (val == 4)
			vec = glm::make_vec2(&VCUBEUVEARTH[i]);
		else if (val == 5)
			vec = glm::make_vec2(&VCUBEUVSNOW[i]);
		uvs.push_back(vec);
	}

	for (int i = oneFaceUV * n + 36; i < oneFaceUV * u + 36; i+=2)
	{
		glm::vec2 vec = glm::make_vec2(&VCUBEUV[i]);
		if (val == 2)
			vec = glm::make_vec2(&VCUBEUVWATER[i]);
		else if (val == 4)
			vec = glm::make_vec2(&VCUBEUVEARTH[i]);
		else if (val == 5)
			vec = glm::make_vec2(&VCUBEUVSNOW[i]);
		uvs.push_back(vec);
	}
}

void 	Chunk::build(void)
{
	int sx, sy, sz;
	int oneFace = ((sizeof(VCUBE) / 4)/6);
	int oneFaceUV = ((sizeof(VCUBEUV) / 4)/6);

	sx = this->worldCoord.x;
	sy = this->worldCoord.y;
	sz = this->worldCoord.z;
	for (int x = sx; x < CHUNK_SIZE + sx; x++) {
		for (int z = sz; z < CHUNK_SIZE + sz; z++) {
			for (int y = this->minheight; y <= this->maxheight; y++) {
				if (this->getWorld(x, y, z) > 1) {
					int val = this->getWorld(x, y, z);

					if (!this->collide(x, y, z, 1)) {	// UP
						this->buildFace(1, x , y, z , val);
					}
					if (!this->collide(x, y, z, 2)) {	// DOWN
						this->buildFace(0, x , y, z , val);
					}
					if (!this->collide(x, y, z, 3)) {	//EST
						this->buildFace(2, x , y, z , val);
					}
					if (!this->collide(x, y, z, 4)) {	//OUEST
						this->buildFace(4, x , y, z , val);
					}
					if (!this->collide(x, y, z, 5)) {	//NORD
						this->buildFace(3, x , y, z , val);
					}
					if (!this->collide(x, y, z, 6)) {	//SUD
						this->buildFace(5, x , y, z , val);
					}
				}
			}
		}
	}
	sizeuv = this->uvs.size() * sizeof(glm::vec2);
	sizevert = this->points.size() * sizeof(glm::vec3);
	nb = (this->points.size());
	this->state = STATE::BUILD;
}

unsigned int Chunk::buildVAO(void) {
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	//VBO //Positions
	glGenBuffers(1, &this->VBO_VERT);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_VERT);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeVertices(), this->getVertices(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//UV texture coords
	glGenBuffers(1, &this->VBO_UV);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_UV);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeUVs(), this->getUVs(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return (this->VAO);
}

void	Chunk::updateVAO(void) {
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_VERT);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeVertices(), this->getVertices(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_UV);
	glBufferData(GL_ARRAY_BUFFER, this->getSizeUVs(), this->getUVs(), GL_STATIC_DRAW);
}

void	Chunk::cleanVAO(void) {
	glDeleteBuffers(1, &this->VBO_VERT);
	glDeleteBuffers(1, &this->VBO_UV);
	glDeleteVertexArrays(1, &this->VAO);
}

float	*Chunk::getVertices(void) {
	return (&this->points[0][0]);
}
size_t	Chunk::getSizeVertices(void) {
	return (sizevert);
}

float	*Chunk::getUVs(void) {
	return (&this->uvs[0][0]);
}
size_t	Chunk::getSizeUVs(void) {
	return (sizeuv);
}

size_t	Chunk::getTriangle(void) {
	return (nb);
}
