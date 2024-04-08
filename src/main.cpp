#include "rtweekend.h" // include first, the rest assume its definition

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


int main() {

	// world
	Hittable_list world;
	world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

	// camera
	Camera camera;
	camera.aspect_ratio = 16.f / 9.f;
	camera.image_width	= 400;

	// render
	camera.render(world);
}