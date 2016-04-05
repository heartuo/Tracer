#include "c_board.h"
const double CBoard::kEpsilon = 0.001;

CBoard::CBoard(const Point3D p, const Normal& n) : 
point (p), normal (n)
{
	color = white; // all planes are white
	shape = PLANE;
}

RGBColor CBoard::get_color()
{
	return color;
}

Point3D CBoard::get_centroid()
{
	return Point3D(0, 0, 0);
}

bool CBoard::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t = (point - ray.o) * normal / (ray.d * normal);

	if (t > kEpsilon)
	{
		tmin = t;
		sr.ray = ray;
		sr.normal = normal;
		sr.light_normal = normal;
		sr.local_hit_point = ray.o + t * ray.d;
		Vector3D diff = sr.local_hit_point - point;

		/*
		int xg = ((int)diff.x) / 100;
		int zg = ((int)diff.z) / 100;

		if ((xg % 2) && (zg % 2))
			sr.color = black;
		else if ((xg % 2) && !(zg % 2))
			sr.color = white;
		else if (!(xg % 2) && (zg % 2))
			sr.color = white;
		else // (!(xg % 2) && !(yg % 2))
			sr.color = black;
		*/
		
		double rrx[4][4] = { {1.0, 0, 0, 0}, 
			{0, diff.y / diff.length(), diff.z / diff.length(), 0}, 
			{0, -diff.z / diff.length(), diff.y / diff.length(), 0}, 
			{0, 0, 0, 1.0} };
		
		Matrix rx(rrx);

		diff = rx * diff;

		double rrz[4][4] = {{diff.y / diff.length(), diff.x / diff.length(), 0, 0}, 
			{-diff.x / diff.length(), diff.y / diff.length(), 0, 0}, 
			{0, 0, 1.0, 0}, 
			{0, 0, 0, 1.0}};

		Matrix rz(rrz);

		diff = rz * diff;

		int xg = ((int)diff.z) / 100;
		int zg = ((int)diff.y) / 100;

		if ((xg % 2) && (zg % 2))
			sr.color = black;
		else if ((xg % 2) && !(zg % 2))
			sr.color = white;
		else if (!(xg % 2) && (zg % 2))
			sr.color = white;
		else // (!(xg % 2) && !(yg % 2))
			sr.color = black;

		/*
		// y doesnt matter here
		if (((int) diff.x + (int) diff.z) % 2 == 1)
		// if (diff.length() > 200)
		{
			sr.color = black;
		}
		else
		{
			sr.color = white;
		}
		*/
		

		//(int(x) + int(y))%2 == 1
		return 1;
	}
	else
		return 0;
}