#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "stb_image.h"
#include <string>
#include <iostream>

Texture::Texture(std::string path) :textureId(-1)
{
	loadTexture(path);
	std::cout << textureId << std::endl;
}
	


void Texture::loadTexture(std::string path)
{
	//textures
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	stbi_set_flip_vertically_on_load(true);

	int width, height, bpp;
	stbi_uc* imgData = stbi_load(path.c_str(), &width, &height, &bpp, 4);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData);		//data
	stbi_image_free(imgData);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
