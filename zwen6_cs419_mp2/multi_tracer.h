#ifndef __MULTI_TRACER__
#define __MULTI_TRACER__

#include "tracer.h"
#include <math.h>

class MultiTracer: public Tracer
{
	public:
		MultiTracer();
		MultiTracer(World* world_ptr);
		void apply_lightings(ShadeRec& sr) const;
		virtual ~MultiTracer(void);
		virtual RGBColor trace_ray(const Ray& ray) const;
};

#endif