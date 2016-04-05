#include "world.h"

/*
	main()
	takes void
	returns void
	run the main program
	note: the program not yet memory optimized
	leaks everywhere
*/
int main() {
	World w;
	w.build();
	w.render_scene();
}