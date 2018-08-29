#include "ProjectionComponent.h"
#include "GL/freeglut.h"
#include "Texture.h"
#include "PlayingfieldComponent.h"
#include <iostream>

Texture * tex;

ProjectionComponent::ProjectionComponent()
{
	tex = new Texture("Map_Beamer_V2.png");
}

void ProjectionComponent::display()
{
	//tex = new Texture("Map_Beamer_V2.png");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

	// Draw a Red 1x1 Square centered at origin
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 1);

	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
	glTexCoord2f(0, 0);  glVertex2f(-1, 1);    // x, y
	glTexCoord2f(0, 1); glVertex2f(-1, -1);
	glTexCoord2f(1, 1); glVertex2f(1, -1);
	glTexCoord2f(1, 0); glVertex2f(1, 1);

	glDisable(GL_TEXTURE_2D);
	glEnd();

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (PlayingFieldComponent::fields[x][y]->filled)
			{
				glPushMatrix();
				glTranslatef(y*0.165f, x*0.195f, 0);
				glBegin(GL_QUADS);
				glColor3f(1, 0, 0);
				glVertex2f(0, 0.5f / 2.7f);
				glVertex2f(0.5f / 2.97f, 0.5f / 2.7f);
				glVertex2f(0.5f / 2.97f, 0);
				glVertex2f(0, 0);
				glEnd();
				glPopMatrix();
			}
		}
		glColor3f(1, 1, 1);
	}
	glutSwapBuffers();
}

void ProjectionComponent::update()
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (PlayingFieldComponent::fields[x][y]->filled)
			{
				glPushMatrix();
				glTranslatef(y*0.165f, x*0.195f, 0);
				glBegin(GL_QUADS);
				glColor3f(1, 0, 0);
				glVertex2f(0, 0.5f / 2.7f);
				glVertex2f(0.5f / 2.97f, 0.5f / 2.7f);
				glVertex2f(0.5f / 2.97f, 0);
				glVertex2f(0, 0);
				glEnd();
				glPopMatrix();
			}
		}
	}
	glutSwapBuffers();

}

void ProjectionComponent::drawAllFields()
{
}

ProjectionComponent::~ProjectionComponent()
{
}
