#include "AObject.hpp"

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
