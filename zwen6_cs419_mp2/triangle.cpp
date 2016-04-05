#include "triangle.h"
#include <iostream>

using namespace std;

const double Triangle::kEpsilon = 0.001;

Triangle::Triangle(const Point3D a, const Point3D b, const Point3D c) : 
a(a), b(b), c(c)
{
	color = RGBColor(0.4, 0, 0); // all planes are grey
	shape = TRIANGLE;

	Vector3D ab = a - b;
	Vector3D ac = a - c;

	normal = ab ^ ac;
	normal.normalize();
}

RGBColor Triangle::get_color()
{
	return color;
}

bool Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t = (a - ray.o) * normal / (ray.d * normal);

	if (t > kEpsilon)
	{

		Point3D p = ray.o + t * ray.d;

		double lambda1 = ((b.y - c.y) * (p.x - c.x) + (c.x - b.x) * (p.y - c.y)) / ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));
		double lambda2 = ((c.y - a.y) * (p.x - c.x) + (a.x - c.x) * (p.y - c.y)) / ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));
		double lambda3 = 1 - lambda2 - lambda1;

		if (lambda1 >= 0 && lambda1 <= 1 && lambda2 >= 0 && lambda2 <= 1 && lambda3 >= 0 && lambda3 <= 1)
		{
			// cout << "lambda2 " << lambda2 << endl;
			tmin = t;
			sr.ray = ray;
			sr.normal = normal;
			sr.light_normal = normal;
			sr.local_hit_point = ray.o + t * ray.d;
			// sr.shape = TRIANGLE;

			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
		return 0;
}

Point3D Triangle::get_centroid()
{
	return (a + b + c) * 0.33333;
}

double Triangle::get_ext()
{
	Point3D centr = get_centroid();
	double da = centr.distance(a);
	double db = centr.distance(b);
	double dc = centr.distance(c);

	if (da > db)
	{
		return (da > dc)?da:dc;
	}

	return (db > dc)?db:dc;
}

