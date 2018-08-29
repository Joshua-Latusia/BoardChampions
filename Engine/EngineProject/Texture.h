#pragma once
#include <string>

class Texture
{
private:
	unsigned int load(std::string path);

public:
	unsigned int textureID = -1;

	Texture(std::string path);
	~Texture();
};

