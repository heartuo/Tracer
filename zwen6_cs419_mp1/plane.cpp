#include "plane.h"
// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>
const double Plane::kEpsilon = 0.001;

Plane::Plane(const Point3D p, const Normal& n) : 
point (p), normal (n)
{
	color = white; // all planes are white
	shape = PLANE;
}

bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t = (point - ray.o) * normal / (ray.d * normal);

	if (t > kEpsilon)
	{
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = ray.o + t * ray.d;
		// sr.shape = PLANE;
		return 1;
	}
	else
		return 0;
}
// #419end