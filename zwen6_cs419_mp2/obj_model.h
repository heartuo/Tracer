#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#include <stdlib.h>
#include <math.h>
#include <vector>
#include <tuple>
#include "point3d.h"
#include "vector3d.h"

using namespace std;

class OBJModel
{
	public:
		OBJModel(const char *path);
		void clearNormals();
		void calcNormals();
		~OBJModel();
		vector<Point3D> *vertices;
		vector<std::tuple<int, int, int>> *faces;
		vector<Vector3D> *fns;
		vector<Vector3D> *vns;
	private:

		int loadFile(const char *path);
		void clear();
		void destroy();
};

#endif
