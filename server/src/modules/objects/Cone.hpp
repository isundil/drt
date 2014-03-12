#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Cone : public AMathObject {
public:

  Cone(double r);

  virtual double computeEquation(Camera * camera, Ray * ray);
};
