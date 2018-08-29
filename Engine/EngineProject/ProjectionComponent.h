#pragma once
class ProjectionComponent
{
public:
	void static display();
	void static update();
	void drawAllFields();


	ProjectionComponent();
	void static drawFields(int x, int);
	~ProjectionComponent();
};

