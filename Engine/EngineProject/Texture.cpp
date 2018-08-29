#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GL\freeglut.h"
#include <string>

Texture::Texture(std::string path)
{
	textureID = load(path);
}

Texture::~Texture()
{
}

unsigned int Texture::load(std::string path)
{
	//unsigned int textureID = -1;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Load texture image with SBI library
	int width, height, bpp;
	unsigned char* imgData = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData
	);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(imgData);
	return textureID;
}