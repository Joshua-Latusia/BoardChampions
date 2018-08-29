#include "UISystem.h"
#include "GL\freeglut.h"
#include "Game.h"



void UISystem::drawString(char *string, int height)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, 0, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);


	glRasterPos2i(20, height);
	void *font = GLUT_BITMAP_HELVETICA_18;
	for (char* c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}


	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}


void UISystem::init()
{
}

void UISystem::update(float dt)
{
}

UISystem::UISystem()
{
}


UISystem::~UISystem()
{
}
