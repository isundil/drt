#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Plan : public AMathObject {
public:

  Plan(unsigned int color);

  virtual double computeEquation(Camera * camera, Ray * ray);
};
