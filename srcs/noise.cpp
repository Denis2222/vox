#include <vox.h>


noise::module::Perlin noiseModule;

 // Create a FastNoise object


std::map<std::pair<int,int>, int> makeBruit(void)
{
	float what = 300.0f;
	float that = 10;
	std::map<std::pair<int,int>, int> bruit;

	for (int x = -1000; x < 1000; x++)
	{
		for (int z = -1000; z < 1000; z++)
		{
			int noise = (int)(noiseModule.GetValue ((double)((double)(x+that)/what), (double)((double)(z+that)/what), 1) * 50) + 50;
			std::cout << x << " x " <<  z << " z " << noise << "     ";
			bruit[std::make_pair(x,z)] = noise;
			z++;
		}
		x++;
	}
	return (bruit);
}



int getNoise(int x, int z)
{
	float what = 300.0f;
	float that = 10;

	//return ((int)(noiseModule.GetValue ((double)((double)(x+that)/what), (double)((double)(z+that)/what), 1) * 50) + 50);

	//static std::map<std::pair<int,int>, int> bruit = makeBruit();


	//if (x > 1000 || x< -1000 | z > 1000 || z < -1000)
	//	return (1);
	//return (bruit[std::make_pair(x,z)]);

	//FastNoise Quick and dirty
	//myNoise.SetNoiseType(FastNoise::SimplexFractal);
	//myNoise.SetSeed(0);
	int noise = (int)(myNoise.GetValue((float)x,(float)z) * 50 + 50);


	//Pure speed
	//int noise =  40;
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
