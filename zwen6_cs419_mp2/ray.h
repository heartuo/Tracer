#ifndef __RAY__
#define __RAY__

// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>

#include "point3d.h"
#include "vector3d.h"

class Ray
{
public:
	bool hit;
	Point3D o;
	Vector3D d;

	Ray(void);
	Ray(const Point3D& origin, const Vector3D& dir);
	Ray(const Ray& ray);
	~Ray(void);

	Ray& operator= (const Ray& rhs);
};

// #cs419end

#endif