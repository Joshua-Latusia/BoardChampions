#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include <GL/freeglut.h>
#include <cstdio>
#include <cmath>
#include <vector>
#include "stb_image.h"



float lastFrameTime = 0;

int width, height;
int ImgArray[256][256];

GLuint textures = -1;

struct Camera
{
	float posX = 0;
	float posY = -4;
	float posZ = 0;
	float rotX = 0;
	float rotY = 0;
	float rotZ = 0;
} camera;

bool keys[255];

struct Vertex
{
	float x, y, z;
	float nx, ny, nz;
	float r, g, b, a;
};

std::vector<Vertex> cubeVertices;



void loadImage()
{
	int imgWidth, imgHeight, imgBpp;
	unsigned char* imgData = stbi_load("HeightMap3.png", &imgWidth, &imgHeight, &imgBpp, 4);

	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			ImgArray[x][y] = (int)(imgData[4 * (x + y * 256)] / 25.5);
		}
	}



}

void loadTexture()
{
	int imgWidth, imgHeight, imgBpp;

	glGenTextures(1, &textures);
	glBindTexture(GL_TEXTURE_2D, textures);
	unsigned char* imgData = stbi_load("texture.png", &imgWidth, &imgHeight, &imgBpp, 4);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,					//level
		GL_RGBA,			//internal format
		imgWidth,			//width
		imgHeight,			//height
		0,				//border
		GL_RGBA,			//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(imgData);
}

void drawHeigtMap()
{
	
	// eerste punt eerste punt 
	// hoogte vorig punt hoogte dit punt en dit punt 
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_TEXTURE_2D);
	float xCoord = 0;
	float yCoord= 0;
	
	for(int y = 0; y < 255; y++)
	{
		for (int x = 0; x < 255; x++)
		{
			if (ImgArray[x][y] == 0)
			{
				xCoord = 0.75f;
				yCoord = 0.75f;
			}
			else if (ImgArray[x][y] == 1)
			{
				xCoord = 0.25f;
				yCoord = 0.25f;
			}
			/*else if(ImgArray[x][y] <= 9 && ImgArray[x][y] > 4)
			{
				xCoord = 0.25f;
				yCoord = 0.25f;
			}
*/
			else if (ImgArray[x][y] > 2)
			{
				
				xCoord = 0;
				yCoord = 0;
				ImgArray[x][y] = ImgArray[x][y];
			}

			glBegin(GL_TRIANGLES);

			glTexCoord2f(xCoord, yCoord);  glVertex3f(x, ImgArray[x][y], y);
			glTexCoord2f(xCoord, yCoord+0.25); glVertex3f(x + 1, ImgArray[x + 1][y], y);
			glTexCoord2f(xCoord+0.25, yCoord+0.25); glVertex3f(x, ImgArray[x][y + 1], y + 1);

			glTexCoord2f(xCoord + 0.25, yCoord + 0.25); glVertex3f(x + 1, ImgArray[x + 1][y], y);
			glTexCoord2f(xCoord, yCoord + 0.25); glVertex3f(x+1, ImgArray[x+1][y + 1], y + 1);
			glTexCoord2f(xCoord, yCoord); glVertex3f(x, ImgArray[x][y+1], y+1);


		}
	}
	glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}




void display()
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width/height, 0.1, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posZ, camera.posY);

	float pos[4] = { 0.5, 1, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);


	glColor3f(0.1f, 1.0f, 0.2f);
	drawHeigtMap();

	glutSwapBuffers();
}

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void idle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME)/1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 10;
	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);
	if (keys['q']) camera.posZ -= deltaTime *speed;
	if (keys['e']) camera.posZ += deltaTime *speed;

	glutPostRedisplay();
}

bool justMoved = false;
void mousePassiveMotion(int x, int y)
{
	if (justMoved)
	{
		justMoved = false;
		return;
	}
	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(width / 2, height / 2);
		justMoved = true;
	}
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);
	keys[key] = true;
}

void keyboardUp(unsigned char key, int,int)
{
	keys[key] = false;
}



int main(int argc, char* argv[])
{
	width = 800;
	height = 600;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Hello World");

	loadImage();
	loadTexture();
	memset(keys, 0, sizeof(keys));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);



	glutWarpPointer(width / 2, height / 2);

	glutMainLoop();


	return 0;
}