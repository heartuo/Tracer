#ifndef __WORLD__
#define __WORLD__

class MultiTracer;
class Ray;

#include <vector>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
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
#include "obj_model.h"
#include "bvh.h"
#include "point_light.h"
#include <iostream>

using namespace std;

#define INFINITE 0
#define FINITE 1

class World
{
public:
	ViewPlane vp;
	RGBColor background_color;
	MultiTracer* tracer_ptr;
	vector<GeometricObject*> inf; // infinite objects e.g. planes
	vector<GeometricObject*> objects;
	BVH* bvh = 0;
	vector<PointLight*> lights;

	World(void);

	void add_object(GeometricObject* obj_ptr, int type); // type is for infinite or finite
	void add_model(OBJModel* mdl);
	void build(void);
	void render_scene(void) const;
	void render_pixel(int r, int c, bool persp, bool aa, RGBColor** buffer, RGBColor& rgb_max) const;
	void open_window(const int hres, const int vres) const;
	ShadeRec hit_objects(const Ray& ray);

	void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;
private:
	void delete_objects();
};

inline void World::add_object(GeometricObject* object_ptr, int type)
{
	if (type == 0)
		inf.push_back(object_ptr);	
	if (type == 1)
		objects.push_back(object_ptr);
}

inline void World::add_model(OBJModel* mdl)
{
	cout << "starting adding model" << endl;
	Triangle* t = NULL;
	for (int i = 0; i < mdl->faces->size(); i++)
	{
		t = new Triangle((*mdl->vertices)[std::get<0>((*(mdl->faces))[i])], (*mdl->vertices)[std::get<1>((*(mdl->faces))[i])], (*mdl->vertices)[std::get<2>((*(mdl->faces))[i])]);
		add_object(t, 1);
		cout << "added face " << i << endl;
	}

	return;
}


#endif
