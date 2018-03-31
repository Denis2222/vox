#include <vox.h>


noise::module::Perlin noiseModule;



int getNoise(int x, int z)
{
	float what = 300.0f;
	float that = 10;

	int noise = ((int)(noiseModule.GetValue ((double)((double)(x+that)/what), 100,  (double)((double)(z+that)/what)) * 100) + 10);

	if (noise < 2)
		noise = 2;

	if (x==0 && z == 0)
		noise = CHUNK_HEIGHT;

	return (noise);
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
