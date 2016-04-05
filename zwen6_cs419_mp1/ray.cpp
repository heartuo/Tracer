#include "ray.h"
Ray::Ray(void)
{

}

Ray::~Ray(void)
{
	
}

Ray::Ray(const Point3D& origin, const Vector3D& dir)
{
	o = origin;
	d = dir;
}