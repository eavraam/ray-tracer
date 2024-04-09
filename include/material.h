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

//> lambertian
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
//< lambertian

//> metal
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
//< metal


//> dielectric
class Dielectric : public Material {
public:
    Dielectric(double _refraction_index) : refraction_index(_refraction_index) {}

    bool scatter(const Ray& ray_in, const Hit_record& hit_rec, Color& attenuation, Ray& scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double ri = hit_rec.front_face ? (1.0 / refraction_index) : refraction_index;

        vec3 unit_direction(unit_vector(ray_in.direction()));
        vec3 refracted = refract(unit_direction, hit_rec.normal, ri);

        scattered = Ray(hit_rec.p, refracted);
        return true;
    }

private:
    double refraction_index;
};



//< dielectric
#endif