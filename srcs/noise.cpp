#include <vox.h>


noise::module::Perlin noiseModule;



int getNoise(int x, int z)
{
	float what = 300.0f;
	float that = 10;
	int min = 1;

	int noise = ((int)(noiseModule.GetValue ((double)((double)(x+that)/what), 100,  (double)((double)(z+that)/what)) * 50) + 50);

	if (noise < 40)
		noise = 40;

	//static std::map<std::pair<int,int>, int> bruit = makeBruit();



	if (x==0 && z == 0)
		noise = 50;

	if (x==0 && z == 10)
		noise = 45;

	if (x==0 && z == 1)
		noise = 35;
	//if (x > 1000 || x< -1000 | z > 1000 || z < -1000)
	//	return (1);
	//return (bruit[std::make_pair(x,z)]);
	//myNoise.SetSeed(0);
	//myNoise.SetNoiseType(FastNoise::Perlin);
	//FastNoise Quick and dirty
	//myNoise.SetNoiseType(FastNoise::SimplexFractal);
	//myNoise.SetSeed(0);
	//int noise = (int)(myNoise.GetValue((float)x,(float)z) * 50 + 50);


	//Pure speed
	//int noise =  30;
	return (noise);
}


/*
struct timespec start, end;
clock_gettime(CLOCK_MONOTONIC_RAW, &start);
//do stuff
usleep(1000000);
clock_gettime(CLOCK_MONOTONIC_RAW, &end);

uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
*/
