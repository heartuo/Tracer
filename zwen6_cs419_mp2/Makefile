CC=g++
CC_OPTS=-g3 -std=c++11 -stdlib=libc++ -w
CC_LIBS=-L/opt/X11/lib
CC_DEFINES=
CC_INCLUDES=-I/opt/X11/include -I/opt/X11/include/freetype2
CC_LINKS=-lpngwriter -lpng -lfreetype -lpthread
CC_ARGS=${CC_OPTS} ${CC_LIBS} ${CC_DEFINES} ${CC_INCLUDES}

# clean is not a file
.PHONY=clean

# target "all" depends on all others
all: MP_2_test

MP_2_test: main world geometric tracers utilities
	@${CC} ${CC_ARGS} -o MP_2_test *.o ${CC_LINKS}

main: main.cpp
	@${CC} ${CC_ARGS} -c main.cpp ${CC_LINKS}

world: world.cpp
	@${CC} ${CC_ARGS} -c world.cpp ${CC_LINKS}

geometric: sphere.cpp plane.cpp triangle.cpp obj_model.cpp bvh.cpp
	@${CC} ${CC_ARGS} -c sphere.cpp plane.cpp triangle.cpp obj_model.cpp bvh.cpp

tracers: multi_tracer.cpp
	@${CC} ${CC_ARGS} -c multi_tracer.cpp

utilities: point3d.cpp vector3d.cpp normal.cpp ray.cpp rgb_color.cpp shade_rec.cpp matrix.cpp
	@${CC} ${CC_ARGS} -c point3d.cpp vector3d.cpp normal.cpp ray.cpp rgb_color.cpp shade_rec.cpp matrix.cpp
clean:
	@rm -f *.o MP_2_test
