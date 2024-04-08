#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable {
public:
	Sphere(const point3& _center, double _radius, shared_ptr<Material> _material)
		: center(_center), radius(fmax(0, _radius)), material(_material) { }

	bool hit(const Ray& ray, Interval ray_t, Hit_record& hit_rec) const override {
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
		hit_rec.material = material;

		return true;
	}

private:
	point3 center;
	double radius;
	shared_ptr<Material> material;
};

#endif
