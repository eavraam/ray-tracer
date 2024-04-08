#ifndef HITTABLE_H
#define HITTABLE_H

class Hit_record {
public:
	point3 p;
	vec3 normal;
	double t;
	bool front_face;

	// outward normal is assumed to have unit length
	void set_face_normal(const Ray& ray, const vec3& outward_normal) {
		front_face = dot(ray.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}

};

class Hittable {
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& ray, Interval ray_t, Hit_record& hit_rec) const = 0;
};

#endif