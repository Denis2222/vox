#include <vox.h>


noise::module::Perlin noiseModule;

void noiseParam(int seed) {
	noiseModule.SetOctaveCount (6);
	noiseModule.SetFrequency (1.0);
	noiseModule.SetSeed(seed);
}

double ridgenoise(int x, int z) {
	float what = 200.0f;
  return 2 * (0.5 - abs(0.5 - noiseModule.GetValue ((double)(x/what), 0,  (double)(z/what))));
}

int getHeight(int x, int z)
{
	int noise;
	float what;
	//Montagneux
	what = 300.0f; // Lissage
	//int noise = ((int)(noiseModule.GetValue ((double)(x/what), 100,  (double)(z/what)) * 100) + 70);

	//Plaines
	//what = 1000;
	//int noise = ((int)(noiseModule.GetValue ((double)(x/what), 100,  (double)(z/what)) * 100) + 45);


	//int noise = getMoisture(x, z);
	//if (noise > 20)
	//{
		what = 400.0f; // Lissage
		noise = ((int)(noiseModule.GetValue ((double)(x/what), 100,  (double)(z/what)) * 70) + 80);
	//}
	//else
	//{
	//	what = 800;
	//	noise = ((int)(noiseModule.GetValue ((double)(x/what), 100,  (double)(z/what)) * 100) + 5);
	//}
	if (noise < 1)
		noise = 1;

	if (x==500 && z == 500)
		noise = 4;
	if (x==502 && z == 500)
		noise = 5;
	if (x==501 && z == 501)
		noise = 6;

	return (noise);
}

int getTree(int x, int y, int z)
{
	int noise;
	float what;
	//Montagneux
	what = 10.0f; // Lissage
	//int noise = ((int)(noiseModule.GetValue ((double)(x/what), 100,  (double)(z/what)) * 100) + 70);

	//Plaines
	//what = 1000;
	//int noise = ((int)(noiseModule.GetValue ((double)(x/what), 100,  (double)(z/what)) * 100) + 45);


	//int noise = getMoisture(x, z);
	//if (noise > 20)
	//{
		what = 2.0f; // Lissage
		noise = ((int)(noiseModule.GetValue ((double)(x/what), 10,  (double)(z/what)) * 70) + 40);
	//}
	//else
	//{
	//	what = 800;
	//	noise = ((int)(noiseModule.GetValue ((double)(x/what), 100,  (double)(z/what)) * 100) + 5);
	//}

	if (noise > 100 && y > 6)
		return (1);
	else
		return (0);
}


int getMoisture(int x, int z)
{
	float what = 300.0f;
	float that = 10;
	int noise = (int)(noiseModule.GetValue ((double)(x/what), 0,  (double)(z/what))* 100);
	return (noise);
}

int		getBlockType(int x, int y, int z, int height) {
	int type = 1;

	if (y <= height && y >= 10)
		{
			float what = 50.0f;
			int noise = (int)(noiseModule.GetValue ((double)(x/what),(double)(y/what),  (double)(z/what))* 20);
			if (noise > 20)
				return (0);
			/*else
				if (noise >0 && noise < 10)
					return (GRASS);
				if (noise >10 && noise < 20)
					return (FOREST);*/
		}

	if (y <= 5)
		return (WATER); //Water

	if (y < 8)
		return(SAND); // Rock

	if (y > 80 && getMoisture(x, z) > 10)
		return (ICE);

	if (y%CHUNK_SIZE == 0)
		return(ROCK);

	if (y <= height && y > (height - 3))
	{
		if (getMoisture(x, z) > height)
			return(GRASS); //  Grass
		else
			return(FOREST);
	}



	return (ROCK); // Rock
}

/*
float *uvArray(int val, int i)
{
	float uv[108] = {
		1.000000 , 0.000000, id,
		0.000000 , 1.000000, id,
		0.000000 , 0.000000, id,
		1.000000 , 0.000000, id,
		0.000000 , 1.000000, id,
		0.000000 , 0.000000, id,
		1.000000 , 0.000000, id2,
		0.000000 , 1.000000, id2,
		0.000000 , 0.000000, id2,
		1.000000 , 0.000000, id2,
		0.000000 , 1.000000, id2,
		0.000000 , 0.000000, id2,
		0.000000 , 0.000000, id3,
		1.000000 , 1.000000, id3,
		0.000000 , 1.000000, id3,
		1.000000 , 0.000000, id3,
		0.000000 , 1.000000, id3,
		0.000000 , 0.000000, id3,
		1.000000 , 0.000000, id4,
		1.000000 , 1.000000, id4,
		0.000000 , 1.000000, id4,
		1.000000 , 0.000000, id4,
		1.000000 , 1.000000, id4,
		0.000000 , 1.000000, id4,
		1.000000 , 0.000000, id5,
		1.000000 , 1.000000, id5,
		0.000000 , 1.000000, id5,
		1.000000 , 0.000000, id5,
		1.000000 , 1.000000, id5,
		0.000000 , 1.000000, id5,
		0.000000 , 0.000000, id6,
		1.000000 , 0.000000, id6,
		1.000000 , 1.000000, id6,
		1.000000 , 0.000000, id6,
		1.000000 , 1.000000, id6,
		0.000000 , 1.000000, id6
	}

	return (uv[i]);
}
*/

glm::vec3 getUVBlock(int val, int i)
{
	glm::vec3 vec = glm::make_vec3(&VCUBEUV[i]);
	/*
	if (val == WATER)
		vec = glm::make_vec2(&VCUBEUVWATER[i]);
	else if (val == ROCK)
		vec = glm::make_vec2(&VCUBEUVEARTH[i]);
	else if (val == ICE)
		vec = glm::make_vec2(&VCUBEUVSNOW[i]);
	else if (val == GRASS)
		vec = glm::make_vec2(&VCUBEUVGRASS[i]);
	else if (val == SAND)
		vec = glm::make_vec2(&VCUBEUVSAND[i]);*/
	return (vec);
}




int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
	result = result / 1024;
    return result;
}
