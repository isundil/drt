#include <string>
#include "camera.hpp"

Camera::Camera(short x, short y, short z, double rx, double ry, double rz) : AObject() {
  _props.addProperty("x", new PropertyValue<double>(x));
  _props.addProperty("y", new PropertyValue<double>(y));
  _props.addProperty("z", new PropertyValue<double>(z));
  _props.addProperty("rx", new PropertyValue<double>(rx));
  _props.addProperty("ry", new PropertyValue<double>(ry));
  _props.addProperty("rz", new PropertyValue<double>(rz));
}
