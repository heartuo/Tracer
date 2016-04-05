#ifndef __POINT_LIGHT__
#define __POINT_LIGHT__

class PointLight: public Light
{
	public:
		PointLight(RGBColor i, Point3D p);
		Point3D p;

};

inline PointLight::PointLight(RGBColor i, Point3D p) :
p(p)
{
	illum = i;
}

#endif