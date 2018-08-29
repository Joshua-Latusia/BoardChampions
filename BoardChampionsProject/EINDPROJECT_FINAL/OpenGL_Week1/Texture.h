#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/freeglut.h>


class Texture
{
public:
	Texture(std::string path);
	void loadTexture(std::string path);
	GLuint textureId;

};

#endif