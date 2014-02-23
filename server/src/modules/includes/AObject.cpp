#include "AObject.hpp"

void ObjectProperties::addProperty(std::string name, APropertyValue * property) {
  properties[name] = property;
}
