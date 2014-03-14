#include <string>
#include "ray.hpp"

#include <iostream>

Ray::Ray(double x, double y, double z) : AObject() {
  this->x = x;
  this->y = y;
  this->z = z;
  // std::cout << "x : " << x << std::endl;
  // std::cout << "y : " << y << std::endl;
  // std::cout << "z : " << z << std::endl;

  // _props.addProperty("x", new PropertyValue<double>(x));
  // _props.addProperty("y", new PropertyValue<double>(y));
  // _props.addProperty("z", new PropertyValue<double>(z));
}
