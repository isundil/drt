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
  void addProperty(int name, APropertyValue * property);
  APropertyValue *operator[](int name) { return properties[name]; }

private :

  std::map<int, APropertyValue *> properties;

};

class AObject : public IObject {
public:
  AObject();

  APropertyValue	*getProperty(int name);

  template <class T>
  T at(int name) {
    return ((PropertyValue<T> *) this->getProperty(name))->getValue();
  }

protected:

  ObjectProperties _props;
};
