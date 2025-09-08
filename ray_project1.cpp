#include <cmath>
#include <iostream>
#include "ray_project1.hpp"
#include <cstdio>

Vector::Vector(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
};

Vector::Vector(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
};

double Vector::dot_product(Vector V) const{
    return (this->x * V.x) + (this->y * V.y) + (this->z * V.z); 
};
    
double Vector::magnitude() const{
    return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
};

Vector Vector::project(Vector U) const{
    double v_u = this->dot_product(U);
    double u_u = U.dot_product(U);
    Vector proj_v_u = (v_u / u_u) * U;
    return proj_v_u;
};

Vector Vector::operator-(Vector V) const{
    double x = this->x - V.x;
    double y = this->y - V.y;
    double z = this->z - V.z;
    return Vector(x, y, z);
};

Vector Vector::operator-() const{
    double x = -1 * this->x;
    double y = -1 * this->y;
    double z = -1 * this->z;
    return Vector(x, y, z);
};

Vector Vector::operator+(Vector V) const{
    double x = this->x + V.x;
    double y = this->y + V.y;
    double z = this->z + V.z;
    return Vector(x, y, z);
};

Vector operator*(double c, Vector V){
    double x = c * V.x;
    double y = c * V.y;
    double z = c * V.z;
    return Vector(x, y, z);
};

double Vector::get_x() const{
    return this->x;
};

double Vector::get_y() const{
    return this->y;
};

double Vector::get_z() const{
    return this->z;
};

Ray::Ray(const Vector start,  const Vector dir){
    this->p = start;
    this->d = dir;
};

Vector Ray::get_start() const{
    return this->p;
};

Vector Ray::get_direction() const{
    return this->d;
};


Color::Color(){
    this->red = 0;
    this->green = 0;
    this->blue = 0;
}

Color::Color(double red, double green, double blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
};

double Color::get_r() const{
    return this->red;
};

double Color::get_g() const{
    return this->green;
};

double Color::get_b() const{
    return this->blue;
};

Color Color::operator+(Color c) const{
    double r = this->red + c.red;
    double g = this->green + c.green;
    double b = this->blue + c.blue;
    return Color(r, g, b);
};

void Color::operator+=(Color c){
    this->red += c.red;
    this->green += c.green;
    this->blue += c.blue;
};

Color operator*(double c, Color C){
    double r = c * C.red;
    double g = c * C.green;
    double b = c * C.blue;
    return Color(r, g, b);
};


void print_v(Vector V){
    std::cout << "[" << V.get_x() << ", ";
    std::cout << V.get_y() << ", ";
    std::cout << V.get_z() << "]";
    std::cout << std::endl;
};

void print_color(Color C){
    std::cout << "(r, g, b)->" << "(";
    std::cout << C.get_r() << ", ";
    std::cout << C.get_g() << ", ";
    std::cout << C.get_b() << ")";
    std::cout << std::endl;
};

