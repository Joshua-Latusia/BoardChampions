#ifndef ModelComponent_H
#define ModelComponent_H

#include <vector>
#include <list>

#include "Vec.h"
#include "DrawComponent.h"
class Texture;

class VertexNew
{
public:
	float x, y, z;
	float nx, ny, nz;
	float texx, texy;

};


class ModelComponent : public DrawComponent
{
private:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};


	class Face
	{
	public:
		std::list<Vertex> vertices;
	};
	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		Texture* texture;
		Vec3fl ambiant;
		Vec3fl diffuse;
		Vec3fl specular;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		std::list<Face> faces;
	};


	std::vector<Vec3fl>	vertices;
	std::vector<VertexNew>	verticesnew;
	std::vector<Vec3fl>	normals;
	std::vector<Vec2f>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	void loadMaterialFile(const std::string &fileName, const std::string &dirName);
public:
	ModelComponent(const std::string &filename);
	~ModelComponent(void);

	virtual void draw() override;
	virtual void update(float) override;
	void attackMethod();
	void setAttacked();
};

class ModelManager
{
	//void draw() override;




public:

	static std::vector<ModelComponent*> models;
	

	ModelManager();


};


#endif