#include "IObject.hh"

#include <string>
#include <map>

class APropertyValue {};

template <typename T>
class PropertyValue : public APropertyValue {
public:
  PropertyValue(T _val) : _val(value) {}
  T getValue() { return value; }
private :
  T value;
};

class ObjectProperties {
public:
  void addProperty(std::string name, APropertyValue * property);

private :

  std::map<std::string, APropertyValue *> properties;

};

class AObject {
public:
protected:

  ObjectProperties _props;
  double computeEquation(AObject * camera, AObject * ray);
};
