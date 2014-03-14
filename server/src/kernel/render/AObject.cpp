#include "AObject.hpp"
#include "camera.hpp"
#include "ray.hpp"

void ObjectProperties::addProperty(std::string name, APropertyValue * property) {
  if (properties.find(name) != properties.end()) {
    delete properties[name];
  }
  properties[name] = property;
}

APropertyValue *AObject::getProperty(std::string name) {
  return _props[name];
}

AObject::AObject() {
}

double	AObject::computeEquation(Camera * camera, Ray * ray) {
  return 0;
}
