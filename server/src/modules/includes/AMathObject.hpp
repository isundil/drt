#pragma once
#include "AObject.hpp"

class Camera;
class Ray;

class AMathObject : public AObject {
public:
  AMathObject() : AObject() {};

  virtual double computeEquation(Camera * camera, Ray * ray) = 0;
};

