#include "FieldComponent.h"
#include "PlayingFieldComponent.h"
#include <GL/freeglut.h>
#include <cmath>

void FieldComponent::init()
{
	linesVex.push_back(LineVertex{ x, z,y });
	linesVex.push_back(LineVertex{ x + width,z , y });
	linesVex.push_back(LineVertex{ x, z,y });
	linesVex.push_back(LineVertex{ x, z, y + height });
	linesVex.push_back(LineVertex{ x + width,z,y });
	linesVex.push_back(LineVertex{ x + width, z, y + height });
	linesVex.push_back(LineVertex{ x,z,y + height });
	linesVex.push_back(LineVertex{ x + width,z,y + height });

	filledVex.push_back(LineVertex{ x,z,y });
	filledVex.push_back(LineVertex{ x + width, z,y});
	filledVex.push_back(LineVertex{ x, z,y + height });
	filledVex.push_back(LineVertex{ x, z, y + height});
	filledVex.push_back(LineVertex{ x + width, z,y + height });
	filledVex.push_back(LineVertex{ x + width, z,y });
}

void FieldComponent::drawLines()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(LineVertex), ((float*)linesVex.data()) + 0);
	glDrawArrays(GL_LINES, 0, linesVex.size());
	glDisableClientState(GL_VERTEX_ARRAY);
}
void FieldComponent::drawQuads()
{
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(red, green, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(LineVertex), ((float*)filledVex.data()) + 0);
	glDrawArrays(GL_TRIANGLES, 0, linesVex.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	glColor3f(1, 1, 1);
}

void FieldComponent::fill(bool filled)
{
	this->filled = filled;;
}

void FieldComponent::setGroundColor(int color)
{
	if(color == greenColor)
	{
		red = 0.0f;
		green = 1.0f;
	}else if(color == redColor)
	{
		red = 1.0f;
		green = 0.0f;
	}else if(color == yellowColor)
	{
		red = 1.0f;
		green = 1.0f;
	}
}

bool FieldComponent::onfield(int x, int y)
{
	if (x >= this->x && x <=(this->x + width) && y >= this->y && y <= (this->y + height))
	{
		return true;
	}

	return false;
}





void FieldComponent::draw()
{
	if (filled)
		drawQuads();

	drawLines();
}

FieldComponent::FieldComponent(float x, float y, float z, float width, float height, Card * card): x(x),y(y),z(z),width(width),height(height), card(card)
{
	init();
	middleX = x + width / 2;
	middleY = y + height / 2;
	filled = false;
}


FieldComponent::~FieldComponent(){}
