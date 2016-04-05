#include "world.h"
#include <iostream>
#include <pngwriter.h>

pthread_mutex_t mlock;

using namespace std;

int nt; 
int chunk; // presumably an integer

bool aa;
bool persp;
RGBColor rgb_max;
RGBColor **image;
int hres;
World* w;

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
	// vp.s = 0.01; // s for teapot
	// vp.s = 0.001; // s for cow
	vp.s = 0.1; // s for spheres
	vp.dist = 80.0;
	vp.eye = Point3D(15, 80, 120); // eye for teapot
	// vp.eye = Point3D(15, 80, 120); // eye for teapot
	vp.dir = Vector3D(0, -1.2, -1); // dir for teapot
	// vp.dir = Vector3D(0, 0.8, -1); // dir for teapot
	vp.up = Vector3D(0, 1, 0);

	//vp.eye = Point3D(100, -400, 500);
	//vp.dir = Vector3D(0, 1, 0);
	//vp.up = Vector3D(0, 0, -1);

	vp.setup();

	// ViewPlane(Point3D eye, Vector3D dir, int dist, int h, int v, float s);
	// vp = ViewPlane();

	background_color = black;
	// l = new Light(Vector3D(1.0, 0, 0), 0.5);
	// l.neg_dir = Vector3D(1.0, 0.0, 0.0);
	// l.illum = RGBColor(1.0, 0.8, 0.8);

	// lights.push_back(new PointLight(RGBColor(1.0, 1.0, 1.0), Point3D(100, 0, 0)));
	// lights.push_back(new PointLight(RGBColor(1.0, 1.0, 1.0), Point3D(10, 8, 8)));
	//lights.push_back(new PointLight(RGBColor(1.0, 1.0, 1.0), Point3D(50, 20, 50)));
	lights.push_back(new PointLight(RGBColor(0.7, 0.6, 0.7), Point3D(5, 5, 6)));

	tracer_ptr = new MultiTracer(this);

	OBJModel* teapot = new OBJModel("teapot_0.obj");
	// add_model(teapot);
	// OBJModel* teapot = new OBJModel("cow.obj");
	// add_model(teapot);

	Point3D f(0, 0, -25); // wall for spheres
	// Point3D f(0, 0, -5); // wall for teapot
	Vector3D nn(0, 0, 1.0);
	Plane* ss = new Plane(f, nn);
	ss->set_color(RGBColor(0.04, 0.04, 0.15));
	add_object(ss, 0);

	
	Sphere* s;
	/*
	Point3D c(16, 0, 10);
	double r = 5;
	s = new Sphere(c, r);
	s->set_color(RGBColor(0, 0.2, 0));
	add_object(s, 1);

	Point3D d(-16, 0, 0);
	r = 10;
	s = new Sphere(d, r);
	s->set_color(RGBColor(0.2, 0, 0));
	add_object(s, 1);
	*/

	/*
	Point3D e(0, -20, -50);
	r = 4;
	s = new Sphere(e, r);
	s->set_color(RGBColor(0.4, 0, 0));
	add_object(s, 1);
	*/
	

	
	for (int i = 0; i < 10000; i++)
	{
		int c_rand = rand() % 4;
		double rr = rand() % 6;
		double x = rand() % 50 - 25;
		double y = rand() % 50 - 25;
		double z = rand() % 30;
		

		Point3D pp(x, y, z);
		s = new Sphere(pp, rr);

		switch(c_rand)
		{
			case 0:
				s->set_color(RGBColor(0.1, 0.1, 0.2));
				break;
			case 1:
				s->set_color(RGBColor(0.2, 0.1, 0.0));
				break;
			case 2:
				s->set_color(RGBColor(0.0, 0.1, 0.0));
				break;
			case 3:
				s->set_color(RGBColor(0.0, 0.0, 0.1));
				break;
			default:
				break;
		}

		add_object(s, 1);
	}
	

	/*
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
	*/

	bvh = new BVH(objects);

	aa = false;
	persp = true;
	rgb_max = 0.0;
	hres = vp.hres;
	w = this;

	image = new RGBColor*[vp.vres];

	for (int i = 0; i < vp.vres; i++)
	{
		image[i] = new RGBColor[vp.hres];
	}


	// multithreading... 

	nt = 8;
	chunk = vp.vres / nt; // presumably an integer
	cout << "chunk is: " << chunk << endl;

	cout << "world built..." << endl;
	
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
	int num_inf = inf.size();
	GeometricObject* obj = 0;

	// process infinite objects
	for (int j = 0; j < num_inf; j++)
		if (inf[j]->hit(ray, t, sr) && (t <= tmin)) {

			obj = inf[j];
			tmin = t;
		}
	if (obj)
	{
		sr.shape = obj->get_shape();
		sr.hit = true;
		sr.color = obj->get_color();
		obj->hit(ray, t, sr);
	}
	
	obj = NULL;
	// recurse into bvh
	bvh->traverse(ray, sr, t, tmin, obj);

	if (obj)
	{
		sr.shape = obj->get_shape();
		sr.hit = true;
		sr.color = obj->get_color();
		obj->hit(ray, t, sr);
	}

	return sr;
}

void World::render_pixel(int r, int c, bool persp, bool aa, RGBColor** buffer, RGBColor& rgb_max) const
{
	Ray ray;
	RGBColor pixel_color;
	double x, y;

	double r_max = 0.0;
	double g_max = 0.0;
	double b_max = 0.0;

	double sub_s = vp.s / 5.0;

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

	double rgb = pixel_color.r * pixel_color.r + pixel_color.g * pixel_color.g + pixel_color.b * pixel_color.b;
	
	// mutex lock start //////////
	pthread_mutex_lock(&mlock);
	double c_max = rgb_max.r * rgb_max.r + rgb_max.g * rgb_max.g + rgb_max.b * rgb_max.b;

	if (rgb > c_max)
	{
		rgb_max.r = pixel_color.r;
		rgb_max.g = pixel_color.g;
		rgb_max.b = pixel_color.b;
	}
	// mutex lock end ///////////
	pthread_mutex_unlock(&mlock);
			
	buffer[r][c] = RGBColor(pixel_color.r, pixel_color.g, pixel_color.b);
	// png.plot(c + 1, r + 1, pixel_color.r, pixel_color.g, pixel_color.b);
	// cout << "added pixel " << r << " "<< c << endl;
}

void* render_chunk(void* i)
{
	int k = *(int*)i;
	cout << "thread " << k << "started..." << endl;

	for (int r = k * chunk ; r < (k + 1) * chunk; r++)
		{
			for (int c = 0; c < hres; c++)
			{
				w->render_pixel(r, c, persp, aa, image, rgb_max);
			}
		}
	return 0;
}

/*
	render_scene()
	takes void
	returns void
	renders the scene received on the view plane onto screen
*/
void World::render_scene() const
{

	cout << "rendering..." << endl;
	pthread_mutex_init(&mlock, NULL);
	
	pngwriter png(vp.hres, vp.vres, 0, "ray_tracing.png");
	// cout << "image h" << vp.hres << "image v" << vp.vres << endl;

	/*
	// single-threaded solution /////////////////
	for (int r = 0; r < vp.vres; r++)
		for (int c = 0; c < vp.hres; c++)
		{
			render_pixel(r, c, persp, aa, image, rgb_max);
		}
	////////////////////////////////////////////
	*/
	
	pthread_t tids[nt - 1];
	int chunks[nt - 1];

	
	for (int k = 1; k < nt; k++)
	{
		chunks[k - 1] = k;

		pthread_create(&(tids[k - 1]), NULL, render_chunk, &(chunks[k - 1]));
		// render_chunk((void*)&(tids[k - 1]));
	}
	

	for (int r = 0; r < chunk; r++)
		for (int c = 0; c < vp.hres; c++)
		{
			render_pixel(r, c, persp, aa, image, rgb_max);
		}

	// pthread join ////////////////////////
	
	void* status;
	for (int i = 1; i < nt; i++)
	{
		pthread_join(tids[i - 1], &status);
	}
	
	

	for (int r = 0; r < vp.vres; r++)
		for (int c = 0; c < vp.hres; c++)
	{
		double rr = image[r][c].r / rgb_max.r;
		double gg = image[r][c].g / rgb_max.g;
		double bb = image[r][c].b / rgb_max.b;

		png.plot(c + 1, r + 1, image[r][c].r, image[r][c].g, image[r][c].b);
		// png.plot(c + 1, r + 1, rr, gg, bb);
	}

	pthread_mutex_destroy(&mlock);
	delete image;

	cout << "render successful" << endl;

	png.close();

}



