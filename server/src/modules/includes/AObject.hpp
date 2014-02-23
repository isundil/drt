#pragma once

#include <string>
#include <map>

#include "IObject.hh"

class APropertyValue {};

template <typename T>
class PropertyValue : public APropertyValue {
public:
  PropertyValue(T _val) : value(_val) {}
  T getValue() { return value; }
private :
  T value;
};

class ObjectProperties {
public:
  void addProperty(std::string name, APropertyValue * property);
  APropertyValue *operator[](std::string name) { return properties[name]; }

private :

  std::map<std::string, APropertyValue *> properties;

};

class AObject : public IObject {
public:
  AObject();

  APropertyValue	*getProperty(std::string name);

  template <class T>
  T at(std::string name) {
    return ((PropertyValue<T> *) this->getProperty(name))->getValue();
  }

protected:

  ObjectProperties _props;
};
