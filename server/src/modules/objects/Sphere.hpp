#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Sphere : public AMathObject {
public:

  Sphere(double r);

  virtual double	computeEquation(Camera * camera, Ray * ray);
};
