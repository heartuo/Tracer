#include "multi_tracer.h"
#include <iostream>

using namespace std;

MultiTracer::MultiTracer(void): Tracer() {}

MultiTracer::MultiTracer(World* _worldPtr): Tracer(_worldPtr) {}

MultiTracer::~MultiTracer(void) {}

/*
	apply_lightings()
	takes ShadeRec
	returns void
	checks the ShadeRec's object shape and applies appropriate lightings
*/

RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi)
{
	RGBColor l;
	float ndotwi = sr.light_normal * wi;
	Vector3D r(-wi + 2.0 * sr.light_normal * ndotwi);
	float rdotwo = r * wo;

	RGBColor ks(0.7); // specular coeff
	double e = 10;
	if (rdotwo > 0.0)
		l = ks * pow(rdotwo, e);

	return l;
}

void MultiTracer::apply_lightings(ShadeRec& sr) const
{
	
	

	vector<PointLight*> pl = world_ptr->lights;
	RGBColor kd(0.4);

	for (int i = 0; i < pl.size(); i++)
	{
		Ray sray; // shadow ray
		sray.o = sr.local_hit_point;
		sray.d = pl[i]->p - sr.local_hit_point;
		sray.d.normalize();

		
		ShadeRec ssr = world_ptr->hit_objects(sray); // shadow shade rec
		if (ssr.hit)
			continue;
		

		Vector3D nd = sray.d;

		// cout << ((1/255) * (k * l.illum)) * (sr.normal * l.neg_dir) << endl;
		RGBColor l = sr.color;


		Vector3D wo = -sr.ray.d;
		Vector3D wi = nd;
		float ndotwi = sr.light_normal * wi;

		if (ndotwi > 0.0)
		{
			l += (f(sr, wo, wi) + kd) * (pl[i]->illum * ndotwi);
			// l += (((k * pl[i]->illum)) * (sr.light_normal * nd));
		}

		sr.color = l;

		/*
		if (sr.shape == SPHERE)
		{
			sr.color += ((k * pl[i]->illum)) * (sr.light_normal * nd);
		
			// RGBColor t = ((k * l.illum)) * (sr.normal * l.neg_dir);
			//cout << "R: " << t.r << "G: " << t.g << "B: " << t.b << endl;
			//cout << "Dot: " << (sr.normal * l.neg_dir) << endl;
			return;
		}
		*/
	}

	
}

/*
	trace_ray()
	takes Ray
	returns RGBColor
	uses helper function to trace the color returned by the ray
*/
RGBColor MultiTracer::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
		
	if (sr.hit)
	{
		apply_lightings(sr);
		return (sr.color);   
	}
	
	else
		return (world_ptr->background_color);
}