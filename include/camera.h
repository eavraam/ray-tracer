#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"
#include "material.h"

class Camera {
public:
	double aspect_ratio      = 1.0; // Ratio of image width over height
	int    image_width       = 100; // Rendered image width in pixel count
    int    samples_per_pixel = 10;  // Count of random samples for each pixel
    int    max_depth         = 10;  // Maximum number of ray bounces into scene

    void render(const Hittable& world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                Color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    Ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:

    int    image_height;        // Rendered image height
    double pixel_samples_scale; // Color  scale factor for a sum of pixel samples
    point3 center;              // Camera center
    point3 pixel00_location;    // Location of pixel 0, 0
    vec3   pixel_delta_u;       // Offset to pixel to the right
    vec3   pixel_delta_v;       // Offset to pixel below

//> initialization
    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
//< initialization

//> ray
    // construct a camera ray originating from the origin and directed at randomly
    // sampled point around the pixel location i, j.
    Ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = pixel00_location
                            + ((i + offset.x()) * pixel_delta_u)
                            + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

    // generate a random sample in the [-0.5, -0.5] - [+0.5, +0.5] unit square.
    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    // get the ray color
	Color ray_color(const Ray& ray, int depth, const Hittable& world) {
		// if we exceed the ray bounce limit, no more light is gathered.
        if (depth <= 0) {
            return Color(0, 0, 0);
        }
        
        Hit_record hit_rec;
		// interval starts at 0.001 to approximate the floating point rounding errors
        // leading to shadow acne
        if (world.hit(ray, Interval(0.001, infinity), hit_rec)) {
            Ray scattered;
            Color attenuation;
            if (hit_rec.material->scatter(ray, hit_rec, attenuation, scattered)) {
                return attenuation * ray_color(scattered, depth - 1, world);
            }
            return Color(0, 0, 0);
		}

		vec3 unit_direction = unit_vector(ray.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	}
//< ray
};


#endif // !CAMERA_H
