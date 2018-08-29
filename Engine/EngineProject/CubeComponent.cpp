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

	glBegin(GL_QUADS);


		glColor3f(1, 0, 0);
		glVertex3f(-drawSize, -drawSize, -drawSize);
		glVertex3f(-drawSize, -drawSize, drawSize);
		glVertex3f(-drawSize, drawSize, drawSize);
		glVertex3f(-drawSize, drawSize, -drawSize);

		glColor3f(1, 1, 1);
		glVertex3f(drawSize, -drawSize, -drawSize);
		glVertex3f(drawSize, -drawSize, drawSize);
		glVertex3f(drawSize, drawSize, drawSize);
		glVertex3f(drawSize, drawSize, -drawSize);

		//glColor3f(0, 1, 0);
		glVertex3f(-drawSize, -drawSize, -drawSize);
		glVertex3f(-drawSize, -drawSize, drawSize);
		glVertex3f(drawSize, -drawSize, drawSize);
		glVertex3f(drawSize, -drawSize, -drawSize);

		glVertex3f(-drawSize, drawSize, -drawSize);
		glVertex3f(-drawSize, drawSize, drawSize);
		glVertex3f(drawSize, drawSize, drawSize);
		glVertex3f(drawSize, drawSize, -drawSize);

		//glColor3f(0, 0, 1);
		glVertex3f(-drawSize, -drawSize, -drawSize);
		glVertex3f(-drawSize, drawSize, -drawSize);
		glVertex3f(drawSize, drawSize, -drawSize);
		glVertex3f(drawSize, -drawSize, -drawSize);

		glVertex3f(-drawSize, -drawSize, drawSize);
		glVertex3f(-drawSize, drawSize, drawSize);
		glVertex3f(drawSize, drawSize, drawSize);
		glVertex3f(drawSize, -drawSize, drawSize);
		glColor3f(1, 1, 1);

	glEnd();


}
