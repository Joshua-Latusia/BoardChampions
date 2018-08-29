#include "ObjModel.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Texture.h"
#include <GL/freeglut.h>

Vec3f calculateNormal(Vec3f* v1, Vec3f* v2, Vec3f* v3)
{
	Vec3f va, vb, vr;
	float val;
	va.x = v1->x - v2->x;
	va.y = v1->y - v2->y;
	va.z = v1->z - v2->z;

	vb.x = v1->x - v3->x;
	vb.y = v1->y - v3->y;
	vb.z = v1->z - v3->z;

	vr.x = (va.y * vb.z) - (vb.y * va.z);
	vr.y = (vb.x * va.z) - (va.x * vb.z);
	vr.z = (va.x * vb.y) - (vb.x * va.y);

	val = sqrtf((vr.x * vr.x) + (vr.y * vr.y) + (vr.z * vr.z));

	Vec3f norm;
	norm.x = vr.x / val;
	norm.y = vr.y / val;
	norm.z = vr.z / val;

	return norm;
}

/**
* Replaces a substring in a string
*/
static std::string replace(std::string str, const std::string &toReplace, const std::string &replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}

/**
* Splits a string into substrings, based on a seperator
*/
static std::vector<std::string> split(std::string str, const std::string &seperator)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(seperator);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

/**
* Turns a string to lowercase
*/
static inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}


/**
* Cleans up a line for processing
*/
static inline std::string cleanLine(std::string line)
{
	line = replace(line, "\t", " ");
	while (line.find("  ") != std::string::npos)
		line = replace(line, "  ", " ");
	if (line == "")
		return "";
	if (line[0] == ' ')
		line = line.substr(1);
	if (line == "")
		return "";
	if (line[line.length() - 1] == ' ')
		line = line.substr(0, line.length() - 1);
	return line;
}




/**
* Loads an object model
*/
ObjModel::ObjModel(const std::string &fileName)
{
	std::cout << "Loading " << fileName << std::endl;
	std::string dirName = fileName;
	if (dirName.rfind("/") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("/"));
	if (dirName.rfind("\\") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("\\"));
	if (fileName == dirName)
		dirName = "";


	std::ifstream pFile(fileName.c_str());

	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}


	ObjGroup* currentGroup = new ObjGroup();
	currentGroup->materialIndex = -1;


	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = cleanLine(line);
		if (line == "" || line[0] == '#') //skip empty or commented line
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "v")
			vertices.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vn")
			normals.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vt")
			texcoords.push_back(Vec2f((float)atof(params[1].c_str()), (float)atof(params[2].c_str())));
		else if (params[0] == "f")
		{
			for (size_t ii = 4; ii <= params.size(); ii++)
			{		

				for (size_t i = ii - 3; i < ii; i++)	//magische forlus om van quads triangles te maken ;)
				{
					VertexNew vertexnew;
					std::vector<std::string> indices = split(params[i == (ii - 3) ? 1 : i], "/");
					if (indices.size() >= 1)	//er is een positie	
					{
					
						vertexnew.x = vertices[atoi(indices[0].c_str()) - 1].x;
						vertexnew.y = vertices[atoi(indices[0].c_str()) - 1].y;
						vertexnew.z = vertices[atoi(indices[0].c_str()) - 1].z;
					}
					if (indices.size() == 2)		//alleen texture
					{
						vertexnew.texx = texcoords[atoi(indices[1].c_str()) - 1].x;
						vertexnew.texy = texcoords[atoi(indices[1].c_str()) - 1].y;
					}
					if (indices.size() == 3)		//v/t/n of v//n
					{
						if (indices[1] != "") {
							vertexnew.texx = texcoords[atoi(indices[1].c_str()) - 1].x;
							vertexnew.texy = texcoords[atoi(indices[1].c_str()) - 1].y;
						}
						vertexnew.nx = normals[atoi(indices[2].c_str()) - 1].x;
						vertexnew.ny = normals[atoi(indices[2].c_str()) - 1].y;
						vertexnew.nz = normals[atoi(indices[2].c_str()) - 1].z;

					}
					verticesnew.push_back(vertexnew);
				}
				
				Vec3f normal = calculateNormal(new Vec3f(verticesnew[verticesnew.size() - 1].x, verticesnew[verticesnew.size() - 1].y, verticesnew[verticesnew.size() - 1].z),
					new Vec3f(verticesnew[verticesnew.size() - 2].x, verticesnew[verticesnew.size() - 2].y, verticesnew[verticesnew.size() - 2].z),
					new Vec3f(verticesnew[verticesnew.size() - 3].x, verticesnew[verticesnew.size() - 3].y, verticesnew[verticesnew.size() - 3].z)
				);
				for (int h = 1; h < 4; h++) {
					verticesnew[verticesnew.size() - h].nx = normal.x;
					verticesnew[verticesnew.size() - h].ny = normal.y;
					verticesnew[verticesnew.size() - h].nz = normal.z;
				}
			}
		}
		else if (params[0] == "s")
		{//smoothing groups
		}
		else if (params[0] == "mtllib")
		{
			loadMaterialFile(dirName + "/" + params[1], dirName);
		}
		else if (params[0] == "usemtl")
		{
			if (currentGroup->faces.size() != 0)
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->materialIndex = -1;

			for (size_t i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if (info->name == params[1])
				{
					currentGroup->materialIndex = i;
					break;
				}
			}
			if (currentGroup->materialIndex == -1)
				std::cout << "Could not find material name " << params[1] << std::endl;
		}
	}
	groups.push_back(currentGroup);
}


ObjModel::~ObjModel(void)
{
}




void ObjModel::draw()
{

	for (auto group : groups)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, materials[0]->texture->textureId);


		MaterialInfo * mat = materials[group->materialIndex];
		GLfloat color[] = { mat->specular.x, mat->specular.y, mat->specular.z };
		GLfloat color2[] = { mat->ambiant.x, mat->ambiant.y, mat->ambiant.z };
		GLfloat color3[] = { mat->diffuse.x, mat->diffuse.y, mat->diffuse.z };

		glMaterialfv(GL_FRONT, GL_SPECULAR, color);
		glMaterialfv(GL_FRONT, GL_AMBIENT, color2);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color3);


		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, sizeof(VertexNew), ((float*)verticesnew.data()) + 6);
		glNormalPointer(GL_FLOAT, sizeof(VertexNew), ((float*)verticesnew.data()) + 3);
		glVertexPointer(3, GL_FLOAT, sizeof(VertexNew), ((float*)verticesnew.data()) + 0);

		glDrawArrays(GL_TRIANGLES, 0, verticesnew.size());

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

	}

}

void ObjModel::loadMaterialFile(const std::string &fileName, const std::string &dirName)
{
	std::cout << "Loading " << fileName << std::endl;
	std::ifstream pFile(fileName.c_str());
	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}

	MaterialInfo* currentMaterial = NULL;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = cleanLine(line);
		if (line == "" || line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "newmtl")
		{
			if (currentMaterial != NULL)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->name = params[1];
		}
		else if (params[0] == "map_kd")
		{
			std::string tex = params[1];
			if (tex.find("/"))
				tex = tex.substr(tex.rfind("/") + 1);
			if (tex.find("\\"))
				tex = tex.substr(tex.rfind("\\") + 1);
			//TODO
			MaterialInfo * matinfo = new MaterialInfo();
			matinfo->texture = new Texture(dirName + "/" + tex);
			materials.push_back(matinfo);
		}
		else if (params[0] == "kd")
		{
			currentMaterial->diffuse = Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str()));

		}
		else if (params[0] == "ka")
		{
			currentMaterial->ambiant = Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str()));
		}
		else if (params[0] == "ks")
		{
			currentMaterial->specular = Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str()));
		}
		else if (
			params[0] == "illum" ||
			params[0] == "map_bump" ||
			params[0] == "map_ke" ||
			params[0] == "map_ka" ||
			params[0] == "map_d" ||
			params[0] == "d" ||
			params[0] == "ke" ||
			params[0] == "ns" ||
			params[0] == "ni" ||
			params[0] == "td" ||
			params[0] == "tf" ||
			params[0] == "tr" ||
			false)
		{
			//these values are usually not used for rendering at this time, so ignore them
		}
		else
			std::cout << "Didn't parse " << params[0] << " in material file" << std::endl;
	}
	if (currentMaterial != NULL)
		materials.push_back(currentMaterial);

}

ObjModel::MaterialInfo::MaterialInfo()
{
	texture = NULL;
}


