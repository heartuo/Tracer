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
void MultiTracer::apply_lightings(ShadeRec& sr) const
{
	Light l = world_ptr->l;
	RGBColor k(1.0, 1.0, 1.0);

	if (sr.shape == PLANE || sr.shape == TRIANGLE)
	{
		// cout << ((1/255) * (k * l.illum)) * (sr.normal * l.neg_dir) << endl;
		sr.color += ((k * l.illum)) * (sr.normal * l.neg_dir);
		// RGBColor t = ((1/255) * (k * l.illum)) * (sr.normal * l.neg_dir);
		// cout << "R: " << t.r << "G: " << t.g << "B: " << t.b << endl;
		return;
	}
	if (sr.shape == SPHERE)
	{
		sr.color += ((k * l.illum)) * (sr.light_normal * l.neg_dir);
		
		// RGBColor t = ((k * l.illum)) * (sr.normal * l.neg_dir);
		//cout << "R: " << t.r << "G: " << t.g << "B: " << t.b << endl;
		//cout << "Dot: " << (sr.normal * l.neg_dir) << endl;
		return;
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