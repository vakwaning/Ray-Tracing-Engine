#pragma once 
#include "shapes.hpp"
#include <vector>
#include <memory>

class Scene{
private:
    Vector cam_position;
    Vector light_position;
    Color back_color;
    std::vector<std::shared_ptr<Shape> > shapes;
    double ambient;
    double specular_factor;
    double specular_exponent;
    int max_reflections;
    
    Color get_ray_color(const Ray&, double);

public:
    Scene(Vector, Vector, Color, double, double, double, int);
    Scene(Vector, Vector);
    void add_shape(std::shared_ptr<Shape>);
    Color get_point_color(Vector);

    //~Scene();
};