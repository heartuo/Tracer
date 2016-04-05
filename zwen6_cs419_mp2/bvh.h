#ifndef __BVH__
#define __BVH__

class Sphere;
class Ray;

#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include "geometric_object.h"
#include "sphere.h"
#include "ray.h"

using namespace std;

class BVH
{
public: 
	double r; // radius of the bounding sphere
	Point3D c; // centroid
	BVH* left; 
	BVH* right; // childrens
	vector<GeometricObject*> prim;

	BVH(vector<GeometricObject*> v);
	bool traverse(Ray ray, ShadeRec& sr, double& t, double& tmin, GeometricObject*& obj);
	BVH();
	~BVH();
};

#endif