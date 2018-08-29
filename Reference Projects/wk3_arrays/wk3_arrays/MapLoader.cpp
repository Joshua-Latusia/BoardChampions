#include "MapLoader.h"
#include "stb_image.h" 


unsigned int MapLoader::load(char * path)
{
	int imgWidth, imgHeight, imgBpp;
	unsigned char* imgData = stbi_load(path, &imgWidth, &imgHeight, &imgBpp, 4);

	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			ImgArray[x][y] = (int)(imgData[4 * (x + y * 256)] / 5);
		}
	}

	return 1;

}

MapLoader::MapLoader(char* path)
{
	load(path);
}


MapLoader::~MapLoader()
{
}
