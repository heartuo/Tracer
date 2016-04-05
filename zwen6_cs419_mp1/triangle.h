#ifndef __TRIANGLE__
#define __TRIANGLE__

// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>

#include "geometric_object.h"
//#include "rgb_color.h"
//#include "normal.h"

class Triangle : public GeometricObject
{
public:
	static const double kEpsilon;
	Point3D a;
	Point3D b;
	Point3D c;

	Normal normal;

	Triangle(const Point3D a, const Point3D b, const Point3D c);
	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

};

#endif

// #419end