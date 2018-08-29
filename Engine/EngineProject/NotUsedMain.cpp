#include <GL/freeglut.h>
#include <math.h>
#include "GameObject.h"
#include "CubeComponent.h"
#include "SpinComponent.h"
#include "MoveComponent.h"
#include "PlayingFieldComponent.h"
#include "EventSystem.h"
#include "Subject.h"
#include "InputSystem.h"

int height = 800;
int width = 1200;

float angle = 0.0f;

bool keys[256];

std::list<GameObject*> objects;

//TEMP
InputSystem inputSystem;
Subject inputEvents;
//TEMP


void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int  y)
{
	keys[key] = true;
	if (key == 27)
		exit(0);
}


//void keyboardUp(unsigned char key, int x, int y)
//{
//	keys[key] = false;
//}


void init()
{
	glEnable(GL_DEPTH_TEST);
	
	memset(keys, false, sizeof(keys));
	

	//Add gameobjects
	//Add playing field
	GameObject* field = new GameObject();
	field->addComponent(new PlayingFieldComponent("tilesheet.png", "background.png"));
	field->scale = Vec3fl(2.0f, 1.0f, 1.0f);
	field->position = Vec3fl(0.0f, 0.0f, 0.0f);
	objects.push_back(field);

	//Add moveable cube
	GameObject* gObj = new GameObject();
	gObj->addComponent(new CubeComponent(0.5f));

	//Try something with event handling

	Component* moveComp = new MoveComponent();
	inputEvents.attachListener((MoveComponent*)moveComp);
	
	gObj->addComponent(moveComp);
	gObj->addComponent(new SpinComponent(90.0f));
	gObj->position = Vec3fl(0.0f, 0.0f, 0.25f);
	objects.push_back(gObj);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	gluLookAt(0, -6, 8,
			  0, 0, 0,
			  0, 1, 0);


	for (auto &o : objects)
	{
		o->draw();
	}
		
	glutSwapBuffers();
}


int lastTime = 0;
void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	angle += deltaTime;

	for (auto &o : objects)
	{
		o->update(deltaTime);
	}

	glutPostRedisplay();
}
//
//int main(int argc, char* argv[])
//{
//	
//
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
//	glutInitWindowSize(width, height);
//	glutInit(&argc, argv);
//	glutCreateWindow("Hello OpenGL");
//	glutDisplayFunc(display);
//	glutIdleFunc(idle);
//	glutReshapeFunc(reshape);
//
//	/*INIT SYSTEMS*/
//	inputSystem.init();
//	/*END INIT SYSTEMS*/
//
//	glutKeyboardFunc(keyboard);
//	inputClass.init();
//	//glutKeyboardUpFunc(keyboardUp);
//	//opengl init
//	init();
//
//	glutMainLoop();
//
//	return 0;
//}

