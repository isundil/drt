#include <string>
#include "ray.hpp"

#include <iostream>

Ray::Ray(double x, double y, double z) : AObject() {
  this->x = x;
  this->y = y;
  this->z = z;
}

double Ray::getX() const
{ return x + mod_x; }

double Ray::getY() const
{ return y + mod_y; }

double Ray::getZ() const
{ return z + mod_z; }

void Ray::setX(double _x)
{ mod_x = _x; }

void Ray::setY(double _y)
{ mod_y = _y; }

void Ray::setZ(double _z)
{ mod_z = _z; }

void Ray::reset() {
  mod_x = 0;
  mod_y = 0;
  mod_z = 0;
}
