#include "GameLogicSystem.h"
#include "ModelComponent.h"
#include "PlayingFieldComponent.h"
#include "MoveComponent.h"
#include "KeyboardMovementComponent.h"
#include "Game.h"
#include "CameraMovementComponent.h"
#include "FieldComponent.h"
#include "PlayerComponent.h"
#include "InputComponent.h"
#include "StatusComponent.h"
#include "ComputerVisionComponent.h"
#include "SoundPlayerComponent.h"

GameLogicSystem::GameState GameLogicSystem::gameState;


int activePlayerID = 0;

int mouseClicked = 1;

int posI = 0;
int posJ = 0;

bool pic1 = true;
ComputerVisionComponent vision = ComputerVisionComponent(BUILT_IN_CAM);

std::vector<LogicGameObject *> statusBars;
std::vector<LogicGameObject *> players;

std::vector<Card *> cards;




void GameLogicSystem::init()
{
	/*Start game turn loop*/
	gameState = GameState::GAMELOAD;

	/*Adds all the objects to the inputsystem*/
	systemInit();

	/*Calls init function of every object*/
	objectInit();


}

void GameLogicSystem::systemInit()
{
	Game::inputEvents.attachListener(this);
	///*Add objects*/
	map = new LogicGameObject();
	PlayingFieldComponent* f = new PlayingFieldComponent("texture.png", "Heightmap4.png");
	map->addComponent(f);
	objects.push_back(map);

	for (int i = 0; i < 12; i++)
	{
		LogicGameObject* player = new LogicGameObject();
		players.push_back(player);

		LogicGameObject* statusbar = new LogicGameObject();
		statusBars.push_back(player);
	}
}

void GameLogicSystem::objectInit()
{
	for (LogicGameObject* gObj : objects)
	{
		gObj->init();
	}
}


void CheckMovement(std::string kkfilename)
{
	std::vector<Card *> cards2;
	
	std::string filename = kkfilename;

	cv::Mat image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file


	if (!image.data)                              // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return;
	}

	vision.imgTogrey(image);

	vision.countAllCardsDebug(vision.cap, image, RED_ID, cards2);
	int cards1_x, cards1_y, cards2_x, cards2_y;


	// check card 1 difference
	for(int i = cards2.size()-1; i >= 0; i--)
	{	
		bool hasMatch = false;
		for (int x = cards.size()-1; x >= 0; x--)
		{
			if (cards[i]->x == cards2[x]->x && cards[i]->y == cards2[x]->y)
			{
				hasMatch = true;
			}
			
		}
		if (!hasMatch)
		{
			cards1_x = cards[i]->x;
			cards1_y = cards[i]->y;
			// eventueel ID opslaan??
			break;
			// moet uit loop breaken

		}
		
	}

	// check card 2 difference
	for (int i = cards.size()-1; i >= 0; i--)
	{
		bool hasMatch = false;
		for (int x = cards2.size()-1; x >= 0; x--)
		{
			if (cards2[i]->x == cards[x]->x && cards2[i]->y == cards[x]->y)
			{
				hasMatch = true;
			}
			
		}
		if (!hasMatch)
		{
			cards2_x = cards2[i]->x;
			cards2_y = cards2[i]->y;
			break;
			// moet uit loop breaken

		}

	}






	// Code cas
	/*if (cards[i]->x != cards2[i]->x || cards[i]->y != cards2[i]->y)
	{*/
		std::cout << cards1_x << " --- " << cards1_y << " ------ " << cards2_x << " --- " << cards2_y << std::endl;
		int playerID = PlayingFieldComponent::fields[cards1_x][cards1_y]->card->playerID;
		LogicGameObject* player = players[playerID];
		player->getComponent<MoveComponent*>("maffe")->setTarget(cards2_x, cards2_y);
		statusBars[playerID]->getComponent<MoveComponent *>("test")->setTarget(cards2_x, cards2_y);
		PlayingFieldComponent::fields[cards2_x][cards2_y]->card = PlayingFieldComponent::fields[cards1_x][cards1_y]->card;
		PlayingFieldComponent::fields[cards1_x][cards1_y]->card = nullptr;
		cards = cards2;
		
	//}
}

void GameLogicSystem::update(float dt)
{
	//gameTime = glutGet(GLUT_ELAPSED_TIME);

	switch (gameState)
	{
		//read all the cards for the first time

	case GameState::GAMEINIT:
	{


		std::string filename = "D:\\school\\jaar 2\\periode 4\\Poftaak\\BoardChampions\\Engine\\EngineProject\\Camera Roll\\WIN_20170619_16_10_26_Pro.jpg";

		cv::Mat image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file


		if (!image.data)                              // Check for invalid input
		{
			std::cout << "Could not open or find the image" << std::endl;
			return;
		}

		vision.imgTogrey(image);

	

		vision.countAllCardsDebug(vision.cap, image, RED_ID, cards);

		//vision.countAllCards(vision.cap, RED_ID, cards);
		if (cards.size() != 12)
			return;

		for(auto card : cards)
		{
			PlayingFieldComponent::fields[card->x][card->y]->card = card;
		}

		for (int j = 0; j < 10; j++) //This loops on the columns
		{
			for (int i = 0; i < 8; i++)    //This loops on the rows.
			{
				if (PlayingFieldComponent::fields[i][j]->card != nullptr)
				{
					LogicGameObject* player = new LogicGameObject();

					player->addComponent(ModelManager::models[PlayingFieldComponent::fields[i][j]->card->modelID]);

					if (PlayingFieldComponent::fields[i][j]->card->modelID == MELEECARD) {
						player->scale = Vec3fl(0.1f, 0.1f, 0.1f);
					}
					else if (PlayingFieldComponent::fields[i][j]->card->modelID == BRUTECARD)
					{
						player->scale = Vec3fl(0.15f, 0.15f, 0.15f);
					}
					else if (PlayingFieldComponent::fields[i][j]->card->modelID == MAGICCARD)
					{
						player->scale = Vec3fl(0.15f, 0.15f, 0.15f);
					}

					FieldComponent* f = PlayingFieldComponent::fields[i][j];
					player->position.x = f->middleX;
					player->position.z = f->middleY;
					player->position.y = 7;


					MoveComponent* mov2 = new MoveComponent(15);
					player->addComponent(mov2);

					players[PlayingFieldComponent::fields[i][j]->card->playerID] = player;
					objects.push_back(player);

					//statusBar
					//-----------------------------------------------------------------------
					LogicGameObject* statusBar = new LogicGameObject();
					statusBar->position.x = f->middleX;
					statusBar->position.z = f->middleY;
					statusBar->position.y = 40;

					StatusComponent * status = new StatusComponent();
					status->statusPoints = PlayingFieldComponent::fields[i][j]->card->healthValue;
					statusBar->addComponent(status);


					MoveComponent* mov3 = new MoveComponent(15);
					statusBar->addComponent(mov3);

					statusBars[PlayingFieldComponent::fields[i][j]->card->playerID] = statusBar;
					objects.push_back(statusBar);
				}
			}
		}




		gameState = PLAYER1SETUP;
		
	}
			break;
		/*Setup cards for player1*/
	case GameState::PLAYER1SETUP:
	{
		for (int i = 0; i < 8; i++)    //This loops on the rows.
		{
			for (int j = 0; j < 10; j++) //This loops on the columns
			{
				if (PlayingFieldComponent::fields[i][j]->card != nullptr && PlayingFieldComponent::fields[i][j]->card->playerID == activePlayerID)
				{
					std::cout << i << " + " << j << std::endl;
					posI = i;
					posJ = j;
					PlayingFieldComponent::fillFieldColor(PlayingFieldComponent::fields[i][j]->card->modelID, posI, posJ);

					gameState = PLAYER1STARTTURN;
					std::cout << activePlayerID << "active player1d" << std::endl;

				}
			}
		}

	}
	break;

	case GameState::PLAYER1STARTTURN:
	{
		if (mouseClicked == 0)
		{
			if(pic1)
				CheckMovement("D:\\school\\jaar 2\\periode 4\\Poftaak\\BoardChampions\\Engine\\EngineProject\\Camera Roll\\WIN_20170619_16_10_30_Pro.jpg");
			else
				CheckMovement("D:\\school\\jaar 2\\periode 4\\Poftaak\\BoardChampions\\Engine\\EngineProject\\Camera Roll\\WIN_20170619_16_10_26_Pro.jpg");
			//int x = 0;
			//int y = 8;
			////players[activePlayerID]->getComponent<MoveComponent *>("test")->setTarget(x, y);
			////statusBars[activePlayerID]->getComponent<MoveComponent *>("test")->setTarget(x, y);
			//PlayingFieldComponent::fields[x][y]->card = PlayingFieldComponent::fields[posI][posJ]->card;

			//SoundPlayerComponent::soundDevice->play2D("media/walking.wav", true, false);


			PlayingFieldComponent::clearFieldColor();
			pic1 = !pic1;
			//PlayingFieldComponent::fields[x][y]->card = players[activePlayerID].
			//	PlayingFieldComponent::fields[i][j]->card->modelID

			mouseClicked = 1;
			//gameState = PLAYER1MOVEUNIT;
		}
		else
		{
			//CheckMovement("D:\\school\\jaar 2\\periode 4\\Poftaak\\BoardChampions\\Engine\\EngineProject\\Camera Roll\\WIN_20170619_16_10_26_Pro.jpg");
		}
	}
		break;
	case GameState::PLAYER1MOVEUNIT:
		if (players[activePlayerID]->getComponent<MoveComponent *>("test")->done)
		{
			SoundPlayerComponent::soundDevice->removeSoundSource("media/walking.wav");
			std::cout << "klaar met bewegen";
			for (int i = 0; i < 8; i++)    //This loops on the rows.
			{
				for (int j = 0; j < 10; j++) //This loops on the columns
				{
					if (PlayingFieldComponent::fields[i][j]->card != nullptr && PlayingFieldComponent::fields[i][j]->card->playerID == activePlayerID)
						PlayingFieldComponent::fillFieldColor(PlayingFieldComponent::fields[i][j]->card->modelID, i, j);
				}
			}

			gameState = PLAYER1UNITCOMBAT;

		

		}
		break;
	case GameState::PLAYER1UNITCOMBAT:
	


		SoundPlayerComponent::soundDevice->play2D("media/explosion.wav");

				for (int i = 0; i < 8; i++)    //This loops on the rows.
				{
					for (int j = 0; j < 10; j++) //This loops on the columns
					{
						if (PlayingFieldComponent::fields[i][j]->card != nullptr && PlayingFieldComponent::fields[i][j]->card->playerID == activePlayerID)
						{
							
						}

					}
				}


		gameState = PLAYER1ENDTURN;

		break;
	case GameState::PLAYER1ENDTURN:

		/*
		setStatusBars();
		if (activePlayerID > 14)
		activePlayerID = 0;
		else
		activePlayerID++;

		gameState = PLAYER1SETUP;*/
		break;
	case GameState::GAMELOAD:
		break;
	case GameState::PLAYER2STARTTURN:

		break;
	case GameState::PLAYER2MOVEUNIT:

		break;
	case GameState::PLAYER2UNITCOMBAT:

		break;
	case GameState::PLAYER2ENDTURN:

		break;
	}

	for (LogicGameObject* gObj : objects)
	{
		gObj->update(dt);
	}
}

void GameLogicSystem::draw()
{
	for (LogicGameObject* gObj : objects)
	{
		gObj->draw();
	}

	//std::string timeToDraw = "Game Time: " + std::to_string(gameTime);
	//char *timeCstr = &timeToDraw[0u];
	//UISystem::drawString(timeCstr, 60);

	////Draw player position on screen
	//std::string stringToDraw = "Player X: " + std::to_string(Game::camera.posX) + ", Y: " + std::to_string(Game::camera.posY) + ", Z: " + std::to_string(Game::camera.posZ);
	//char *cstr = &stringToDraw[0u];
	//UISystem::drawString(cstr, 20);

	//std::string stringToDraw2 =  "X: " + std::to_string(Game::camera.rotX) + "Player Rotation Y: " + std::to_string(Game::camera.rotY) + ", Z: " + std::to_string(Game::camera.rotZ);
	//char *cstr2 = &stringToDraw2[0u];
	//UISystem::drawString(cstr2, 40);
}

void GameLogicSystem::setStatusBars()
{
	//if (activePlayerID == 8 || activePlayerID == 0) {
	//	for(auto status : statusBars)
	//		status->getComponent<StatusComponent *>("h")->isRed = !status->getComponent<StatusComponent *>("h")->isRed;
	//}

	for (int i = 0; i < 8; i++)    //This loops on the rows.
	{
		for (int j = 0; j < 10; j ++) //This loops on the columns
		{
			if (PlayingFieldComponent::fields[i][j]->card != nullptr)
			{
				//if(statusBars[PlayingFieldComponent::fields[i][j]->card->playerID]->getComponent<StatusComponent *>("h")->isRed)
				//std::cout << PlayingFieldComponent::fields[i][j]->card->playerID << std::endl;
				auto comp = statusBars[PlayingFieldComponent::fields[i][j]->card->playerID];
				if (comp->getComponent<StatusComponent *>("h") != nullptr)
				{
					comp->getComponent<StatusComponent *>("h")->statusPoints = PlayingFieldComponent::fields[i][j]->card->healthValue;
				}
			}
		}
	}



}

void GameLogicSystem::listenMapLoaded()
{
	ModelManager();

	SoundPlayerComponent();



	
		KeyboardMovementComponent* movementComp = new KeyboardMovementComponent();
		Game::inputEvents.attachListener(movementComp);


		LogicGameObject* cameraController = new LogicGameObject();
		CameraMovementComponent* cameraMovement = new CameraMovementComponent(10.0f);
		Game::inputEvents.attachListener(cameraMovement);
		cameraController->addComponent(cameraMovement);
		objects.push_back(cameraController);

		gameState = GAMEINIT;
}



GameLogicSystem::GameLogicSystem()
{
}

GameLogicSystem::~GameLogicSystem()
{
}