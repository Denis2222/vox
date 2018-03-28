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

	if (x==0 && z == 0)
		noise = 50;

	if (x==0 && z == 10)
		noise = 45;

	if (x==0 && z == 1)
		noise = 35;

	return (noise);
}
