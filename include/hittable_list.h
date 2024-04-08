#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

class Hittable_list : public Hittable {
public:
	Hittable_list() {}
	Hittable_list(shared_ptr<Hittable> object) { add(object); }

	void clear() { objects.clear(); }

	void add(shared_ptr<Hittable> object) {
		objects.push_back(object);
	}

	bool hit(const Ray& ray, Interval ray_t, Hit_record& hit_rec) const override {
		Hit_record temp_rec;
		bool hit_anything = false;
		auto closest_so_far = ray_t.max;

		for (const auto& object : objects) {
			if (object->hit(ray, Interval(ray_t.min, closest_so_far), temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				hit_rec = temp_rec;
			}
		}

		return hit_anything;
	}

public:
	std::vector<shared_ptr<Hittable>> objects;
};



#endif