#include "Terrain.hpp"

		Terrain::Terrain(void)
		{

			float what = 300.0f;
			float that = 10;

			for (int x = -1000; x < 1000; x++)
			{
				for (int z = -1000; z < 1000; z++)
				{
					map[x][z] = getNoise(x, z);
				}
			}


/*
			float what = 300.0f;
			float that = 10;

			for (int x = -1000; x < 1000; x++)
			{
				for (int z = -1000; z < 1000; z++)
				{
					map2d[glm::vec2(x,z)] = (int)(noiseModule.GetValue ((double)((double)(x+that)/what), (double)((double)(z+that)/what), 1) * 50) + 50;
				}
			}
*/
		}

		Terrain::~Terrain(void)
		{

		}
