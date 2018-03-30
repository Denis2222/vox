#include <GameObject/Map/Chunk.hpp>

		Chunk::Chunk(int x, int y, int z, Map *map)
		{
			this->localCoord = glm::vec3(x, y, z);
			this->worldCoord = glm::vec3(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);
			this->state = STATE::INIT;
			this->map = map;
			bzero(&this->worldChar, CHUNK_SIZE * CHUNK_SIZE * (CHUNK_HEIGHT + 1));
		}

		Chunk::~Chunk()
		{
			points.clear();
			uvs.clear();
			bzero(&this->worldChar, CHUNK_SIZE * CHUNK_SIZE * (CHUNK_HEIGHT + 1));
		}

int		Chunk::getWorld(int x, int y, int z)
{
	unsigned int X, Y, Z;

	X = x;
	Y = y;
	Z = z;
	if (Y == -1)
		return (0);
	if (Y >= CHUNK_HEIGHT)
		return (0);

	if (Y > 256 || Y < 0 || X > CHUNK_SIZE - 1 || X < 0 || Z > CHUNK_SIZE - 1 || Z < 0)
	{
		return (0);
	}

	return (this->worldChar[X][Y][Z]);
}

void	Chunk::setWorld(int x, int y, int z, int val)
{
	unsigned int X, Y, Z;
	X = x;
	Y = y;
	Z = z;

	if (Y > 256 || Y < 0 || X > CHUNK_SIZE - 1 || X < 0 || Z > CHUNK_SIZE - 1 || Z < 0)
	{
		return ;
	}

	this->worldChar[X][Y][Z] = val;
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

	if (y%16 == 0)
		type=4;

	return (type);
}

void	Chunk::generate(void) {
	int sx, sy, sz;
	sx = this->worldCoord.x;
	sy = this->worldCoord.y;
	sz = this->worldCoord.z;

	this->minheight = 256;
	this->maxheight = 0;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			int height = getNoise(x + sx, z + sz);
			for (int y = 0; y < CHUNK_HEIGHT; y++)
			{
				if (y <= height)
				{
					//if (z == 0 || z == CHUNK_SIZE - 1)
						setWorld(x, y, z, getBlockType(x + sx, y, z + sz, height));
					//else if (x == 0 || x == CHUNK_SIZE - 1)
					//	setWorld(x, y, z, 2); //getBlockType(x + sx, y, z + sz, height)
					//else
						//setWorld(x, y, z, 3); //getBlockType(x + sx, y, z + sz, height)

					if (y >= this->maxheight)
						this->maxheight = y;
					if (y <= this->minheight)
						this->minheight = y;
				}
			}
		}
	}
	//printf("Generate : %d %d\n", this->minheight, this->maxheight);
	this->state = STATE::GENERATE;
}

void Chunk::interact(int x, int y, int z, int val) {
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

bool	Chunk::collide(int x, int y, int z, int way) {
	bool retour = false;
	int type = -1;


	//printf("extern\n");
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


	//Haut ou bas, facile
	if (way == 1 || way == 2)
	{
		if (getWorld(qx, qy , qz) > 1)
			retour = true;
	}
	else if (qx >= 0  && qx < CHUNK_SIZE && qz >= 0 && qz < CHUNK_SIZE)
	{
		//On est dans le chunk
		if (getWorld(qx, qy , qz) > 1)
			retour = true;
	}
	else {
		//On est hors du chunk on demande a la map

		type = this->map->getBlockInfo(qx + (int)this->worldCoord.x, qy, qz + (int)this->worldCoord.z);
		//printf("Askmap : x:%d y:%d z:%d info: %d \n", qx + (int)this->worldCoord.x, qy, qz+(int)this->worldCoord.z, type);
		if (type > 1)
			retour = true;
		else if (type < 0)
		{
			//La map le connais pas
			int noise = getNoise(qx + (int)this->worldCoord.x, qz + (int)this->worldCoord.z);
			if (qy <= noise)
			{
				type = getBlockType(qx + (int)this->worldCoord.x, qy, qz + (int)this->worldCoord.z, noise);
				if (type > 1)
					retour = true;
				else
					retour = false;
			} else {
				retour = false;
			}
		} else {
			retour = false;
		}
	}
	return (retour);
}

bool	Chunk::collideDebug(int x, int y, int z, int way) {
	/*
	printf("collide(%d, %d, %d) \n", x, y, z);
	printf("worldCoord(%d, %d, %d) \n", (int)this->worldCoord.x, (int)this->worldCoord.y, (int)this->worldCoord.z);*/
	bool retour = false;
	int type = -1;


	//printf("extern\n");
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


	//Haut ou bas, facile
	if (way == 1 || way == 2)
	{
		if (getWorld(qx, qy , qz) > 1)
			retour = true;
	}
	/*else if (qx >= 0  && qx < CHUNK_SIZE && qz >= 0 && qz < CHUNK_SIZE)
	{
		//On est dans le chunk
		if (getWorld(qx, qy , qz) > 1)
			retour = true;
	}*/
	else {
		//On est hors du chunk on demande a la map

		type = this->map->getBlockInfo(qx + (int)this->worldCoord.x, qy, qz + (int)this->worldCoord.z);
		printf("Askmap : x:%d y:%d z:%d info: %d \n", qx + (int)this->worldCoord.x, qy, qz+(int)this->worldCoord.z, type);
		if (type > 1)
			retour = true;
		else if (type < 0)
		{
			//La map le connais pas
			int noise = getNoise(qx + (int)this->worldCoord.x, qz + (int)this->worldCoord.z);
			if (qy <= noise)
			{
				type = getBlockType(qx + (int)this->worldCoord.x, qy, qz + (int)this->worldCoord.z, noise);
				if (type > 1)
					retour = true;
				else
					retour = false;
			} else {
				retour = false;
			}
		} else {
			retour = false;
		}
	}
	return (retour);
}

void	Chunk::buildFace(int n, int x, int y, int z, int val) {
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

void 	Chunk::build(void) {
	int sx, sy, sz;
	int oneFace = ((sizeof(VCUBE) / 4)/6);
	int oneFaceUV = ((sizeof(VCUBEUV) / 4)/6);

	sx = this->worldCoord.x;
	sy = this->worldCoord.y;
	sz = this->worldCoord.z;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int y = this->minheight; y <= this->maxheight; y++) {
				//printf("build()\n");
				if (y > 256 || y < 0)
				{
					printf("%d %d %d", x, y, z);
					printf("COLLIDE ECRIT ICI !\n");
					exit(0);
				}
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
