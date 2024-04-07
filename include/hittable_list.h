#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }

	void add(shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	bool hit(const ray& ray, double ray_tmin, double ray_tmax, hit_record& hit_rec) const override {
		hit_record temp_rec;
		bool hit_anything = false;
		auto closest_so_far = ray_tmax;

		for (const auto& object : objects) {
			if (object->hit(ray, ray_tmin, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				hit_rec = temp_rec;
			}
		}

		return hit_anything;
	}

public:
	std::vector<shared_ptr<hittable>> objects;
};



#endif