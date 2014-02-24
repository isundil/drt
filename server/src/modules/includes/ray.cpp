#include <string>
#include "ray.hpp"

Ray::Ray() : AObject() {
  _props.addProperty("x", new PropertyValue<double>(1));
  _props.addProperty("y", new PropertyValue<double>(2));
  _props.addProperty("z", new PropertyValue<double>(4));
}
