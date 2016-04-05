#ifndef __WORLD__
#define __WORLD__

class MultiTracer;

#include <vector>
#include "constants.h"
#include "point3d.h"
#include "vector3d.h"

#include "light.h"
#include "view_plane.h"
#include "rgb_color.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "tracer.h"
#include "multi_tracer.h"

using namespace std;

class World
{
public:
	ViewPlane vp;
	RGBColor background_color;
	MultiTracer* tracer_ptr;
	vector<GeometricObject*> objects;
	Light l;

	World(void);

	void add_object(GeometricObject* obj_ptr);
	void build(void);
	void render_scene(void) const;
	void open_window(const int hres, const int vres) const;
	ShadeRec hit_objects(const Ray& ray);

	void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;
private:
	void delete_objects();
};

inline void World::add_object(GeometricObject* object_ptr)
{  
	objects.push_back(object_ptr);	
}

#endif
