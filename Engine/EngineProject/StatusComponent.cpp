#include "StatusComponent.h"
#include <GL/freeglut.h>



void drawCube(float drawSize)
{

	glVertex3f(-drawSize, -drawSize, -drawSize);
	glVertex3f(-drawSize, -drawSize, drawSize);
	glVertex3f(-drawSize, drawSize, drawSize);
	glVertex3f(-drawSize, drawSize, -drawSize);

	glVertex3f(drawSize, -drawSize, -drawSize);
	glVertex3f(drawSize, -drawSize, drawSize);
	glVertex3f(drawSize, drawSize, drawSize);
	glVertex3f(drawSize, drawSize, -drawSize);

	glVertex3f(-drawSize, -drawSize, -drawSize);
	glVertex3f(-drawSize, -drawSize, drawSize);
	glVertex3f(drawSize, -drawSize, drawSize);
	glVertex3f(drawSize, -drawSize, -drawSize);

	glVertex3f(-drawSize, drawSize, -drawSize);
	glVertex3f(-drawSize, drawSize, drawSize);
	glVertex3f(drawSize, drawSize, drawSize);
	glVertex3f(drawSize, drawSize, -drawSize);

	glVertex3f(-drawSize, -drawSize, -drawSize);
	glVertex3f(-drawSize, drawSize, -drawSize);
	glVertex3f(drawSize, drawSize, -drawSize);
	glVertex3f(drawSize, -drawSize, -drawSize);

	glVertex3f(-drawSize, -drawSize, drawSize);
	glVertex3f(-drawSize, drawSize, drawSize);
	glVertex3f(drawSize, drawSize, drawSize);
	glVertex3f(drawSize, -drawSize, drawSize);
}

StatusComponent::StatusComponent()
{
}

StatusComponent::~StatusComponent()
{
}

void StatusComponent::draw()
{
	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
	
	glColor3f(1, 0, 0);

	drawCube(statusPoints * 3.0f/ 20.0f / 2.0f);
	glEnd();


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	glBegin(GL_QUADS);	
	
	glColor4f(6, 6, 6,0.1f);
	
		drawCube(3 / 2.0f);
	glEnd();


	glDisable(GL_BLEND);

	



}
