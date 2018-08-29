#define STB_PERLIN_IMPLEMENTATION
#define _USE_MATH_DEFINES

#define MAX_HEIGHT 20;

#include <GL/freeglut.h>
#include <vector>;
#include "ObjModel.h"
#include "Texture.h"
#include <string>
#include <iostream>
#include <math.h>
#include "stb_image.h"
#include "Vertex.h"


int height = 800;
int width = 1200;

int rotSteve = 0;
float posSteveX = 0;
float posSteveY = 0;
float posSteveZ = 0;

const int arrX = 50;
const int arrY = 50;
const int arrZ = 50;

std::vector<Vertex> heightmap;

Texture* text;

int currentModel = 0;

std::vector<std::pair<int, ObjModel*> > models;

struct Camera
{
	float posX = 10;
	float posY = -10;
	float posZ = 0;

	float rotX = 10;
	float rotY = 120;
} camera;

bool keys[255];

int lastTime = 0;


void display()
{
	glClearColor(0.6f, 0.6f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, (float)width / (float)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	float pos[4] = { 0.5, 10, -1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);


	glPushMatrix();
	glTranslatef(0, 0, 0);
	models[currentModel].second->draw();
	glPopMatrix();

	


	glutSwapBuffers();

}



void keyboard(unsigned char key, int x, int  y)
{

	if (key == 27)
		exit(0);
	keys[key] = true;
	
}

void keyboardUp(unsigned char key, int, int)
{
	keys[key] = false;
}


void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posZ += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}



void mouseMotion(int x, int y)
{
	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(width / 2, height / 2);
	}
}



void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	const float speed = 5;
	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);

	if (keys['q']) camera.posY -= deltaTime * speed;
	if (keys['e']) camera.posY += deltaTime * speed;

	if (keys['i']) posSteveX += deltaTime * speed;
	if (keys['j']) { posSteveZ += deltaTime * speed; rotSteve += 90; }
	if (keys['k']) posSteveX -= deltaTime * speed;
	if (keys['l']) posSteveZ -= deltaTime * speed;



	glutPostRedisplay();
}

void initGraphics(void)
{
	glEnable(GL_DEPTH_TEST);


	models.push_back(std::pair<int, ObjModel*>(0, new ObjModel("models/steve/steve.obj")));
}






int main(int argc, char* argv[])
{


	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Hello OpenGL");

	memset(keys, 0, sizeof(keys));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	initGraphics();

	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMotionFunc(mouseMotion);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glutWarpPointer(width / 2, height / 2);

	glutMainLoop();

	return 0;
}