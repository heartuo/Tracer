#ifndef __PLANE__
#define __PLANE__

#include "geometric_object.h"

// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>

class Plane: public GeometricObject
{
	public:
		Plane();
		Plane(const Point3D p, const Normal& n);
		virtual RGBColor get_color();
		virtual bool hit(const Ray& ray, double& t, ShadeRec& sr) const; // t is the hit point parameter
		virtual Point3D get_centroid();
	private: 
		Point3D point; // a point in the plane
		Normal normal; // plane's normal
		static const double kEpsilon;

};

// #419end

#endif