#include <cmath>
#include <iostream>
#include "scene.hpp"
#include "shapes.cpp"
#include "array.hpp"
#include <cstdio>
#include <vector>
#include <fstream>

Scene::Scene(Vector cam_pos, Vector light_pos, Color col, double ambient, double spec_factor, double spec_exp, int max_ref){
    this->cam_position = cam_pos;
    this->light_position = light_pos;
    this->back_color = col;
    this->ambient = ambient;
    this->specular_factor = spec_factor;
    this->specular_exponent = spec_exp;
    this->max_reflections = max_ref;
};

Scene::Scene(Vector cam_pos, Vector light_pos){
    this->cam_position = cam_pos;
    this->light_position = light_pos;
    this->back_color = Color(135, 206, 235);
    this->ambient = 0.2;
    this->specular_factor = 0.5;
    this->specular_exponent = 8;
    this->max_reflections = 6;
    //this->shape_len = 0;
};

void Scene::add_shape(std::shared_ptr<Shape> shape){
    this->shapes.push_back(shape);
};


Color Scene::get_point_color(Vector p){
    Vector d = p - this->cam_position;
    Ray r = Ray(this->cam_position, d);
    return get_ray_color(r, this->max_reflections);
};


Color Scene::get_ray_color(const Ray& r, double ref){
    double t = -1;
    Shape* hit_shape = nullptr;

    for (size_t i = 0; i < shapes.size(); i++) {
        Shape* curr_shape = this->shapes[i].get();
        double col_time = curr_shape->get_collision_time(r);
        if (col_time >= 0 && (t < 0 || col_time < t)) {
            t = col_time;
            hit_shape = curr_shape;
        }
    }

    if (hit_shape == nullptr){
        return this->back_color;
    }

    // Implementing the lightning model

    Vector int_point = r.get_start() + (t*r.get_direction());
    Vector norm_vect = hit_shape->get_normal_vector(int_point);

    norm_vect = (1 / norm_vect.magnitude()) * norm_vect;

    // Ambient light
    double a = this->ambient * (1 - hit_shape->get_reflectivity());
    Color l_ambient = a * hit_shape->get_color();


    // Checking for shadows
    Vector to_light = this->light_position - int_point;
    double light_dist = to_light.magnitude();
    Vector light_dir = (1 / light_dist) * to_light;
    Ray shadow_ray = Ray(int_point + 1e-6 * light_dir, light_dir);

    bool in_shadow = false;
    for (auto& shape : shapes) {
        double t = shape->get_collision_time(shadow_ray);
        if (t > 0 && t < light_dist) {
            in_shadow = true;
            break;
        }
    }


    // Diffuse light
    Vector lt = this->light_position - int_point;
    lt = (1 / lt.magnitude()) * lt; 
    Color l_diffuse = (1 - a) * (1 - hit_shape->get_reflectivity()) * std::max(0.0, norm_vect.dot_product(lt)) * hit_shape->get_color();

    // Specular light
    Vector h = lt + (1 / r.get_direction().magnitude()) * (-r.get_direction());
    h = (1 / h.magnitude()) * h;
    Color l_specular = this->specular_factor * std::pow(std::max(0.0, h.dot_product(norm_vect)), this->specular_exponent) * Color(255, 255, 255);

    // Reflections
    Color l_reflected = Color();

    if (ref > 0){
        Vector v = (1 / r.get_direction().magnitude()) * r.get_direction();
        Vector refl = (-v + 2 * (-v - norm_vect.project(v)));
        Ray ref_ray = Ray(int_point + 1e-6 * refl, refl);
        Color c = get_ray_color(ref_ray, ref - 1);
        l_reflected = (1 - a) * hit_shape->get_reflectivity() * c;
    }
    
    if (in_shadow){
        return l_ambient + l_reflected;
    } else {
    return l_ambient + l_diffuse + l_specular + l_reflected;
    }
};


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

// int main() {
//   Vector c_pos = Vector(0, 0, 10);
//   Vector l_pos = Vector(100, 100, -100);
//   Color back = Color(80, 91, 2.1);

//   float s_refl = 0.8;
//   Color s_col = Color(1.1, 201.2, 9.1);
//   Vector center = Vector(1, 1, 1);
//   double radius = 1;
//   std::shared_ptr<Shape> sphere(new Sphere(s_col, s_refl, center, radius));

//   float p_refl = 0.2;
//   Color p_col = Color(0, 0, 101);
//   Vector point = Vector(2, 2, 2);
//   Vector norm = Vector(1, 0, 0);
//   std::shared_ptr<Shape> plane(new Plane( p_col, p_refl, point, norm));

//   double l_ambient = 0.9;
//   double l_diffuse = 0.1;
//   unsigned l_specular = 10;
//   unsigned l_reflected = 9;

//   Scene scene1 = Scene(c_pos, l_pos, back, l_ambient, l_diffuse, l_specular, l_reflected);
//   scene1.add_shape(plane);
//   scene1.add_shape(sphere);

//   Vector point2 = Vector(10, 10, 10);
//   Color point_color = scene1.get_point_color(point2);
//   double red = point_color.get_r();
//   double green = point_color.get_g();
//   double blue = point_color.get_b();

//   std::cout << "Point color (should be 80, 91, 2.1): " << red << ", " << green << ", " << blue << std::endl;

//   Scene scene2 = Scene(c_pos, l_pos);
//   point_color = scene2.get_point_color(point2);
//   red = point_color.get_r();
//   green = point_color.get_g();
//   blue = point_color.get_b();

//   std::cout << "Point color (should be 135, 206, 235): " << red << ", " << green << ", " << blue << std::endl;
// }


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

