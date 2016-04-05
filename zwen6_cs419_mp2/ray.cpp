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

Ray::Ray(const Ray& ray)
{
	o = ray.o;
	d = ray.d;
}

Ray& Ray::operator= (const Ray& rhs)
{
	this->o = rhs.o;
	this->d = rhs.d;
	this->hit = rhs.hit;
	return (*this);
}