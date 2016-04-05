#include "shade_rec.h"

// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>

ShadeRec::ShadeRec(World& w)
	:hit(false), local_hit_point(), normal(), light_normal(), color(black), world(w)
{}

ShadeRec::ShadeRec(const ShadeRec& sr)
	: 	hit(sr.hit),
		local_hit_point(sr.local_hit_point),
		normal(sr.normal),
		light_normal(), 
		color(sr.color),
		world(sr.world)
{}

// #419end