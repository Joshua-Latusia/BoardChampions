#pragma once

#include "Component.h"
#include "PlayerComponent.h"
#include "Listener.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include "Card.h"	

//
//
// Intents Technologies, Joshua Latusia, 2017-05-15

// Global defines

// COLOR defines

#define RED_ID 1
#define RED_TRESHOLD_LOW 75
#define RED_TRESHOLD_HIGH 160

#define BLACK_ID 2
#define BLACK_TRESHOLD_LOW 10
#define BLACK_TRESHOLD_HIGH 72


#define ALL_COLORS_ID 3
#define CARDS_TRESHOLD_LOW 10
#define CARDS_TRESHOLD_HIGH 165

// CAMERA DEFINES

#define BUILT_IN_CAM 0
#define EXTERNAL_CAM 1

#define CAMERA_WIDTH 1920
#define CAMERA_HEIGHT 1080

// CARD_TYPE defines

#define SQUARE_MAX_AREA 3500
#define SQUARE_MIN_AREA 2250

#define ROUND_MAX_AREA 2150
#define ROUND_MIN_AREA 1250

#define STAR_MAX_AREA 1100
#define STAR_MIN_AREA 500

#define HEART_MAX_AREA -1
#define HEART_MIN_AREA -1

#define ARROW_MAX_AREA  -1
#define ARROW_MIN_AREA  -1

#define MINIMAL_BLOB_SIZE 350

// CV defines

#define HORIZONTAL_FIELDS 10
#define VERTICAL_FIELDS 8

#define ROI_X	500
#define ROI_Y	150

#define ROI_WIDTH  810
#define ROI_HEIGHT	530

#define LEFT_TOP_CARD_X 78
#define LEFT_TOP_CARD_Y 30

#define CARD_DISTANCE_X 67
#define CARD_DISTANCE_Y 67

#define CARD_RADIUS_MARGIN 37				// error margin of card in pix





class ComputerVisionComponent : public Component, public Listener
{
private:

public:
	cv::VideoCapture cap;

	void imgTogrey(cv::Mat &img);

	// Debugging
	void captureGreyImgDebug(cv::VideoCapture cap);
	void imgTresholdBetweenDebug(int upperval, int lowerval, cv::Mat &img);

	void initCamera(cv::VideoCapture cap);

	void captureGreyImg(cv::VideoCapture cap, cv::Mat &greyImg);

	// TODO Choose which detect chars and count all cards next time.
	void detectField(const cv::Point2d* centerVec, int & x, int & y);
	void detectCharacters(const std::vector<cv::Point2d*> centerVec, const std::vector<int> areaVec, const int colorId,std::vector<Card *> &cards);

	void imgTresholdBetween(int upperval, int lowerval, cv::Mat &img);
	void imgTresholdBetween(int upperval, int lowerval, cv::Mat originalimg, cv::Mat &tresholdimg);

	void setTresholdBoundries(const int colorID, int & uppertreshold, int & lowertreshold);

	void countAllCardsDebug(cv::VideoCapture cap, cv::Mat greyImg, const int colorID, std::vector<Card *>& cards);



	void countAllCards(cv::VideoCapture cap, const int colorID, std::vector<Card *>& cards);

	void init() override;
	void update(float dt) override;
	ComputerVisionComponent(int cameraID);
	~ComputerVisionComponent();

};