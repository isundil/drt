#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Sphere : public AMathObject {
public:

  Sphere();

  virtual double computeEquation(Camera * camera, Ray * ray);
};
