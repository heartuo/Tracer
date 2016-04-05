#ifndef __TRACER__
#define __TRACER__

class World;

#include "world.h"

class Tracer
{
public:
	Tracer(void);
	Tracer(World* world_ptr);
	virtual RGBColor trace_ray(const Ray& ray) const;
	virtual ~Tracer(void);

protected:
	World* world_ptr;
};

inline Tracer::Tracer(void)
{

}

inline Tracer::Tracer(World* world_ptr) : world_ptr(world_ptr)
{

}

inline RGBColor Tracer::trace_ray(const Ray& ray) const
{

}

inline Tracer::~Tracer(void)
{

}

#endif