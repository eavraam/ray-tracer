#include "rtweekend.h" // include first, the rest assume its definition

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


int main() {

	// materials
	auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto material_left = make_shared<Dielectric>(1.50);
	auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
	auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

	// world
	Hittable_list world;
	world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
	world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
	world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
	world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

	// camera
	Camera camera;

	camera.aspect_ratio		 = 16.f / 9.f;
	camera.image_width		 = 400;
	camera.samples_per_pixel = 100;
	camera.max_depth		 = 50;

	camera.vfov		 = 20;
	camera.look_from = point3(-2, 2, 1);
	camera.look_at	 = point3(0, 0, -1);
	camera.vup		 = vec3(0, 1, 0);

	camera.defocus_angle = 10.0f;
	camera.focus_dist	 = 3.4f;

	// render
	camera.render(world);
}