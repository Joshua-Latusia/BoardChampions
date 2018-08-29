#pragma once
#include <vector>

class Texture
{
private:
	unsigned int load(char* path);

public:
	unsigned int textureID = -1;
	unsigned char* RGBAPixelData;

	Texture(char* path);
	~Texture();
};

