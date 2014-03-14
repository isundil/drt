#include <string>
#include "ray.hpp"

Ray::Ray(double x, double y, double z) : AObject() {
  _props.addProperty("x", new PropertyValue<double>(x));
  _props.addProperty("y", new PropertyValue<double>(y));
  _props.addProperty("z", new PropertyValue<double>(r));
}
