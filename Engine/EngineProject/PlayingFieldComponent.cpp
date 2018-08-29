#include "PlayingFieldComponent.h"
#include <GL/freeglut.h>
#include "stb_image.h"
#include "Game.h"
#include "Card.h"
#include "MagicCard.h"
#include "MeleeCard.h"


FieldComponent* PlayingFieldComponent::fields[8][10];

PlayingFieldComponent::PlayingFieldComponent(char * texPath, char * heightPath) : DrawComponent(texPath)
{
	this->heightPath = heightPath;
	done = false;
}

void PlayingFieldComponent::init()
{
	int imgWidth, imgHeight, imgBpp;
	unsigned char* imgData = stbi_load(heightPath, &imgWidth, &imgHeight, &imgBpp, 4);

	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			ImgArray[x][y] = (int)(imgData[4 * (x + y * 256)] / 5);
		}
	}

	fillArrays();
}


void PlayingFieldComponent::drawHeightMap()
{
	if (wireframeMode)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glShadeModel(GL_SMOOTH);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, sizeof(TexVertex), ((float*)heightmapVex.data() + 6));
	glNormalPointer(GL_FLOAT, sizeof(TexVertex), ((float*)heightmapVex.data()) + 3);
	glVertexPointer(3, GL_FLOAT, sizeof(TexVertex), ((float*)heightmapVex.data()) + 0);
	glDrawArrays(GL_TRIANGLES, 0, heightmapVex.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

};

Vec3fl PlayingFieldComponent::calculateNormal(Vec3fl* v1, Vec3fl* v2, Vec3fl* v3)
{
	Vec3fl vu, vv, vr;
	float val;
	vu.x = v2->x - v1->x;
	vu.y = v2->y - v1->y;
	vu.z = v2->z - v1->z;

	vv.x = v3->x - v1->x;
	vv.y = v3->y - v1->y;
	vv.z = v3->z - v1->z;

	vr.x = (vu.y * vv.z) - (vv.y * vu.z);
	vr.y = (vv.x * vu.z) - (vu.x * vv.z);
	vr.z = (vu.x * vv.y) - (vv.x * vu.y);

	val = sqrtf((vr.x * vr.x) + (vr.y * vr.y) + (vr.z * vr.z));

	Vec3fl norm;
	norm.x = vr.x / val;
	norm.y = vr.y / val;
	norm.z = vr.z / val;

	//norm.x = (vu.x + vu.y + vu.z) / 3.0f;
	//norm.y = (vv.x + vv.y + vv.z) / 3.0f;
	//norm.z = (vr.x + vr.y + vr.z) / 3.0f;

	return norm;
}

Vec3fl PlayingFieldComponent::getInterpolatedValue(Vec3fl * v1, Vec3fl * v2, Vec3fl * v3, Vec3fl * v4, Vec3fl * v5)
{
	Vec3fl interpolated;
	interpolated.x = (v1->x + v2->x + v3->x + v4->x + v5->x) / 5.0f;
	interpolated.y = (v1->y + v2->y + v3->y + v4->y + v5->y) / 5.0f;
	interpolated.z = (v1->z + v2->z + v3->z + v4->z + v5->z) / 5.0f;
	return interpolated;
}

void PlayingFieldComponent::clearFieldColor()
{
	for (int i = 0; i < 8; i++)    //This loops on the rows.
	{
		for (int j = 0; j < 10; j++) //This loops on the columns
		{
			fields[i][j]->setGroundColor(false);
			fields[i][j]->fill(false);
		}
	}
}

//standaard ground color fill (top right bottom left 2x in length)
void PlayingFieldComponent::standardFillFieldColor(int posx, int posy)
{
	bool teamcolor = fields[posx][posy]->card->team;

	//std::cout << teamcolor << " + " << fields[posx + 1][posy]->card->team << std::endl;

	//links

		if (posx < 7) {
			fields[posx + 1][posy]->fill(true);
			if (fields[posx + 1][posy]->card != nullptr) {
				if (fields[posx + 1][posy]->card->team != teamcolor)
					fields[posx + 1][posy]->setGroundColor(greenColor);
				else
					fields[posx + 1][posy]->fill(false);

			}
				else if (posx < 6) {
						fields[posx + 2][posy]->fill(true);
						if (fields[posx + 2][posy]->card != nullptr)
							if (fields[posx + 2][posy]->card->team != teamcolor)
								fields[posx + 2][posy]->setGroundColor(greenColor);
							else
								fields[posx + 2][posy]->fill(false);
					}
		}


	//rechts

		if (posx > 0) {
			fields[posx - 1][posy]->fill(true);
			if (fields[posx - 1][posy]->card != nullptr) {
				if (fields[posx - 1][posy]->card->team != teamcolor)
					fields[posx - 1][posy]->setGroundColor(greenColor);
				else
					fields[posx - 1][posy]->fill(false);
			}
			else if (posx > 1) {
					fields[posx - 2][posy]->fill(true);
					if (fields[posx - 2][posy]->card != nullptr) {
						if (fields[posx - 2][posy]->card->team != teamcolor)
							fields[posx - 2][posy]->setGroundColor(greenColor);
						else
							fields[posx - 2][posy]->fill(false);
					}
				}
		}

	//voor

		if (posy < 9) {
			fields[posx][posy + 1]->fill(true);
			if (fields[posx][posy + 1]->card != nullptr) {
				if (fields[posx][posy + 1]->card->team != teamcolor)
					fields[posx][posy + 1]->setGroundColor(greenColor);
				else
					fields[posx][posy + 1]->fill(false);
			}
			else if (posy < 8) {
					fields[posx][posy + 2]->fill(true);
					if (fields[posx][posy + 2]->card != nullptr){
						if (fields[posx][posy + 2]->card->team != teamcolor)
							fields[posx][posy + 2]->setGroundColor(greenColor);
						else
							fields[posx][posy + 2]->fill(false);					
				}

			}
		}

	//achter

		if (posy > 0) {
			fields[posx][posy - 1]->fill(true);
			if (fields[posx][posy - 1]->card != nullptr)
			{
				if (fields[posx][posy - 1]->card->team != teamcolor)
					fields[posx][posy - 1]->setGroundColor(greenColor);
				else
					fields[posx][posy - 1]->fill(false);
			}
			else if (posy > 1)
					fields[posx][posy - 2]->fill(true);
			if (fields[posx][posy - 2]->card != nullptr) {
				if (fields[posx][posy - 2]->card->team != teamcolor)
					fields[posx][posy - 2]->setGroundColor(greenColor);
				else
					fields[posx][posy - 2]->fill(false);
			}
		}
}

//diagonal ground color fill (ridder special, 1x length)
void PlayingFieldComponent::ridderFillFieldColor(int posx, int posy)
{
	//links boven

		if (posx < 7 && posy < 9) {
			fields[posx + 1][posy + 1]->fill(true);
			if(fields[posx + 1][posy + 1]->card != nullptr)
				fields[posx + 1][posy + 1]->setGroundColor(greenColor);
		}

	//rechts boven

		if (posx > 0 &&  posy < 9) {
			fields[posx - 1][posy + 1]->fill(true);
			if(fields[posx - 1][posy + 1]->card != nullptr)
				fields[posx - 1][posy + 1]->setGroundColor(greenColor);
		}

	//rechts onder
		if (posx > 0 && posy > 0) {
			fields[posx - 1][posy - 1]->fill(true);
			if(fields[posx - 1][posy - 1]->card != nullptr)
				fields[posx - 1][posy - 1]->setGroundColor(greenColor);
		}

	//links onder
		if (posy > 0 && posx < 7) {
			fields[posx + 1][posy - 1]->fill(true);
			if(fields[posx + 1][posy - 1]->card != nullptr)
				fields[posx + 1][posy - 1]->setGroundColor(greenColor);
		}
}

void PlayingFieldComponent::magicFillFieldColor(int posx, int posy)
{
	ridderFillFieldColor(posx, posy);
	{
		//links boven
		if (isValid(posx + 2, posy + 2))
		{
			if (posx < 7 && isValid(posx, posy)) {
				fields[posx + 2][posy + 2]->fill(true);
				if(fields[posx + 2][posy + 2]->card != nullptr)
					fields[posx + 2][posy + 2]->setGroundColor(greenColor);
			}
		}

		//rechts boven
		if (isValid(posx - 2, posy + 2))
		{
			if (posx > 0) {
				fields[posx - 2][posy + 2]->fill(true);
				if(fields[posx - 2][posy + 2]->card != nullptr)
					fields[posx - 2][posy + 2]->setGroundColor(greenColor);
			}
		}

		//rechts onder
		if (isValid(posx - 2, posy - 2))
		{
			if (posx > 0 && isValid(posx, posy)) {
				fields[posx - 2][posy - 2]->fill(true);
				if(fields[posx - 2][posy - 2]->card != nullptr)
					fields[posx - 2][posy - 2]->setGroundColor(greenColor);

			}
		}

		//links onder
		if (isValid(posx + 2, posy - 2))
		{
			if (posx < 7 && isValid(posx, posy)) {
				fields[posx + 2][posy - 2]->fill(true);
				if(fields[posx + 2][posy - 2]->card != nullptr)
					fields[posx + 2][posy - 2]->setGroundColor(greenColor);
			}
		}
	}
}


bool PlayingFieldComponent::isValid(int xPos, int yPos)
{
	if (xPos >= 0 && xPos <= 7)
	{
		if (yPos >= 0 && yPos <= 9)
		{
			return true;
		}
	}
	return false;
}


void PlayingFieldComponent::fillFieldColor(int modelID, int posx, int posy)
{
	PlayingFieldComponent::clearFieldColor();

	if (posx < 0 || posx > 7 || posy < 0 || posy > 9)
		return;

	
	//top right left bottom 2x
	standardFillFieldColor(posx, posy);

	if(modelID == MELEECARD) //MELEECARD
	{
		ridderFillFieldColor(posx, posy);

	}
	else if (modelID == MAGICCARD)
	{
		magicFillFieldColor(posx, posy);
	}
	
	fields[posx][posy]->setGroundColor(yellowColor);
	fields[posx][posy]->fill(true);
		


}






PlayingFieldComponent::~PlayingFieldComponent()
{
}

void PlayingFieldComponent::draw()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->textureID);
	drawHeightMap();

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (fields[x][y] != nullptr)
			{
				fields[x][y]->draw();
			}
		}
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void PlayingFieldComponent::fillArrays()
{

	float xCoord = 0;
	float yCoord = 0;
	int fieldPosX = 0;
	int fieldPosY = 0;

	/*Fill normals first so we can interpolate*/
	for (int y = 0; y < 255; y++)
	{
		for (int x = 0; x < 255; x++)
		{
			Vec3fl* vec1 = new Vec3fl(x, y, ImgArray[x][y]);
			Vec3fl* vec2 = new Vec3fl(x + 1, y, ImgArray[x + 1][y]);
			Vec3fl* vec3 = new Vec3fl(x + 1, y + 1, ImgArray[x + 1][y + 1]);
			NormalArray[x][y] = calculateNormal(vec1, vec2, vec3);
		}
	}



	/*Interpolate normals*/
	for (int y = 1; y < 254; y++)
	{
		for (int x = 1; x < 254; x++)
		{
			Vec3fl* vecLeft = &NormalArray[x - 1][y];
			Vec3fl* vecUp = &NormalArray[x][y - 1];
			Vec3fl* vecRight = &NormalArray[x + 1][y];
			Vec3fl* vecDown = &NormalArray[x][y + 1];
			Vec3fl* vecCurrent = &NormalArray[x][y];
			NormalArray[x][y] = getInterpolatedValue(vecCurrent, vecDown, vecLeft, vecRight, vecUp);
		}
	}

	int counter = 0;

	for (int y = 0; y < 255; y++)
	{
		for (int x = 0; x < 255; x++)
		{
			if (ImgArray[x][y] <= 2)
			{
				xCoord = 0.75f;
				yCoord = 0.75f;
			}
			else if (ImgArray[x][y] > 2 && ImgArray[x][y] <= 4)
			{

				xCoord = 0.50f;
				yCoord = 0.50f;

			}
			else if (ImgArray[x][y] > 4 && ImgArray[x][y] <= 12)
			{
				xCoord = 0.25f;
				yCoord = 0.25f;
			}

			else if (ImgArray[x][y] > 12)
			{

				xCoord = 0;
				yCoord = 0;
			}

			//Right triangle
			float verX = x;
			float verY = y;
			float verZ = ImgArray[x][y];
			Vec3fl normal = NormalArray[(int)verX][(int)verY];

			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord, yCoord });

			verX = x + 1;
			verY = y;
			verZ = ImgArray[x + 1][y];
			normal = NormalArray[(int)verX][(int)verY];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord, yCoord + 0.25f });

			verX = x + 1;
			verY = y + 1;
			verZ = ImgArray[x + 1][y + 1];
			normal = NormalArray[(int)verX][(int)verY];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord + 0.25f, yCoord + 0.25f });

			//Left triangle
			verX = x;
			verY = y;
			verZ = ImgArray[x][y];
			normal = NormalArray[(int)verX][(int)verY];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord, yCoord });

			verX = x + 1;
			verY = y + 1;
			verZ = ImgArray[x + 1][y + 1];
			normal = NormalArray[(int)verX][(int)verY];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord + 0.25f, yCoord + 0.25f });

			verX = x;
			verY = y + 1;
			verZ = ImgArray[x][y + 1];
			normal = NormalArray[(int)verX][(int)verY];
			heightmapVex.push_back(TexVertex{ verX,verZ,verY,
				normal.x,normal.z,normal.y, xCoord, yCoord + 0.25f });


			if (x >= 61 && x < 189 && y >= 37 && y < 217)
			{
				if (x % 16 == 13 && y % 18 == 1)
				{		
					/*	if(counter % 2 == 0)
							fields[fieldPosX][fieldPosY] = new FieldComponent((float)x, (float)y, (float)ImgArray[x][y] + 0.1f, 16, 18, new BruteCard(counter));
						else if (counter % 3 == 0)
							fields[fieldPosX][fieldPosY] = new FieldComponent((float)x, (float)y, (float)ImgArray[x][y] + 0.1f, 16, 18, new MeleeCard(counter));
						else
							fields[fieldPosX][fieldPosY] = new FieldComponent((float)x, (float)y, (float)ImgArray[x][y] + 0.1f, 16, 18, new MagicCard(counter));
*/

						counter++;
						fields[fieldPosX][fieldPosY] = new FieldComponent((float)x, (float)y, (float)ImgArray[x][y] + 0.1f, 16, 18, NULL);
			
					
					fieldPosX++;
					if (fieldPosX > 7)
					{
						fieldPosX = 0;
						fieldPosY++;
					}
				}
			}
			
		}
	}
	Game::inputEvents.notifyMapLoaded();
}

FieldComponent* PlayingFieldComponent::getfieldComponent(int xx, int yy)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (fields[x][y]->onfield(xx, yy))
			{
				return fields[x][y];
			}
		}
	}
	return NULL;
}


void PlayingFieldComponent::getfieldComponentIndex(int &xx, int &yy)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (fields[x][y]->onfield(xx, yy))
			{
				xx = x;
				yy = y;
			}
		}
	}
}