#ifndef __SPHERE__
#define __SPHERE__
// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>
#include "geometric_object.h"

#include <math.h>

class Sphere: public GeometricObject
{
	public:
		Sphere();
		Sphere(const Point3D c, const double& r);
		virtual bool hit(const Ray& ray, double& t, ShadeRec& sr) const; // t is the hit point parameter
		virtual RGBColor get_color();
		virtual Point3D get_centroid();
		virtual double get_ext();
	private: 
		Point3D center; // center
		double r; // radius
		static const double kEpsilon;
};
// #419end

#endif