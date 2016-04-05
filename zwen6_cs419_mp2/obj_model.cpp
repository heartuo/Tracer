#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "obj_model.h"

using namespace std;

OBJModel::OBJModel(const char *path)
{
	vertices = new vector<Point3D>;
	faces = new vector<std::tuple<int, int, int>>;
	fns = new vector<Vector3D>;
	vns = new vector<Vector3D>;

	if (!loadFile(path))
		calcNormals();
}

int OBJModel::loadFile(const char *path)
{
	ifstream in(path, ios::in);
	if(!in)
	{
    	printf("No such file: %s \n", path);
    	return 1;
	}
	//allocating only a total of 128 characters since a .obj file is expected
	string buffer;
	while(getline(in, buffer))
	{
    	// read the first word of the line
 		if (buffer.substr(0, 2) == "v ")
		{
			Point3D v;
			istringstream s(buffer.substr(2));
			s >> v.x;
			s >> v.y;
			s >> v.z;
			
    		vertices->push_back(v);
		}   
 		else if (buffer.substr(0, 2) == "f ")
		{
    		std::string vertex1, vertex2, vertex3;
			tuple<int, int, int> f;
			istringstream s(buffer.substr(2));
			s >> std::get<0>(f);
			std::get<0>(f)--;//.obj format index starts at 1
			s >> std::get<1>(f);
			std::get<1>(f)--;//.obj format index starts at 1
			s >> std::get<2>(f);
			std::get<2>(f)--;//.obj format index starts at 1
			faces->push_back(f);
		}
	}
	return 0;
}

/* This function calculates per-face and per-vertex normals from the vertices and faces. */
void OBJModel::calcNormals()
{
	for (int i = 0; i < faces->size(); i++)
	{
		Point3D a = (*vertices)[std::get<0>((*faces)[i])];
		Point3D b = (*vertices)[std::get<1>((*faces)[i])];
		Point3D c = (*vertices)[std::get<2>((*faces)[i])];

		Vector3D n = ((b - a) ^ (c - a));
		n.normalize();
		fns->push_back(n);
	}
	// per-face normals processed and per-vertex normals set up
	for (int i = 0; i < vertices->size(); i++)
		vns->push_back(Vector3D(0.0, 0.0, 0.0)); 
	for (int i = 0; i < faces->size(); i++)
	{
		(*vns)[std::get<0>((*faces)[i])] += (*fns)[i];
		(*vns)[std::get<1>((*faces)[i])] += (*fns)[i];
		(*vns)[std::get<2>((*faces)[i])] += (*fns)[i];
	}// add per-vertex vectors
	for (int i = 0; i < vns->size(); i++)
	{
		((*vns)[i]).normalize();
	}// normalize per-vertex vectors
}

void OBJModel::clearNormals()
{
	fns->clear();
	vns->clear();
}

void OBJModel::destroy()
{
	vertices->clear();
	faces->clear();
	fns->clear();
	vns->clear();
	free(vertices);
	free(faces);
	free(fns);
	free(vns);
}

void OBJModel::clear()
{
	vertices->clear();
	faces->clear();
	fns->clear();
	vns->clear();
}

OBJModel::~OBJModel()
{
	destroy();
}
