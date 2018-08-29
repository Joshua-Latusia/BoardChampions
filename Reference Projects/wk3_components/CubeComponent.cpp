#include "CubeComponent.h"
#include <GL/freeglut.h>
#include <cmath>


CubeComponent::CubeComponent(float size)
{
	this->size = size;
}


CubeComponent::~CubeComponent()
{
}

void CubeComponent::draw()
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
		//TODO: add textured cube
	}
	else
	{
		glColor3f(1, 0, 0);
		glVertex3f(-drawSize, -drawSize, -drawSize);
		glVertex3f(-drawSize, -drawSize, drawSize);
		glVertex3f(-drawSize, drawSize, drawSize);
		glVertex3f(-drawSize, drawSize, -drawSize);

		glVertex3f(drawSize, -drawSize, -drawSize);
		glVertex3f(drawSize, -drawSize, drawSize);
		glVertex3f(drawSize, drawSize, drawSize);
		glVertex3f(drawSize, drawSize, -drawSize);

		glColor3f(0, 1, 0);
		glVertex3f(-drawSize, -drawSize, -drawSize);
		glVertex3f(-drawSize, -drawSize, drawSize);
		glVertex3f(drawSize, -drawSize, drawSize);
		glVertex3f(drawSize, -drawSize, -drawSize);

		glVertex3f(-drawSize, drawSize, -drawSize);
		glVertex3f(-drawSize, drawSize, drawSize);
		glVertex3f(drawSize, drawSize, drawSize);
		glVertex3f(drawSize, drawSize, -drawSize);

		glColor3f(0, 0, 1);
		glVertex3f(-drawSize, -drawSize, -drawSize);
		glVertex3f(-drawSize, drawSize, -drawSize);
		glVertex3f(drawSize, drawSize, -drawSize);
		glVertex3f(drawSize, -drawSize, -drawSize);

		glVertex3f(-drawSize, -drawSize, drawSize);
		glVertex3f(-drawSize, drawSize, drawSize);
		glVertex3f(drawSize, drawSize, drawSize);
		glVertex3f(drawSize, -drawSize, drawSize);
	}

	glEnd();

	if (texture)
	{
		glDisable(GL_TEXTURE_2D);
	}

	glBegin(GL_QUADS);
	

	glEnd();
}
