#include "DrawComponent.h"

DrawComponent::DrawComponent()
{
}

DrawComponent::DrawComponent(char* texPath)
{
	texture = new Texture(texPath);
}


DrawComponent::~DrawComponent()
{
}
