#include <string>
#include "ray.hpp"

#include <iostream>

Ray::Ray(double x, double y, double z) : AObject() {
  this->x = x;
  this->y = y;
  this->z = z;
}

double Ray::getX() const
{ return x; }

double Ray::getY() const
{ return y; }

double Ray::getZ() const
{ return z; }

void Ray::setX(double _x)
{ x = _x; }

void Ray::setY(double _y)
{ y = _y; }

void Ray::setZ(double _z)
{ z = _z; }
