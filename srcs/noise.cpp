#include <vox.h>
#include "FastNoise.h"

noise::module::Perlin noiseModule;

static FastNoise myNoise; // Create a FastNoise object


int getNoise(int x, int z)
{

	//int noise = (int)(noiseModule.GetValue ((double)((double)(x+20)/300.0f), (double)((double)(z+20)/300.0f), 1) * 50) + 50;


	//FastNoise Quick and dirty
	//myNoise.SetNoiseType(FastNoise::SimplexFractal);
	//myNoise.SetSeed(0);
	int noise = (int)(myNoise.GetValue((float)x,(float)z) * 40 + 50);


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
