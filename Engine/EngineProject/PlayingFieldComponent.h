#pragma once
#ifndef PLAYING_FIELD_COMPONENT_H
#define PLAYING_FIELD_COMPONENT_H
#include "DrawComponent.h"
#include "FieldComponent.h"
#include <vector>
#include "Vec.h"
#include "vertices.h"


class PlayingFieldComponent : public DrawComponent
{
private:
	std::vector<TexVertex> heightmapVex;

	float ImgArray[256][256];
	Vec3fl NormalArray[255][255];
	char* heightPath = "";

	static void standardFillFieldColor(int posx, int posy);
	static void ridderFillFieldColor(int posx, int posy);
	static void magicFillFieldColor(int posx, int posy);

public:
	bool wireframeMode = false;
	bool done;
	
	static FieldComponent* fields[8][10];

	void init() override;
	PlayingFieldComponent(char* texPath, char* heightPath);
	~PlayingFieldComponent();
	void drawHeightMap();
	static Vec3fl calculateNormal(Vec3fl* v1, Vec3fl* v2, Vec3fl* v3);
	Vec3fl getInterpolatedValue(Vec3fl* v1, Vec3fl* v2, Vec3fl* v3, Vec3fl* v4, Vec3fl* v5);
	static void clearFieldColor();
	static void fillFieldColor(int modelID, int posx, int posy);
	static bool isValid(int x, int y);
	void draw() override;
	void fillArrays();
	static FieldComponent* getfieldComponent(int x, int y);
	static void getfieldComponentIndex(int & xx, int &yy);
};

#endif


