#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	sphere(point3 _center, double _radius) : center(_center), radius(_radius) {};

	bool hit(const ray& ray, interval ray_t, hit_record& hit_rec) const override {
		vec3 dist = ray.origin() - center;
		auto a = ray.direction().length_squared();
		auto half_b = dot(dist, ray.direction());
		auto c = dist.length_squared() - radius * radius;

		auto discriminant = half_b * half_b - a * c;
		if (discriminant < 0) return false;
		auto sqrt_discriminant = sqrt(discriminant);

		// find the nearest root that lies in the acceptable range
		auto root = (-half_b - sqrt_discriminant) / a;
		if (!ray_t.surrounds(root)) {
			root = (-half_b + sqrt_discriminant) / a;
			if (!ray_t.surrounds(root)) {
				return false;
			}
		}

		hit_rec.t = root;
		hit_rec.p = ray.at(hit_rec.t);
		vec3 outward_normal = (hit_rec.p - center) / radius;
		hit_rec.set_face_normal(ray, outward_normal);

		return true;
	}

private:
	point3 center;
	double radius;
};

#endif
