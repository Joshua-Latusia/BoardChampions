#include "PlayingFieldComponent.h"
#include <GL/freeglut.h>

#include <cmath>


PlayingFieldComponent::PlayingFieldComponent(float newSize)
{
	size = newSize;
}

PlayingFieldComponent::PlayingFieldComponent(float newSize, char* texPath) : DrawComponent(texPath)
{
	size = newSize;
}


PlayingFieldComponent::~PlayingFieldComponent()
{
}

void PlayingFieldComponent::draw()
{
	float drawSize = size / 2.0f;
	if (texture)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->textureID);
	}

	glBegin(GL_QUADS);

	if (texture)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0, 0); glVertex3f(-drawSize, -drawSize, 0);
		glTexCoord2f(1, 0); glVertex3f(drawSize, -drawSize, 0);
		glTexCoord2f(1, 1); glVertex3f(drawSize, drawSize, 0);
		glTexCoord2f(0, 1); glVertex3f(-drawSize, drawSize, 0);
	}
	else
	{
		glColor3f(0, 0.5f, 0);
		glVertex3f(-drawSize, -drawSize, 0);
		glVertex3f(drawSize, -drawSize, 0);
		glVertex3f(drawSize, drawSize, 0);
		glVertex3f(-drawSize, drawSize, 0);
	}

	glEnd();

	if (texture)
	{
		glDisable(GL_TEXTURE_2D);
	}
}
