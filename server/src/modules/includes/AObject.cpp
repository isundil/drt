#include "AObject.hpp"

void ObjectProperties::addProperty(std::string name, APropertyValue * property) {
  properties[name] = property;
}

APropertyValue *AObject::getProperty(std::string name) {
  return _props[name];
}

AObject::AObject() {
  _props.addProperty("x", new PropertyValue<double>(0));
  _props.addProperty("y", new PropertyValue<double>(0));
  _props.addProperty("z", new PropertyValue<double>(0));
}
