#include "InputSystem.h"
#include "GameLogicSystem.h"
#include "Game.h"
#include "GL/freeglut.h"
#include "ProjectionComponent.h"
#include "ComputerVisionComponent.h"
#include "CubeComponent.h"
#include "Card.h"

/*Screen (width, height)*/
Game::Screen Game::screen = { 1200, 800 };

/*Camera*/
Game::Camera Game::camera;

/*Systems*/
InputSystem* Game::inputSystem = new InputSystem;
GameLogicSystem* Game::gameLogicSystem = new GameLogicSystem;

/*Event handler for input, receives input events from input system*/
Subject Game::inputEvents = Subject();

/*Timer for handling delta time*/
int Game::lastTime = 0;


void Game::init(int argc, char* argv[])
{
	/*Create opengl window*/
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	/*glutInitWindowSize(1456, 2000000);

	glutCreateWindow("Board Champions 2D Beamer");
	///*All opengl functions
	ProjectionComponent();
	glutDisplayFunc(ProjectionComponent::display);
	glutIdleFunc(ProjectionComponent::update);
	glutReshapeFunc(Game::reshape);
	glutPositionWindow(2147,-30);
*/
	glutInitWindowSize(screen.width, screen.height);


	glutCreateWindow("Board Champions");
	/*All opengl functions*/
	glutDisplayFunc(Game::display);
	glutIdleFunc(Game::update);
	glutReshapeFunc(Game::reshape);

	



	/*Init game systems*/
	inputSystem->init();
	gameLogicSystem->init();

	/*Opengl specific init */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 10.f);
	glFogf(GL_FOG_END, 500.f);
	float FogCol[3] = { 1.0f,1.0f,1.0f };
	glFogfv(GL_FOG_COLOR, FogCol);
	glEnable(GL_LIGHT1);

	GLfloat  lightPos0[] = { -100, -100, -100, 0 };
	GLfloat lightPos1[] = { 1,1,1,0 };
	//GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
	//GLfloat lightPos0[] = { -120,10,-420, 1.0f }; //Positioned at (4, 0, 8)
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightPos1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);


	//glEnable(GL_FOG);
	//glFogi(GL_FOG_MODE, GL_LINEAR);
	//glFogf(GL_FOG_START, 10.f);
	//glFogf(GL_FOG_END, 500.f);
	//float FogCol[3] = { 0.8f,0.8f,0.8f };
	//glFogfv(GL_FOG_COLOR, FogCol);

	glEnable(GL_NORMALIZE);

	/*OpenCv specific inits */
glutMainLoop();


	/*Enable lighting*/
	float pos[4] = { -200.0f, -100.0f, -40.0f, 0 };

	glutMainLoop();
}


void Game::update()
{
	//Calculate delta time
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	//Update systems with parameter deltatime
	inputSystem->update(deltaTime);
	gameLogicSystem->update(deltaTime);
	
	glutPostRedisplay();
}


void Game::display()
{
	glClearColor(0.6f, 0.6f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, screen.width / (float)screen.height, 0.1f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	//glRotatef(camera.rotZ, 0, 0, 1);
	glTranslatef(camera.posX, camera.posZ, camera.posY);

	glColor3f(1.0f, 1.0f, 1.0f);


	GLfloat  lightPos[] = { 27.104f/100,126.887f/100,67.11f/100, 0 };
	GLfloat lightmodel[] = { 0.05,0.05,0.05,1.0f };
	GLfloat diffuse[]{ 1.5,1.5,1.5,1 };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightmodel);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	


	/*TODO: Add system drawing here*/
	glPushMatrix();
	gameLogicSystem->draw();
	glPopMatrix();
	
	glutSwapBuffers();
}

void Game::reshape(int w, int h)
{
	screen.width = w;
	screen.height = h;
	glViewport(0, 0, w, h);
}

Game::Game(int argc, char* argv[])
{
	init(argc, argv);
}

Game::~Game()
{
}

// Just so it doesnt make main ugly
void joshuaTestCode()
{
	ComputerVisionComponent cv = ComputerVisionComponent(BUILT_IN_CAM);
	cv::Mat image,image2;

	std::string filename = "D:\\school\\jaar 2\\periode 4\\Poftaak\\BoardChampions\\Engine\\EngineProject\\Camera Roll\\WIN_20170619_21_44_43_Pro.jpg";

	image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file


	if (!image.data)                              // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return;
	}

	cv.imgTogrey(image);

	std::vector<Card *> cards; 
	//cv.countAllCardsDebug(cv.cap, image, RED_ID, cards); // FOR READING BOARD

//	std::cout << cards.size() << std::endl;
	cv.countAllCards(cv.cap, RED_ID, cards);


	cv::waitKey(0);
}

int main(int argc, char* argv[])
{
	//Game* game1 = new Game(argc, argv);
	
	//joshuaTestCode();
	Game* game1 = new Game(argc, argv);



	return 0;
}