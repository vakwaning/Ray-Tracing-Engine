#pragma once 
#include "ray_project1.hpp"
#include "ray_project1.cpp"

class Shape{
private:
    Color color;
    float reflexivity;

public:
    Shape();
    Shape(Color, float);
    double virtual get_collision_time(Ray) = 0;
    Vector virtual get_normal_vector(Vector) = 0;
    Color get_color();
    double get_reflectivity();
    virtual ~Shape();
};

class Sphere : public Shape{
private:
    Vector center;
    double radius;

public:
    Sphere();
    Sphere(Color, float, Vector, double);
    double virtual get_collision_time(Ray);
    Vector virtual get_normal_vector(Vector);
};

class Plane : public Shape{
private:
    Vector point;
    Vector norm_vector;

public:
    Plane();
    Plane(Color, float, Vector, Vector);
    virtual double  get_collision_time(Ray);
    virtual Vector  get_normal_vector(Vector);
};
