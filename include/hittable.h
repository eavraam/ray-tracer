#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
public:
	point3 p;
	vec3 normal;
	double t;
	bool front_face;

	// outward normal is assumed to have unit length
	void set_face_normal(const ray& ray, const vec3& outward_normal) {
		front_face = dot(ray.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}

};

class hittable {
public:
	virtual ~hittable() = default;

	virtual bool hit(const ray& ray, interval ray_t, hit_record& hit_rec) const = 0;
};

#endif