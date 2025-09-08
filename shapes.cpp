#include <cmath>
#include <iostream>
#include "shapes.hpp"
#include <cstdio>

Shape::Shape(){
    this->color = Color();
    this->reflexivity = 0;
};

Shape::Shape(Color c, float reflexivity){
    this->color = c;
    this->reflexivity = reflexivity;
};

Color Shape::get_color(){
    return this->color;
};

double Shape::get_reflectivity(){
    return this->reflexivity;
};

Shape::~Shape() = default;

Sphere::Sphere(): Shape(Color(), 0){
    this->center = Vector();
    this->radius = 0;
};

Sphere::Sphere(Color color, float reflexivity, Vector center, double radius): Shape(color, reflexivity){
    this->center = center;
    this->radius = radius;
};

double Sphere::get_collision_time(Ray r){
    double t = -1;
    double t1 = 0;
    double t2 = 0;

    double a = r.get_direction().dot_product(r.get_direction());
   
    Vector s_c = r.get_start() - this->center;
    double b = 2 * (r.get_direction().dot_product(s_c)); 

    double c = s_c.dot_product(s_c) - (this->radius * this->radius);

    double disc = (b * b) - (4 * a * c);

    if (disc < 0){
        return t;
    }

    t1 = ((-1*b) + sqrt(disc)) / (2 * a);
    t2 = ((-1*b) - sqrt(disc)) / (2 * a);

    // const double t_min = 1e-6;
    // if (t1 >= t_min){
    //     return t1;
    // } 
    // if (t2 >= t_min) {
    //     return t2;
    // }
    // return t;
    if (t1 < 0 && t2 < 0){
        return t;
    } else if (t1 < 0){
        return t2;
    } else if (t2 < 0){
        return t1;
    } else {
       return std::min(t1, t2);
    }
    
};

Vector Sphere::get_normal_vector(Vector v){
    return v - this->center;
};


Plane::Plane():Shape(Color(), 0){
    this->point = Vector();
    this->norm_vector = Vector();
}; 

Plane::Plane(Color color, float reflexivity, Vector point, Vector norm_vec):Shape(color, reflexivity){
    this->point = point;
    this->norm_vector = norm_vec;
};

Vector Plane::get_normal_vector(Vector v){
    return this->norm_vector;
};

double Plane::get_collision_time(Ray r){
    double d_dot_n = r.get_direction().dot_product(this->norm_vector);

    if (std::abs(d_dot_n) < 1e-6){
        return -1;
    }

    Vector p_s = this->point - r.get_start();

    double num = p_s.dot_product(this->norm_vector);

    double t = num / d_dot_n;
    
    if (t < 0){
        return -1;
    } else{
        return t;
    }
};

