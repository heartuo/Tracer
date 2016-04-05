#include "world.h"
#include <iostream>
#include <pngwriter.h>

using namespace std;

/*
	World()
	takes void
	default constructor
*/
World::World(void)
{

}

/*
	build()
	takes void
	returns void
	sets up the objects and lightings of the world
*/
void World::build(void)
{
	vp.set_hres(500);
	vp.set_vres(500);
	vp.s = 2;
	vp.dist = 200.0;
	vp.eye = Point3D(0, 0, 700);
	vp.dir = Vector3D(0, 0, -1);
	vp.up = Vector3D(0, 1, 0);

	//vp.eye = Point3D(100, -400, 500);
	//vp.dir = Vector3D(0, 1, 0);
	//vp.up = Vector3D(0, 0, -1);


	vp.setup();

	// ViewPlane(Point3D eye, Vector3D dir, int dist, int h, int v, float s);
	// vp = ViewPlane();

	background_color = black;
	// l = new Light(Vector3D(1.0, 0, 0), 0.5);
	l.neg_dir = Vector3D(1.0, 0.0, 0.0);
	l.illum = RGBColor(1.0, 0.8, 0.8);

	tracer_ptr = new MultiTracer(this);

	Point3D c(0, -0, 0);
	double r = 200;
	Sphere* s = new Sphere(c, r);
	s->set_color(RGBColor(100, 100, 200));
	s->set_color(green);
	add_object(s);

	Point3D d(200, 0, 100);
	r = 100;
	s = new Sphere(d, r);
	s->set_color(RGBColor(100, 100, 200));
	s->set_color(red);
	add_object(s);

	Point3D e(-400, 0, 200);
	r = 300;
	s = new Sphere(e, r);
	s->set_color(RGBColor(100, 100, 200));
	s->set_color(grey);
	add_object(s);

	Triangle* t = new Triangle(Point3D(0, 100, 500), Point3D(200, 100, 600), Point3D(100, -100, 600));
	t->set_color(red);
	add_object(t);

	t = new Triangle(Point3D(-400, 0, 200), Point3D(0, 0, 500), Point3D(100, -400, 300));
	t->set_color(blue);
	add_object(t);
	
	Plane* p = new Plane(Point3D(0, -500, 0), Normal(0, 1, 0));
	add_object(p);
}

/*
	hit_objects()
	takes Ray
	returns ShadeRec
	calculates if the ray hits any objects in the world
	and return the info in ShadeRec
*/
ShadeRec World::hit_objects(const Ray& ray)
{
	ShadeRec sr(*this);
	double t;
	double tmin = kHugeValue;
	int num_objects = objects.size();
	GeometricObject* obj = 0;

	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t <= tmin)) {

			obj = objects[j];
			tmin = t;
			/*
			sr.shape = objects[j]->get_shape();
			sr.hit = true;
			sr.color = objects[j]->get_color();
			*/
		}
	if (obj)
	{
		obj->hit(ray, t, sr);
		sr.shape = obj->get_shape();
		sr.hit = true;
		sr.color = obj->get_color();
	}

	return sr;
}

/*
	render_scene()
	takes void
	returns void
	renders the scene received on the view plane onto screen
*/
void World::render_scene() const
{
	Ray ray;
	double zw = 500.0;
	double x, y;
	pngwriter png(vp.hres, vp.vres, 0, "ray_tracing.png");
	// cout << "image h" << vp.hres << "image v" << vp.vres << endl;
	ray.d = vp.dir;

	double sub_s = vp.s / 5.0;

	bool aa = true;
	bool persp = true;
	

	for (int r = 0; r < vp.vres; r++)
		for (int c = 0; c < vp.hres; c++)
		{
			RGBColor pixel_color;
			// add perspective here
			if (aa)
				for (int subr = 0; subr < 5; subr++)
					for (int subc = 0; subc < 5; subc++)
					{
						x = sub_s * (subc - 0.5 * 4) + vp.s * (c - 0.5 * (vp.hres - 1.0));
						y = sub_s * (subr - 0.5 * 4) + vp.s * (r - 0.5 * (vp.vres - 1.0));
						//ray.o = Point3D(x, y, zw);
						ray.o = Point3D(0, 0, 0);
						ray.o = ray.o + x * vp.u + y * vp.v - vp.dist * vp.w + vp.eye;
						// cout << "Y: " << ray.o.y << endl;
						ray.d = vp.dir;
						if (persp)
							// ray.d = Vector3D(vp.s * (c - vp.hres/2 + 0.5), vp.s * (r - vp.vres/2 + 0.5), -vp.dist);
						{
							ray.d = x * vp.u + y * vp.v - vp.dist * vp.w;
							ray.d.normalize();
						}
						pixel_color += tracer_ptr->trace_ray(ray);
					}
			else
			{
				x = vp.s * (c - 0.5 * (vp.hres - 1.0));
				y = vp.s * (r - 0.5 * (vp.vres - 1.0));
				// ray.o = Point3D(x, y, zw);
				ray.o = Point3D(0, 0, 0);
				ray.o = ray.o + x * vp.u + y * vp.v - vp.dist * vp.w + vp.eye;
				ray.d = vp.dir;
				if (persp)
				{
					ray.d = x * vp.u + y * vp.v - vp.dist * vp.w;
					ray.d.normalize();
				}
					// ray.d = Vector3D(vp.s * (c - vp.hres/2 + 0.5), vp.s * (r - vp.vres/2 + 0.5), -vp.dist);
				pixel_color = tracer_ptr->trace_ray(ray);
			}
			
			if (aa)
				pixel_color /= 25.0;

			png.plot(c + 1, r + 1, pixel_color.r, pixel_color.g, pixel_color.b);
		}

	png.close();

}



