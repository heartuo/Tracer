#ifndef __LIGHT__
#define __LIGHT__

#include "Vector3D.h"

class Light
{
public:
	Vector3D neg_dir; // negative direction of the light
	RGBColor illum; // illumination level
	Light(Vector3D nd, RGBColor i);
	Light();
};

inline Light::Light()
{

}

inline Light::Light(Vector3D nd, RGBColor i) : neg_dir(nd), illum(i)
{

}

#endif