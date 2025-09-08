#include <iostream>
#include "array.hpp"
#include <iostream>
#include "shapes.hpp"
#include "scene.hpp"
#include <fstream>


void write_ppm(const Array2D<Color>& pixels, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    out.write("P6\n", 3);
    std::string s = std::to_string(pixels.get_width());
    out.write(s.c_str(), s.length());
    out.write(" ", 1);
    s = std::to_string(pixels.get_height());
    out.write(s.c_str(), s.length());
    out.write("\n255\n", 5);
    char color[3];
    for (unsigned y = 0; y < pixels.get_height(); y++) {
        for (unsigned x = 0; x < pixels.get_width(); x++) {
        Color c = pixels.get(x, y);
        color[0] = c.get_r();
        color[1] = c.get_g();
        color[2] = c.get_b();
        out.write(color, 3);
        }
    }
    out.close();
}

int main(){
    Vector camera_position(0.5, -1.0, 0.5); 
    Vector light_position(0.0, -0.5, 1.0);
    // Color background_color(0, 0, 0); 
    Scene scene(camera_position, light_position);

    unsigned image_width = 512; 
    unsigned image_height = 512; 
    Array2D<Color> pixels(image_width, image_height);

    std::shared_ptr<Shape> plane = std::make_shared<Plane>(Color(255, 255, 255), 0, Vector(0,0,0), Vector(0, 0, 1));
    std::shared_ptr<Sphere> sp1 =  std::make_shared<Sphere>(Color(255, 0, 0), 0.3, Vector(0.25, 0.45, 0.4), 0.4);
    std::shared_ptr<Sphere> sp2 =  std::make_shared<Sphere>(Color(0, 255, 0), 0, Vector(1, 1, 0.25), 0.25);
    std::shared_ptr<Sphere> sp3 =  std::make_shared<Sphere>(Color(0, 0, 255), 0.7, Vector(0.8, 0.3, 0.15), 0.15);
    scene.add_shape(plane);
    scene.add_shape(sp1);
    scene.add_shape(sp2);
    scene.add_shape(sp3);

    for (unsigned y = 0; y < image_height; y++) {
        for (unsigned x = 0; x < image_width; x++) {
            Vector screen_point(x / ((double)image_width), 0, (image_height - y) / ((double)image_width));
            Color pixel_color = scene.get_point_color(screen_point);
            pixels.set(x, y, pixel_color);
        }
    }
    
    write_ppm(pixels, "image.ppm");
    return 0;
}