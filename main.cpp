#include <iostream>
#include <memory>

#include "utils/color_utils.h"
#include "utils/ray.h"
#include "utils/constants.h"
#include "utils/hittable_list.h"
#include "utils/sphere.h"
#include "utils/color.h"
#include "utils/camera.h"
#include "utils/lambertian.h"
#include "utils/metal.h"
#include "utils/dielectric.h"

#include "scene1.h"

int main()
{
    constexpr double aspect_ratio = 3.0 / 2.0;
    constexpr int image_width = 1200;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr int samples_per_pixel = 500;
    constexpr int max_depth = 50;
    CreateFileHeader(std::cout, image_width, image_height);

    HittableList world = RandomScene();

    Point3 lookfrom(13,2,2);
    Point3 lookat(0,0,0);
    Vector3 view_up(0,1,0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    Camera cam(lookfrom, lookat, view_up, 40, aspect_ratio, aperture, dist_to_focus);

    for (int i = image_height-1; i >= 0; --i) {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < image_width; ++j) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                double u = (j + RandomDouble()) / (image_width - 1);
                double v = (i + RandomDouble()) / (image_height - 1);
                Ray ray = cam.GetRay(u, v);
                pixel_color += RayColor(ray, world, max_depth);
            }
            WriteColor(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << std::endl << "Done." << std::endl;
    return 0;
}