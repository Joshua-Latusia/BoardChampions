//
//
// Intents Technologies, Joshua Latusia, 2017-05-15

#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include "Blobdetectionavans.h"
#include "ComputerVisionComponent.h"
#include "Game.h"
#include "GameObject.h"
#include "GL\freeglut.h"
#include "PlayerComponent.h"
#include "PlayingFieldComponent.h"
#include "MagicCard.h"
#include "MeleeCard.h"
#include "BruteCard.h"


// Converts a given img to a greyImg.
void ComputerVisionComponent::imgTogrey(cv::Mat & img)
{
	cv::cvtColor(img, img, CV_BGR2GRAY);
}

// Tresholds an img between two values and doesn't overwrite the original image
// Vals between the treshold are marked 1, rest is 0
void ComputerVisionComponent::imgTresholdBetween(int upperval, int lowerval, cv::Mat originalimg, cv::Mat & tresholdimg)
{
	if (upperval < lowerval)
	{
		int temp = upperval;
		upperval = lowerval;
		lowerval = temp;
	}
	cv::inRange(originalimg, cv::Scalar(lowerval), cv::Scalar(upperval), originalimg);
	cv::threshold(originalimg, tresholdimg, 250, 1, CV_THRESH_BINARY);

}


// Tresholds an img between two values but overwrites the original image
// Vals between the treshold are marked 1, rest is 0
void ComputerVisionComponent::imgTresholdBetween(int upperval, int lowerval, cv::Mat & img)
{
	if (upperval < lowerval)
	{
		int temp = upperval;
		upperval = lowerval;
		lowerval = temp;
	}
	cv::inRange(img, cv::Scalar(lowerval), cv::Scalar(upperval), img);
	cv::threshold(img, img, 250, 1, CV_THRESH_BINARY);
}

// Tresholds an img between two values, overwrites the original
// Valls in the treshold are marked 170 so they appear visible
void ComputerVisionComponent::imgTresholdBetweenDebug(int upperval, int lowerval, cv::Mat & img)
{
	cv::inRange(img, cv::Scalar(lowerval), cv::Scalar(upperval), img);
	cv::threshold(img, img, 250, 170, CV_THRESH_BINARY);
}

void ComputerVisionComponent::initCamera(cv::VideoCapture cap)
{
	if (cap.isOpened())
	{
		
		cap.set(CV_CAP_PROP_FRAME_WIDTH,CAMERA_WIDTH);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT,CAMERA_HEIGHT);

		//DEBUG to show if camera is working properly
		//namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);		
	}
	else
		std::cout << "Cannot open the video cam" << std::endl;
}

// A VideoCapture needs to be initialized
// Screencapture with a given camera and convert this automaticly to a grey img
void ComputerVisionComponent::captureGreyImg(cv::VideoCapture cap, cv::Mat & greyImg)
{
	// Read a new frame
	bool bSuccess = cap.read(greyImg);

	// Check if frame is correct
	if (bSuccess)
	{
		imgTogrey(greyImg);
	}
	else
		std::cout << "Cannot read a frame from video stream" << std::endl;
}

// A VideoCapture needs to be initialized
// Screencapture with a given camera and convert this automaticly to a grey img, shows this without saving the img anywhere (for debugging)
void ComputerVisionComponent::captureGreyImgDebug(cv::VideoCapture cap)
{
	cv::Mat greyImg;
	// Read a new frame
	bool bSuccess = cap.read(greyImg);

	// Check if frame is correct
	if (bSuccess)
	{
		imgTogrey(greyImg);
		imshow("Debug grey capture", greyImg);
		cv::waitKey(0);

	}
	else
		std::cout << "Cannot read a frame from video stream" << std::endl;
}

// Determines the field coordinates for a card/
// centerVec = center of a card,	&x and &y are the field coordinates
void ComputerVisionComponent::detectField(const cv::Point2d* centerVec, int &x, int &y)
{
	x = LEFT_TOP_CARD_X;
	y = LEFT_TOP_CARD_Y;

	int bugfix_X1 = 0;
	int bugfix_X2 = 0;
	int bugfix_X3 = 0;


	for (int i = 0; i <= HORIZONTAL_FIELDS; i++)
	{
		for (int j = 0; j <= VERTICAL_FIELDS; j++)
		{
			// Looking for the X
			if (i == 0)
			{
				bugfix_X1 = LEFT_TOP_CARD_X;
			}
			else
				bugfix_X1 = 0;

			if(i == HORIZONTAL_FIELDS)
			{
				bugfix_X2 = ROI_WIDTH - i * CARD_DISTANCE_X;
			}
			else
				bugfix_X2 = 0;
			
			if (j == VERTICAL_FIELDS)
			{
				bugfix_X3 = ROI_HEIGHT - j * CARD_DISTANCE_Y;
			}
			else
				bugfix_X3 = 0;


			if (centerVec->y >= x + (i * CARD_DISTANCE_X) - CARD_RADIUS_MARGIN - bugfix_X1 - bugfix_X2  && centerVec->y <= x + (i *  CARD_DISTANCE_X) + CARD_RADIUS_MARGIN + bugfix_X2)
			{
				// X and Y are probably inverted from Jans Code
				// Looking for the y
				if (centerVec->x >= y + (j * CARD_DISTANCE_Y) - CARD_RADIUS_MARGIN - bugfix_X3 && centerVec->x <= y + (j *  CARD_DISTANCE_Y) + CARD_RADIUS_MARGIN + bugfix_X3)
				{
					
					//if (j > 3) // first 4
					//{
						if (j == 0)
							x = 7;
						else if (j == 1)
							x = 6;
						else if (j == 2)
							x = 5;
						else if (j == 3)
							x = 4;
						else if (j == 4)
							x = 3;
						else if (j == 5)
							x = 2;
						else if (j == 6)
							x = 1;
						else if (j == 7)
							x = 0;

					y = i;
						
					// Ugly fix but it works, for some reason it returns an x which is 1 too high after i is greater or equal to 4
					if (y>= 6)
						y--;
					
					//x = j;
					
					std::cout << "X: " << x << "  Y: " << y << std::endl;
					return;
				}
			}
		}
	}
}



// Detection of characters  by area (here you can instert extra functionality what happens with each card.
// ONLY WORKS WITH RED_ID and BLACK_ID
void ComputerVisionComponent::detectCharacters(const std::vector<cv::Point2d*> centerVec, const std::vector<int> areaVec,const int colorId, std::vector<Card *> &cards)
{
	int u = 0;
	if (colorId == RED_ID)
		u = 6;

	int id = 0;

	// Determines what happens with each type of card
	// TODO put right unit with right type of card
	for (int i = 0; i < centerVec.size(); i++)
	{
		int x = 0, y = 0;
		if (areaVec[i] > STAR_MIN_AREA && areaVec[i] < STAR_MAX_AREA)
		{
			// Converts the center of the card vec to tile coords
			detectField(centerVec[i],x,y);
			cards.push_back(new MagicCard(id + u, x, y));
			id++;
			// Magic card
		}
		if (areaVec[i] > ROUND_MIN_AREA && areaVec[i] < ROUND_MAX_AREA)
		{
			detectField(centerVec[i], x, y);
			cards.push_back(new MeleeCard(id + u, x, y));
			id++;
			// Melee card
		}
		if (areaVec[i] > SQUARE_MIN_AREA && areaVec[i] < SQUARE_MAX_AREA)
		{
			detectField(centerVec[i], x, y);
			cards.push_back(new BruteCard(id+ u, x, y));
			id++;
			// Brute card
		}
	}
}

// Treshold boundries for character detection
void ComputerVisionComponent::setTresholdBoundries(const int colorID, int &uppertreshold, int &lowertreshold)
{
	if (colorID < RED_ID || colorID > ALL_COLORS_ID)
	{
		std::cout << colorID << ": is invalid in setTresholdBoundries" << std::endl;
		return;
	}
	if (colorID == RED_ID)
	{
		uppertreshold = RED_TRESHOLD_HIGH;
		lowertreshold = RED_TRESHOLD_LOW;
	}

	if (colorID == BLACK_ID)
	{
		uppertreshold = BLACK_TRESHOLD_HIGH;
		lowertreshold = BLACK_TRESHOLD_LOW;
	}

	if (colorID == ALL_COLORS_ID)
	{
		uppertreshold = CARDS_TRESHOLD_HIGH;
		lowertreshold = CARDS_TRESHOLD_LOW;
	}
}

// Makes a screencapture (Grey) and counts the amount of cards using the black outline of the cards
// TODO define certain parameter values when setup is final
// TODO Delete the MAT parameter and uncomment the caputre camera code
// USE THIS METHOD WHEN YOU DON"T HAVE A CAMERA AN PASS IN A PICTURE.
void ComputerVisionComponent::countAllCardsDebug(cv::VideoCapture cap, cv::Mat greyImg, const int colorID, std::vector<Card *> &cards)
{
	int uppertresholdval = 0;
	int lowertresholdval = 0;

	setTresholdBoundries(colorID, uppertresholdval, lowertresholdval);
	cv::Mat copy = greyImg.clone();

	// Cuts out the Region Of Intrest (the board);
	greyImg = greyImg(cv::Rect(ROI_X,ROI_Y,ROI_WIDTH,ROI_HEIGHT));
	//imshow("Roi Img", greyImg);

	// Tresholding and morphology to get needed colors
	imgTresholdBetween(uppertresholdval, lowertresholdval, greyImg);


	erode(greyImg, greyImg, cv::Mat(), cv::Point(-1, -1), 1, 1, 1);
	dilate(greyImg, greyImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
	//imshow("Dilation & Erosion", greyImg);
	

	//// converten to Mat obj with greater depth 16-bit signed
	cv::Mat binary16S;
	greyImg.convertTo(binary16S, CV_16S);


	// Variables to save blob info 
	cv::Mat labeledImage3;
	std::vector<cv::Point2d *> firstpixelVec3;
	std::vector<cv::Point2d *> posVec3;
	std::vector<int> areaVec3;
	labelBLOBsInfo(binary16S, labeledImage3,
		firstpixelVec3, posVec3, areaVec3, STAR_MIN_AREA, 30000);

	int meleeUnits = 0, bruteUnits = 0, magicUnits = 0;

	// Determines the shape and thus the character of each card
	detectCharacters(posVec3, areaVec3, colorID, cards); 
	

	std::cout << "Melee Cnt: " << meleeUnits << "  Brute Cnt: " << bruteUnits << "  Magic Cnt: " << magicUnits << std::endl;

	//DEBUG print data to console 
	std::cout << "Aantal gevonden BLOBs = " << firstpixelVec3.size() << std::endl;
	for (int i = 0; i < firstpixelVec3.size(); i++)
	{
		std::cout << "BLOB " << i + 1 << std::endl;
		std::cout << "firstpixel = (" << firstpixelVec3[i]->x << "," << firstpixelVec3[i]->y << ")" << std::endl;
		std::cout << "centre = (" << posVec3[i]->x << "," << posVec3[i]->y << ")" << std::endl;
		std::cout << "area = " << areaVec3[i] << std::endl;
	}

	if (colorID == RED_ID)
		countAllCardsDebug(cap, copy, BLACK_ID, cards);
}


// Function to detect the cards on the board.
// Cap = a camera, cards = cardcount, colorID = card color you want to count RED_ID, BLACK_ID ALL_CARDS_ID
// How it works,	1. Takes a picture with the camera		2. Cut out the board from the rest and resizes it
//					3. Threshold + bi-morphology			4. Count blobs and detect different type of cards.
// USE THIS ONE IF YOU DO HAVE A CAMERA
void ComputerVisionComponent::countAllCards(cv::VideoCapture cap, const int colorID, std::vector<Card *> &cards)
{
	int uppertresholdval = 0;
	int lowertresholdval = 0;

	setTresholdBoundries(colorID, uppertresholdval, lowertresholdval);

	// Captures img of board and convert to grey img
	cv::Mat greyImg;

	// Read a new frame
	bool bSuccess = cap.read(greyImg);

	if (!bSuccess)
	{
		std::cout << "Cannot capture img in  countAllCards(); " << std::endl;
		return;
	}
	captureGreyImg(cap, greyImg);
	//imshow("Cap", greyImg);
	

	// Cuts out the Region Of Intrest (the board);
	greyImg = greyImg(cv::Rect(ROI_X, ROI_Y, ROI_WIDTH, ROI_HEIGHT));
	//imshow("Roi Img", greyImg);


	// Tresholding and morphology to get needed colors, and remove noise
	imgTresholdBetween(uppertresholdval, lowertresholdval, greyImg);

	erode(greyImg, greyImg, cv::Mat(), cv::Point(-1, -1), 1, 1, 1);
	dilate(greyImg, greyImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);

	//// converten to Mat obj with greater depth 16-bit signed
	cv::Mat binary16S;
	greyImg.convertTo(binary16S, CV_16S);

	// Variables to save blob info and unit counts
	cv::Mat labeledImage3;
	std::vector<cv::Point2d *> firstpixelVec3;
	std::vector<cv::Point2d *> posVec3;
	std::vector<int> areaVec3;

	labelBLOBsInfo(binary16S, labeledImage3,
		firstpixelVec3, posVec3, areaVec3, MINIMAL_BLOB_SIZE, 30000);

	int meleeUnits, bruteUnits, magicUnits, castle;

	// Determines the shape and thus the character of each card
	detectCharacters(posVec3, areaVec3, colorID, cards);


	//DEBUG print data to console 
	std::cout << "Aantal gevonden BLOBs = " << firstpixelVec3.size() << std::endl;
	for (int i = 0; i < firstpixelVec3.size(); i++)
	{
		std::cout << "BLOB " << i + 1 << std::endl;
		std::cout << "firstpixel = (" << firstpixelVec3[i]->x << "," << firstpixelVec3[i]->y << ")" << std::endl;
		std::cout << "centre = (" << posVec3[i]->x << "," << posVec3[i]->y << ")" << std::endl;
		std::cout << "area = " << areaVec3[i] << std::endl << std::endl;
	}

	if (colorID == RED_ID)
		countAllCards(cap, BLACK_ID, cards);

}



void ComputerVisionComponent::init()
{

}

void ComputerVisionComponent::update(float dt)
{

	//captureGreyImgDebug(cap);
}

// Camera id is BUILT_IN_CAM or EXTERNAL_CAM
// Sets the settings for the camera right.
ComputerVisionComponent::ComputerVisionComponent(int cameraID)
{
	if (cameraID == BUILT_IN_CAM || cameraID == EXTERNAL_CAM)
	{
		cap = cv::VideoCapture(cameraID);
		initCamera(cap);
	}
	else
	{
		cv::VideoCapture cap(BUILT_IN_CAM);
		std::cout << "Invalid Camera ID : " << cameraID << "ID is set to default 0." << std::endl;
	}
}

ComputerVisionComponent::~ComputerVisionComponent()
{
}