#pragma once
#include "DrawComponent.h"
#include "BruteCard.h"
#include <vector>
#include "Vertices.h"
#include "Card.h"

#define redColor 0
#define greenColor 1
#define yellowColor 2


class FieldComponent : public DrawComponent
{
private:
	

public:
	float red = 1.0f;
	float green = 0.0f;

	float x, y, z, width, height, middleX, middleY;
	bool filled;

	std::vector<LineVertex> linesVex;
	std::vector<LineVertex> filledVex;
	Card * card;

	void init() override;
	void draw() override;
	void drawLines();
	void drawQuads();
	void fill(bool filled);
	void setGroundColor(int color);
	bool onfield(int x, int y);
	FieldComponent(float x, float y, float z, float width, float height, Card * card);
	~FieldComponent();
};

