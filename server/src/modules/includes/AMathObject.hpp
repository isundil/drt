#pragma once
#include "AObject.hpp"

#include "camera.hpp"
#include "ray.hpp"

#define SQ(a) (a * a)

class AMathObject : public AObject {
public:
  AMathObject() : AObject() {};

  virtual double computeEquation(Camera * camera, Ray * ray) = 0;
};

