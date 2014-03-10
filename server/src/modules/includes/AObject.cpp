#include "AObject.hpp"

void ObjectProperties::addProperty(int name, APropertyValue * property) {
  if (properties.find(name) != properties.end()) {
    delete properties[name];
  }
  properties[name] = property;
}

APropertyValue *AObject::getProperty(int name) {
  return _props[name];
}

AObject::AObject() {
  _props.addProperty(0, new PropertyValue<double>(0));
  _props.addProperty(1, new PropertyValue<double>(0));
  _props.addProperty(2, new PropertyValue<double>(0));
}
