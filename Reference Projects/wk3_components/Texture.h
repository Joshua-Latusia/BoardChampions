#pragma once
class Texture
{
private:
	unsigned int load(char* path);

public:
	unsigned int textureID = -1;

	Texture(char* path);
	~Texture();
};

