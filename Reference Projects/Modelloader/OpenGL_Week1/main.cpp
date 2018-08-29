#define STB_PERLIN_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include <GL/freeglut.h>
#include "ObjModel.h"
#include "Texture.h"
#include <string>
#include "stb_perlin.h"
#include <iostream>
#include <math.h>


int height = 800;
int width = 1200;

int rotSteve = 0;
float posSteveX = 0;
float posSteveY = 0;
float posSteveZ = 0;

const int arrX = 50;
const int arrY = 50;
const int arrZ = 50;

int arr3D[arrX][arrY][arrZ];

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


void reshape(int w, int h)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void drawCube(int index)
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, text->textureId);

	glBegin(GL_QUADS);

	int column = 16;

	float right = (float)1 / column * (1 + (index  % column));
	float bottom = (float) 1/ column * (1 + floor(index / column));

	float width = (float)1 / column;

	//front
	glTexCoord2f(right - width, bottom - width);
	glVertex3f(0, 0, 0);
	glTexCoord2f(right - width, bottom);
	glVertex3f(0, 1, 0);
	glTexCoord2f(right, bottom);
	glVertex3f(1, 1, 0);
	glTexCoord2f(right, bottom - width);
	glVertex3f(1, 0, 0);


	//back
	glTexCoord2f(right - width, bottom - width);
	glVertex3f(0, 0, -1);
	glTexCoord2f(right - width, bottom);
	glVertex3f(0, 1, -1);
	glTexCoord2f(right, bottom);
	glVertex3f(1, 1, -1);
	glTexCoord2f(right, bottom - width);
	glVertex3f(1, 0, -1);


	//left side
	glTexCoord2f(right - width, bottom - width);
	glVertex3f(0, 0, 0);
	glTexCoord2f(right - width, bottom);
	glVertex3f(0, 1, 0);
	glTexCoord2f(right, bottom);
	glVertex3f(0, 1, -1);
	glTexCoord2f(right, bottom - width);
	glVertex3f(0, 0, -1);

	//right side
	glTexCoord2f(right - width, bottom - width);
	glVertex3f(1, 1, 0);
	glTexCoord2f(right - width, bottom);
	glVertex3f(1, 0, 0);
	glTexCoord2f(right, bottom);
	glVertex3f(1, 0, -1);
	glTexCoord2f(right, bottom - width);
	glVertex3f(1, 1, -1);

	//top side

	glTexCoord2f(right - width, bottom - width);
	glVertex3f(0, 1, 0);
	glTexCoord2f(right - width, bottom);
	glVertex3f(1, 1, 0);
	glTexCoord2f(right, bottom);
	glVertex3f(1, 1, -1);
	glTexCoord2f(right, bottom - width);
	glVertex3f(0, 1, -1);

	////bottom side
	//glVertex3f(0, 0, 0);
	//glVertex3f(1, 0, 0);
	//glVertex3f(1, 0, -1);
	//glVertex3f(0, 0, -1);

	glEnd();

}

void display()
{
	glClearColor(0.6f, 0.6f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();



	gluPerspective(60.0f, (float)width / (float)height, 0.1f, 100.0f);



	//glOrtho(0, (float)width, (float)height, 0, 0.1f, 25.0f);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	/*gluLookAt(0,0,50, 
		0,0,0,
		0,1,0);
*/
	glPushMatrix();
	glScalef(0.4f,0.4f,0.4f);
	//std::cout << float << std::endl;
	
	glTranslatef(1.5 + posSteveX, 4 , 2 + -posSteveZ);
	models[currentModel].second->draw();
	glPopMatrix();


	for (int i = 0; i<arrX; i++) {
		for (int j = 0; j<arrY; j++) {
			for (int k = 0; k<arrZ; k++) {
				if (arr3D[i][j][k] == 1)
				{
					glPushMatrix();
					glTranslatef(i, j, k);
					drawCube(244);
					glPopMatrix();
				}
				if (arr3D[i][j][k] == 2)
				{
					glPushMatrix();
					glTranslatef(i, j, k);
					drawCube(3);
					glPopMatrix();
				}

			}
		}
	}




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


	models.push_back(std::pair<int, ObjModel*>(3, new ObjModel("models/steve/steve.obj")));
}


int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Hello OpenGL");

	memset(keys, 0, sizeof(keys));

	initGraphics();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMotionFunc(mouseMotion);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	for (int i = 0; i<arrX; i++) {
					for (int k = 0; k<arrZ; k++) {
						float number = abs(stb_perlin_noise3((float)i / arrX, (float)k / arrZ, 0, 0, 0, 0) * 10);
					for (int j = 0; j<arrY; j++) {

					if (j <= number)
					{
						arr3D[i][j][k] = 1;
					}
					else if (j > number)
					{
						arr3D[i][j][k] = 2;
						break;
					}

			
				}
			}
		}
	

	text = new Texture("texture.png");


	glutMainLoop();

	return 0;
}