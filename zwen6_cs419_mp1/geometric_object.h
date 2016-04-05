#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>
class ShadeRec;

#include "constants.h"
#include "point3d.h"
#include "vector3d.h"
#include "ray.h"
#include "shade_rec.h"

class GeometricObject
{
	public: 
		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& s) const;
		RGBColor get_color();
		void set_color(RGBColor c);
		int get_shape();
	protected:
		RGBColor color;
		int shape;
};

inline bool GeometricObject::hit(const Ray& ray, double& tmin, ShadeRec& s) const
{

}

inline RGBColor GeometricObject::get_color()
{
	return color;
}

inline int GeometricObject::get_shape()
{
	return shape;
}

inline void GeometricObject::set_color(RGBColor c)
{
	color = c;
}

// #419end

#endif