#include "sphere.h"
#include <iostream>

// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>

const double Sphere::kEpsilon = 0.001;

Sphere::Sphere(const Point3D c, const double& r) : center (c), r (r)
{
	color = red; // all spheres are red
	shape = SPHERE;
}

RGBColor Sphere::get_color()
{
	return color;
}

bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t;
	Vector3D tmp = ray.o - center;
	double a = ray.d * ray.d;
	double b = 2.0 * tmp * ray.d;
	double c = tmp * tmp - r * r;
	double disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return false;
	else
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (- b - e) / denom;

		if (t > kEpsilon)
		{
			tmin = t;
			// sr.shape = SPHERE;
			sr.normal = (tmp + t * ray.d) / r;
			sr.ray = ray;
			sr.local_hit_point = ray.o + t * ray.d;
			sr.light_normal = (sr.local_hit_point - center) / r;

			return true;
		}

		t = (- b + e) / denom;
		if (t > kEpsilon)
		{
			tmin = t;
			// sr.shape = SPHERE;
			sr.normal = (tmp + t * ray.d) / r;
			sr.ray = ray;
			sr.local_hit_point = ray.o + t * ray.d;
			sr.light_normal = (sr.local_hit_point - center) / r;
			return true;
		}
	}

	return false;
}
// #419end

Point3D Sphere::get_centroid()
{
	return center;
}

double Sphere::get_ext()
{
	return r;
}