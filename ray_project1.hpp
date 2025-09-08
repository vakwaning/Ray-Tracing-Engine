#pragma once

class Vector {
private:
    double x;
    double y;
    double z;

public:
    Vector();
    Vector(double, double, double);

    double dot_product(Vector) const;
    double magnitude() const;
    Vector project(Vector) const;

    Vector operator-(Vector) const;
    Vector operator-() const;
    Vector operator+(Vector) const;

    friend Vector operator*(double, Vector);

    double get_x() const;
    double get_y() const;
    double get_z() const;
};


class Ray{
private:
    Vector p;
    Vector d;

public:
    Ray(const Vector, const Vector);
    Vector get_start() const;
    Vector get_direction() const;
};

class Color{
private:
    double red;
    double green;
    double blue;
    
public:
    Color();
    Color(double, double, double);
    double get_r() const;
    double get_g() const;
    double get_b() const;
    Color operator+(Color) const;
    void operator+=(Color);
    friend Color operator*(double, Color);
};