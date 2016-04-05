#ifndef __SHADE_REC__
#define __SHADE_REC__

// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>

class World;

#include "constants.h"
#include "point3d.h"
#include "vector3d.h"
#include "rgb_color.h"
#include "normal.h"
#include "ray.h"



class ShadeRec
{
public:
	bool hit;
	Point3D local_hit_point;
	Ray ray;
	Normal normal;
	Normal light_normal;
	RGBColor color;
	World &world;
	int shape; // geometric shape

	ShadeRec(World& w);
	ShadeRec(const ShadeRec& sr);
	~ShadeRec(void);

	ShadeRec& operator= (const ShadeRec& rhs);
};

inline ShadeRec::~ShadeRec()
{

}

// #419end

#endif