#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

#include "vector3d.h"
#include "point3d.h"

class ViewPlane
{
public:
	int hres;
	int vres;
	int dist; // distance from projection point to plane

	Vector3D dir;
	Vector3D up;
	Point3D eye;

	Vector3D u;
	Vector3D v;
	Vector3D w;

	ViewPlane(Point3D eye, Vector3D dir, Vector3D up, int dist, int h, int v, float s);
	ViewPlane();

	void setup();

	float s; // pixel size
	float gamma;
	float inv_gamma; // 1/gamma

	void set_hres(int h);
	void set_vres(int v);
};

/*
	setup()
	takes void
	returns void
	sets up the camera's local coordinates
*/
inline void ViewPlane::setup()
{
	w = eye - dir;
	w.normalize();

	u = up ^ w;
	u.normalize();

	v = - u ^ w;
	v.normalize();
}

inline void ViewPlane::set_hres(int h)
{  
	hres = h;	
}
inline void ViewPlane::set_vres(int v)
{  
	vres = v;	
}

inline ViewPlane::ViewPlane()
{
}
/*
	ViewPlane()
	takes Point3D, Vector3D, Vector3D, int, int, int, float
	fill the class' member variables with data
*/
inline ViewPlane::ViewPlane(Point3D eye, Vector3D dir, Vector3D up, int dist, int h, int v, float s) : eye(eye), dir(dir), up(up), dist(dist), hres(h), vres(v), s(s)
{
}
#endif