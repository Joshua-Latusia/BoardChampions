#include <GL/freeglut.h>
#include <cstdio>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "Texture.h"
#include "MapLoader.h"
#include "Vec.h"
#include "stb_image.h"

float lastFrameTime = 0;
int width, height;
bool wireframeMode = false;

MapLoader *heightmap;
Texture *texture;
GLuint textures = -1;

struct field
{
	float x, y, z;
	bool solid;
	float width, height;
} ;

struct Camera
{
	float posX = 0;
	float posY = -4;
	float posZ = -20;
	float rotX = 0;
	float rotY = 0;
} camera;

bool keys[255];

struct Vertex
{
	float x, y, z;
	float nx, ny, nz;
	float r, g, b, a;
};

struct TexVertex
{
	float x, y, z;
	float nx, ny, nz;
	float texX, texY;
};
struct LineVertex
{
	float x, y, z;

};

std::vector<Vertex> cubeVertices;
std::vector<TexVertex> heightmapVex;
std::vector<LineVertex> linesVex;
std::vector<field> fields;

void drawHeightMap()
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glShadeModel(GL_SMOOTH);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, sizeof(TexVertex), ((float*)heightmapVex.data()) + 6);
	glNormalPointer(GL_FLOAT, sizeof(TexVertex), ((float*)heightmapVex.data()) + 3);
	glVertexPointer(3, GL_FLOAT, sizeof(TexVertex), ((float*)heightmapVex.data()) + 0);
	glDrawArrays(GL_TRIANGLES, 0, heightmapVex.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}


void drawLines()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(LineVertex), ((float*)linesVex.data()) + 0);	
	glDrawArrays(GL_LINES, 0, linesVex.size());
	glDisableClientState(GL_VERTEX_ARRAY);

}

void display()
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	 gluPerspective(60.0f, (float)width/height, 0.1, 500);
	//glOrtho(-10, 10, 10, -10, 10, -10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posZ, camera.posY);

	float pos[4] = { 0.5, 1, -1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glPushMatrix();
	if (wireframeMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	

	drawHeightMap();
	drawLines();

	glPopMatrix();

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

	const float speed = 25;
	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);
	if (keys['q']) camera.posZ -= deltaTime*speed;
	if (keys['e']) camera.posZ += deltaTime*speed;
	

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
	if (key == 'f') wireframeMode = !wireframeMode;
}

Vec3f calculateNormal(Vec3f* v1, Vec3f* v2, Vec3f* v3)
{
	Vec3f va, vb, vr;
	float val;
	va.x = v1->x - v2->x;
	va.y = v1->y - v2->y;
	va.z = v1->z - v2->z;

	vb.x = v1->x - v3->x;
	vb.y = v1->y - v3->y;
	vb.z = v1->z - v3->z;

	vr.x = (va.y * vb.z) - (vb.y * va.z);
	vr.y = (vb.x * va.z) - (va.x * vb.z);
	vr.z = (va.x * vb.y) - (vb.x * va.y);

	val = sqrtf((vr.x * vr.x) + (vr.y * vr.y) + (vr.z * vr.z));
	
	Vec3f norm;
	//norm.x = vr.x / val;
	//norm.y = vr.y / val;
	//norm.z = vr.z / val;

	norm.x = (va.x + va.y + va.z) / 3;
	norm.y = (vb.x + vb.y + vb.z) / 3;
	norm.z = (vr.x + vr.y + vr.z) / 3;

	return norm;
}


int main(int argc, char* argv[])
{
	width = 800;
	height = 600;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Hello World");

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
	glutFullScreen();

	heightmap = new MapLoader("HeightMap3.png");
	texture = new Texture("texture.png");

	glEnable(GL_TEXTURE_2D);
	float xCoord = 0;
	float yCoord = 0;

	for (int y = 0; y < 255; y++)
	{
		for (int x = 0; x < 255; x++)
		{
			if (heightmap->ImgArray[x][y] <= 2)
			{
				xCoord = 0.75f;
				yCoord = 0.75f;
			}			
			else if (heightmap->ImgArray[x][y] > 2 && heightmap->ImgArray[x][y] <= 4)
			{

				xCoord = 0.50f;
				yCoord = 0.50f;

			}
			else if (heightmap->ImgArray[x][y] > 4 && heightmap->ImgArray[x][y] <= 12)
			{
				xCoord = 0.25f;
				yCoord = 0.25f;
			} 
			
			else if (heightmap->ImgArray[x][y] > 12)
			{

				xCoord = 0;
				yCoord = 0;
			}

			//Right triangle
			//glTexCoord2f(xCoord, yCoord);
			Vec3f* vec1 = new Vec3f(x, y, heightmap->ImgArray[x][y]);
			//glTexCoord2f(xCoord, yCoord + 0.25);
			Vec3f* vec2 = new Vec3f(x+1, y, heightmap->ImgArray[x+1][y]);
			//glTexCoord2f(xCoord + 0.25, yCoord + 0.25);
			Vec3f* vec3 = new Vec3f(x+1, y+1, heightmap->ImgArray[x+1][y+1]);
			Vec3f normal = calculateNormal(vec1, vec2, vec3);

			float verX = x;
			float verY = y;
			float verZ = heightmap->ImgArray[x][y];
			
			heightmapVex.push_back(TexVertex{ verX,verZ,verY, 
				normal.x,normal.z,normal.y, xCoord, yCoord});

			verX = x + 1;
			verY = y;
			verZ = heightmap->ImgArray[x+1][y];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord, yCoord+0.25f});

			verX = x + 1;
			verY = y + 1;
			verZ = heightmap->ImgArray[x+1][y+1];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord+0.25f, yCoord + 0.25f});

			//Left triangle
			//glTexCoord2f(xCoord, yCoord);
			Vec3f* vec4 = new Vec3f(x, y, heightmap->ImgArray[x][y]);
			//glTexCoord2f(xCoord + 0.25, yCoord + 0.25);
			Vec3f* vec5 = new Vec3f(x + 1, y + 1, heightmap->ImgArray[x+1][y]);
			//glTexCoord2f(xCoord, yCoord + 0.25);
			Vec3f* vec6 = new Vec3f(x, y + 1, heightmap->ImgArray[x][y+1]);
			Vec3f normal2 = calculateNormal(vec1, vec2, vec3);


			verX = x;
			verY = y;
			verZ = heightmap->ImgArray[x][y];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY, 
				normal.x,normal.z,normal.y, xCoord, yCoord});

			verX = x + 1;
			verY = y + 1;
			verZ = heightmap->ImgArray[x+1][y+1];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord + 0.25f, yCoord + 0.25f});

			verX = x;
			verY = y + 1;
			verZ = heightmap->ImgArray[x][y+1];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord, yCoord + 0.25f});

			if (x == 61 && y == 217)
			{
			
			}


			if (x >= 61 && x < 189 && y >= 37 && y < 217)
			{
				if (x % 16 == 13 && y % 18 == 1)
				{
					fields.push_back(field{ (float)x, (float)y, (float)heightmap->ImgArray[x][y] + 0.1f, false,(float)16, (float)18 });
					linesVex.push_back(LineVertex{ (float)x, (float)heightmap->ImgArray[x][y] + 0.1f,(float)y });
					linesVex.push_back(LineVertex{ (float)x + 16, (float)heightmap->ImgArray[x][y] + 0.1f,(float)y });
					linesVex.push_back(LineVertex{ (float)x, (float)heightmap->ImgArray[x][y] + 0.1f,(float)y });
					linesVex.push_back(LineVertex{ (float)x, (float)heightmap->ImgArray[x][y] + 0.1f, (float)y + 18 });
					linesVex.push_back(LineVertex{ (float)x + 16,(float)heightmap->ImgArray[x][y] + 0.1f,(float)y });
					linesVex.push_back(LineVertex{ (float)x + 16, (float)heightmap->ImgArray[x][y] + 0.1f, (float)y + 18 });
					linesVex.push_back(LineVertex{ (float)x,(float)heightmap->ImgArray[x][y] + 0.1f,(float)y + 18 });
					linesVex.push_back(LineVertex{ (float)x + 16,(float)heightmap->ImgArray[x][y] + 0.1f,(float)y + 18 });
				}
			}
		}
	}


	glutMainLoop();


	return 0;
}