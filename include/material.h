#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

class Material {

public:
	virtual ~Material() = default;

	virtual bool scatter(
		const Ray& ray_in, const Hit_record& hit_rec, Color& attenuation, Ray& scattered
	) const {
		return false;
	}
};

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo) : albedo(albedo) {}

    bool scatter(const Ray& ray_in, const Hit_record& hit_rec, Color& attenuation, Ray& scattered) const override {
        auto scatter_direction = hit_rec.normal + random_unit_vector();

        // catch degenerate scatter direction
        if (scatter_direction.near_zero()) {
            scatter_direction = hit_rec.normal;
        }

        scattered = Ray(hit_rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};

class Metal : public Material {
public: 
    Metal(const Color& _albedo, double _fuzz)
        : albedo(_albedo), fuzz(_fuzz < 1 ? _fuzz : 1) {}

    bool scatter(const Ray& ray_in, const Hit_record& hit_rec, Color& attenuation, Ray& scattered) const override {
        vec3 reflected = reflect(ray_in.direction(), hit_rec.normal);
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = Ray(hit_rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), hit_rec.normal) > 0);
    }

private:
    Color albedo;
    double fuzz;
};

#endif