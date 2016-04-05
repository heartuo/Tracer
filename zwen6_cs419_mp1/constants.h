#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <stdlib.h>
#include "rgb_color.h"

// #419begin #type=3 #src=<Ray Tracing from the Ground Up, Suffern, Kevin>

const double 	PI 			= 3.1415926535897932384;
const double 	TWO_PI 		= 6.2831853071795864769;
const double 	PI_ON_180 	= 0.0174532925199432957;
const double 	invPI 		= 0.3183098861837906715;
const double 	invTWO_PI 	= 0.1591549430918953358;

const double 	kEpsilon 	= 0.0001; // epsilon value for the calculations
const double	kHugeValue	= 1.0E10; // the theoretical max value to be used in algorithms
// #419end

// color pre-definitions
const RGBColor	black(0.0);
const RGBColor	white(1.0);
const RGBColor	red(1.0, 0.0, 0.0);
const RGBColor	green(0.0, 1.0, 0.0);
const RGBColor	blue(0.0, 0.0, 1.0);
const RGBColor 	grey(0.3);

// i do not know what the heck is this
const float 	invRAND_MAX = 1.0 / (float)RAND_MAX;


// geometric body types
const int PLANE = 0;
const int TRIANGLE = 1;
const int SPHERE = 2;

#endif

