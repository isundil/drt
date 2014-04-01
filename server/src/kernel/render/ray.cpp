#include <string>
#include "ray.hpp"

#include <iostream>

Ray::Ray(double x, double y, double z) : AObject() {
  this->x = x;
  this->y = y;
  this->z = z;
}

double Ray::getX()
{ return (double)((double)x + (double)mod_x); }

double Ray::getY()
{ return (double)((double)y + (double)mod_y); }

double Ray::getZ()
{ return (double)((double)z + (double)mod_z); }

double	Ray::getModX()
{return mod_x;}

double	Ray::getModY()
{return mod_y;}

double	Ray::getModZ()
{return mod_z;}

void Ray::setX(double _x)
{ mod_x = (double)_x; }

void Ray::setY(double _y)
{ mod_y = (double)_y; }

void Ray::setZ(double _z)
{ mod_z = (double)_z; }

void Ray::reset() {
  mod_x = (double)0;
  mod_y = (double)0;
  mod_z = (double)0;
}
